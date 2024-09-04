#include <windows.h>
#include <intrin.h>
#include <stdio.h>

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef double f64;

#define ASSERT(EX) ((EX) ? 1 : (*(volatile int*)0 = 0))

#define MAX_THREAD_COUNT 8

typedef struct Thread_Context
{
  HANDLE chew_event;
  HANDLE init_event;
  __m256* buffer;
  u64 buffer_size;
  u64 start_ticks;
  u64 end_ticks;
} Thread_Context;

// NOTE: buffer_size must be a multiple of 1024
void __vectorcall ReadFullSpeed(u64 buffer_size, __m256* buffer);

DWORD
ChewThroughBuffer(void* params)
{
  volatile Thread_Context* context = params;

  HANDLE chew_event = context->chew_event;
  HANDLE init_event = context->init_event;
  __m256* buffer  = context->buffer;
  u64 buffer_size = context->buffer_size;

  for (u64 i = 0; i < buffer_size/4; ++i)
  {
    ((u32*)buffer)[i] = 0x0B00BA50;
  }

  SetEvent(init_event);
  WaitForSingleObject(chew_event, INFINITE);

  u64 start_ticks = __rdtsc();
  
  ReadFullSpeed(buffer_size, buffer);

  u64 end_ticks = __rdtsc();

  context->start_ticks = start_ticks;
  context->end_ticks   = end_ticks;

  return 0;
}

int
main(int argc, char** argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid Arguments. Usage: membench [number of threads to spawn]\n");
    return -1;
  }

  int thread_count = 0;
  for (char* scan = argv[1]; *scan != 0; ++scan)
  {
    if (thread_count > MAX_THREAD_COUNT)
    {
      fprintf(stderr, "Thread count is too large\n");
      return -1;
    }
    else if ((u8)(*scan - '0') > (u8)9)
    {
      fprintf(stderr, "Thread count is not an integer\n");
      return -1;
    }
    else thread_count = thread_count*10 + (*scan&0xF);
  }

  if (thread_count == 0)
  {
    fprintf(stderr, "Thread count must be positive\n");
    return -1;
  }

  u64 per_thread_buffer_size = 1ULL << 30;
  u64 buffer_size            = (u64)thread_count * per_thread_buffer_size;

  ASSERT(per_thread_buffer_size % 1024 == 0);
  __m256* buffer = VirtualAlloc(0, buffer_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
  if (buffer == 0)
  {
    fprintf(stderr, "Failed to allocate buffer\n");
    return -1;
  }

  HANDLE thread_handles[MAX_THREAD_COUNT] = {0};
  HANDLE init_events[MAX_THREAD_COUNT] = {0};
  Thread_Context thread_contexts[MAX_THREAD_COUNT] = {0};

  HANDLE chew_event = CreateEventA(0, TRUE, FALSE, "start chewing");
  if (chew_event == 0)
  {
    fprintf(stderr, "Failed to create event for syncing threads\n");
    return -1;
  }

  for (u64 i = 0; i < thread_count; ++i)
  {
    init_events[i] = CreateEventA(0, TRUE, FALSE, "init done");
    if (init_events[i] == 0)
    {
      fprintf(stderr, "Failed to create event for syncing threads\n");
      return -1;
    }

    thread_contexts[i].chew_event   = chew_event;
    thread_contexts[i].init_event   = init_events[i];
    thread_contexts[i].buffer       = (__m256*)((u8*)buffer + i*per_thread_buffer_size);
    thread_contexts[i].buffer_size  = per_thread_buffer_size;
    thread_contexts[i].start_ticks  = 0;
    thread_contexts[i].end_ticks    = 0;

    thread_handles[i] = CreateThread(0, 0, ChewThroughBuffer, &thread_contexts[i], 0, 0);

    if (thread_handles[i] == 0)
    {
      fprintf(stderr, "Failed to create threads\n");
      return -1;
    }
  }

  WaitForMultipleObjects(thread_count, init_events, TRUE, INFINITE);

  SetEvent(chew_event);

  WaitForMultipleObjects(thread_count, thread_handles, TRUE, INFINITE);

  u64 earliest_start_ticks = ~(u64)0;
  u64 latest_end_ticks     = 0;
  u64 total_ticks = 0;
  u64 min_ticks   = ~(u64)0;
  u64 max_ticks   = 0;
  for (int i = 0; i < thread_count; ++i)
  {
    if (thread_contexts[i].start_ticks < earliest_start_ticks) earliest_start_ticks = thread_contexts[i].start_ticks;
    if (thread_contexts[i].end_ticks > latest_end_ticks) latest_end_ticks = thread_contexts[i].end_ticks;

    u64 ticks = thread_contexts[i].end_ticks - thread_contexts[i].start_ticks;

    total_ticks += ticks;
    if (ticks < min_ticks) min_ticks = ticks;
    if (ticks > max_ticks) max_ticks = ticks;
  }

  f64 rdtsc_freq;
  {
    LARGE_INTEGER perf_freq;
    QueryPerformanceFrequency(&perf_freq);

    LARGE_INTEGER start_time;
    QueryPerformanceCounter(&start_time);
    u64 start_rdtsc = __rdtsc();

    Sleep(300);

    u64 end_rdtsc = __rdtsc();
    LARGE_INTEGER end_time;
    QueryPerformanceCounter(&end_time);

    rdtsc_freq = (f64)(end_rdtsc - start_rdtsc) * ((f64)perf_freq.QuadPart / (end_time.QuadPart - start_time.QuadPart));
  }

  printf("Chewed through %.1f GB in %.6f s (rdtsc freq: %f Hz)\n", (f64)buffer_size/(1ULL << 30), total_ticks/rdtsc_freq, rdtsc_freq);

  f64 max_time = (f64)max_ticks/rdtsc_freq;
  f64 min_time = (f64)min_ticks/rdtsc_freq;
  f64 avg_time = ((f64)total_ticks/thread_count)/rdtsc_freq;
  f64 per_thread_GB = (f64)per_thread_buffer_size/(1ULL << 30);
  printf("per thread:  read %.1f GB, max %.2f GB/s, min %.2f GB/s, avg %.2f GB/s\n", per_thread_GB, per_thread_GB/max_time, per_thread_GB/min_time, per_thread_GB/avg_time);

  f64 wall_time = (f64)(latest_end_ticks - earliest_start_ticks)/rdtsc_freq;
  f64 buffer_size_GB = (f64)buffer_size/(1ULL << 30);
  printf("all threads: read %.1f GB, %.2f GB/s\n", buffer_size_GB, buffer_size_GB/wall_time);

  return 0;
}
