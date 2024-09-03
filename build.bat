@echo off

setlocal

cd %~dp0

if not exist build mkdir build
cd build

if "%Platform%" neq "x64" (
	echo ERROR: Platform is not "x64" - please run this from the MSVC x64 native tools command prompt.
	goto end
)

set "common_compile_options= /nologo /W3 /I.."
set "common_link_options= /incremental:no /opt:ref /subsystem:console"

set "debug_compile_options=%common_compile_options% /Od /Zo /Z7 /RTC1 /MTd"
set "debug_link_options=%common_link_options% /DEBUG:FULL"

set "release_compile_options=%common_compile_options% /O2 /Zo /Z7"
set "release_link_options=%common_link_options%"

if "%1"=="debug" (
  set "compile_options=%debug_compile_options%"
  set "link_options=%debug_common_link_options%"
) else if "%1"=="release" (
  set "compile_options=%release_compile_options%"
  set "link_options=%release_common_link_options%"
) else (
  goto invalid_arguments
)

if "%2" neq "" goto invalid_arguments

nasm -o membench_asm.obj -f win64 ..\src\membench.asm
cl %debug_compile_options% ..\src\membench.c /link %link_options% /pdb:membench.pdb /out:membench.exe membench_asm.obj

cl %compile_options% ..\src\main.c /link %link_options% /pdb:1brc.pdb /out:1brc.exe

goto end

:invalid_arguments
echo Invalid arguments^. Usage: build ^[debug or release^]
goto end

:end
endlocal
