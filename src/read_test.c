#include "common.h"

#include <stdio.h>

int
wmain(int argc, wchar_t** argv)
{
	if (argc != 2)
	{
		fwprintf(stderr, L"Invalid number of arguments. Expected: %s [path to measurements file]\n", argv[0]);
		return 1;
	}

	umm file_contents_cap      = 0;
	umm file_contents_len      = 0;
	u8* file_contents          = 0;
	u8* buffered_file_contents = 0;
	{
		wchar_t* file_path = argv[1];

		HANDLE file          = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN, 0);
		HANDLE file_buffered = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);
		if (file == INVALID_HANDLE_VALUE || file_buffered == INVALID_HANDLE_VALUE)
		{
			fwprintf(stderr, L"Failed to open file '%s'\n", file_path);
			return 1;
		}

		bool encountered_errors = false;
		do
		{
			u32 drive_path_cap = GetFinalPathNameByHandleW(file, 0, 0, VOLUME_NAME_DOS | FILE_NAME_NORMALIZED);
			
			wchar_t* drive_path = _alloca((u64)drive_path_cap*sizeof(wchar_t));

			u32 drive_path_len = GetFinalPathNameByHandleW(file, drive_path, drive_path_cap, FILE_NAME_NORMALIZED);

			if (drive_path_cap == 0 || drive_path_len == 0)
			{
				fwprintf(stderr, L"Failed to query full path name for the file '%s'\n", file_path);
				encountered_errors = true;
				break;
			}

			if (drive_path_len < 7 || drive_path[0] != L'\\'
					                   || drive_path[1] != L'\\'
														 || drive_path[2] != L'?' 
														 || drive_path[3] != L'\\'
														 || (u8)(((u8)drive_path[4]&0xDF) - 'A') > (u8)('Z' - 'A')
														 || drive_path[5] != L':'
														 || drive_path[6] != L'\\')
			{
				fwprintf(stderr, L"Failed because full path name of file does not contain the drive letter '%s'\n", drive_path);
				encountered_errors = true;
				break;
			}

			drive_path[sizeof("\\\\?\\C:\\")-1] = 0;
			drive_path += sizeof("\\\\?\\")-1;

			u32 sectors_per_cluster = 0;
			u32 sector_size         = 0;
			if (!GetDiskFreeSpaceW(drive_path, (LPDWORD)&sectors_per_cluster, (LPDWORD)&sector_size, &(DWORD){0}, &(DWORD){0}))
			{
				fwprintf(stderr, L"Failed to query drive information for the drive storing the file '%s'\n", file_path);
				encountered_errors = true;
				break;
			}

			LARGE_INTEGER file_size;
			if (!GetFileSizeEx(file, &file_size))
			{
				fwprintf(stderr, L"Failed to get size of file '%s'\n", file_path);
				encountered_errors = true;
				break;
			}

			file_contents_len = file_size.QuadPart;
			file_contents_cap = (file_contents_len + (sector_size-1)) & (u64)-(i64)sector_size;

			file_contents          = VirtualAlloc(0, file_contents_cap, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			buffered_file_contents = VirtualAlloc(0, file_contents_cap, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
			if (file_contents == 0 || buffered_file_contents == 0)
			{
				fprintf(stderr, "Failed to allocate memory for file (%f GB)\n", (f64)file_contents_cap/(1 << 30));
				encountered_errors = true;
				break;
			}

			LARGE_INTEGER perf_freq;
			QueryPerformanceFrequency(&perf_freq);

			umm max_attempts = 8;

			printf("non buffered\n");

			u64 min_t = ~0ULL;
			for (umm attempts = 0; attempts < max_attempts; ++attempts)
			{
				LARGE_INTEGER start_t;
				QueryPerformanceCounter(&start_t);

				for (u64 i = 0; i < (u64)file_contents_len;)
				{
					u32 to_read        = (1U << 31);
					u32 expected_bytes = to_read;
					if (i + to_read > file_contents_len)
					{
						expected_bytes = (u32)(file_contents_len - i);
						to_read        = (expected_bytes + (sector_size-1)) & (u32)-(i32)sector_size;
					}

					OVERLAPPED overlapped = { .Offset = (u32)i, .OffsetHigh = (u32)(i >> 32) };

					DWORD bytes_read = 0;
					if (!ReadFile(file, file_contents + i, to_read, &bytes_read, &overlapped) || bytes_read != expected_bytes)
					{
						fwprintf(stderr, L"Failed to read file '%s' (%u)\n", file_path, GetLastError());
						encountered_errors = true;
						break;
					}

					i += to_read;
				}

				LARGE_INTEGER end_t;
				QueryPerformanceCounter(&end_t);

				u64 t = end_t.QuadPart - start_t.QuadPart;

				printf("%llu\n", t);

				if (t < min_t)
				{
					min_t    = t;
					attempts = 0;
				}
			}

			if (encountered_errors) break;

			printf("\nbuffered\n");

			u64 buffered_min_t = ~0ULL;
			for (umm attempts = 0; attempts < max_attempts; ++attempts)
			{
				LARGE_INTEGER start_t;
				QueryPerformanceCounter(&start_t);

				for (u64 i = 0; i < (u64)file_contents_len;)
				{
					u32 to_read        = (1U << 31);
					u32 expected_bytes = to_read;
					if (i + to_read > file_contents_len)
					{
						expected_bytes = (u32)(file_contents_len - i);
						to_read        = (expected_bytes + (sector_size-1)) & (u32)-(i32)sector_size;
					}

					OVERLAPPED overlapped = { .Offset = (u32)i, .OffsetHigh = (u32)(i >> 32) };

					DWORD bytes_read = 0;
					if (!ReadFile(file_buffered, buffered_file_contents + i, to_read, &bytes_read, &overlapped) || bytes_read != expected_bytes)
					{
						fwprintf(stderr, L"Failed to read file '%s' (%u)\n", file_path, GetLastError());
						encountered_errors = true;
						break;
					}

					i += to_read;
				}

				LARGE_INTEGER end_t;
				QueryPerformanceCounter(&end_t);

				u64 t = end_t.QuadPart - start_t.QuadPart;

				printf("%llu\n", t);

				if (t < buffered_min_t)
				{
					buffered_min_t = t;
					attempts       = 0;
				}
			}

			if (encountered_errors) break;

			// assume it takes less than 1 minute to load the file
			// => 60*6e9 = 3.6e11 => max multiplier is (2^64-1)/3.6e11 = 5.12409557e7
			u64 hns_ps = 10000000;
			u64 min_t_hns          = (         min_t*hns_ps)/perf_freq.QuadPart;
			u64 buffered_min_t_hns = (buffered_min_t*hns_ps)/perf_freq.QuadPart;
			
			// log2(1000000 * ((2^35)/2^9) * 5^7) < 63
			u64 min_gbs          = (1000000 * (file_contents_cap>>9) * (hns_ps/(1<<7))) / (         min_t_hns*(1<<14));
			u64 buffered_min_gbs = (1000000 * (file_contents_cap>>9) * (hns_ps/(1<<7))) / (buffered_min_t_hns*(1<<14));

			u8 ld = min_gbs%10;
			if      (ld < 5) min_gbs = min_gbs/10;
			else if (ld > 5) min_gbs = min_gbs/10 + 1;
			else
			{
				min_gbs /= 10;
				min_gbs += (min_gbs % 2 == 0 ? 0 : 1);
			}

			u8 bld = buffered_min_gbs%10;
			if      (bld < 5) buffered_min_gbs = buffered_min_gbs/10;
			else if (bld > 5) buffered_min_gbs = buffered_min_gbs/10 + 1;
			else
			{
				buffered_min_gbs /= 10;
				buffered_min_gbs += (buffered_min_gbs % 2 == 0 ? 0 : 1);
			}

			printf("\n");
			printf("non-buffered: %llu.%05llu GB/s\n",          min_gbs/100000,          min_gbs%100000);
			printf("    buffered: %llu.%05llu GB/s\n", buffered_min_gbs/100000, buffered_min_gbs%100000);

		} while (0);

		CloseHandle(file);
		CloseHandle(file_buffered);

		if (encountered_errors) return 1;
	}

	//printf("%.*s\n", 1000, file_contents);

	return 0;
}
