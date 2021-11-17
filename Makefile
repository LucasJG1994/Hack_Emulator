# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake\bin\cmake-gui.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named hackemu

# Build rule for target.
hackemu: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 hackemu
.PHONY : hackemu

# fast build rule for target.
hackemu/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/build
.PHONY : hackemu/fast

#=============================================================================
# Target rules for targets named minifb

# Build rule for target.
minifb: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 minifb
.PHONY : minifb

# fast build rule for target.
minifb/fast:
	$(MAKE) $(MAKESILENT) -f lib\minifb\CMakeFiles\minifb.dir\build.make lib/minifb/CMakeFiles/minifb.dir/build
.PHONY : minifb/fast

#=============================================================================
# Target rules for targets named noise

# Build rule for target.
noise: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 noise
.PHONY : noise

# fast build rule for target.
noise/fast:
	$(MAKE) $(MAKESILENT) -f lib\minifb\CMakeFiles\noise.dir\build.make lib/minifb/CMakeFiles/noise.dir/build
.PHONY : noise/fast

#=============================================================================
# Target rules for targets named input_events

# Build rule for target.
input_events: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 input_events
.PHONY : input_events

# fast build rule for target.
input_events/fast:
	$(MAKE) $(MAKESILENT) -f lib\minifb\CMakeFiles\input_events.dir\build.make lib/minifb/CMakeFiles/input_events.dir/build
.PHONY : input_events/fast

#=============================================================================
# Target rules for targets named input_events_cpp

# Build rule for target.
input_events_cpp: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 input_events_cpp
.PHONY : input_events_cpp

# fast build rule for target.
input_events_cpp/fast:
	$(MAKE) $(MAKESILENT) -f lib\minifb\CMakeFiles\input_events_cpp.dir\build.make lib/minifb/CMakeFiles/input_events_cpp.dir/build
.PHONY : input_events_cpp/fast

#=============================================================================
# Target rules for targets named multiple_windows

# Build rule for target.
multiple_windows: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 multiple_windows
.PHONY : multiple_windows

# fast build rule for target.
multiple_windows/fast:
	$(MAKE) $(MAKESILENT) -f lib\minifb\CMakeFiles\multiple_windows.dir\build.make lib/minifb/CMakeFiles/multiple_windows.dir/build
.PHONY : multiple_windows/fast

lib/minifb/src/windows/WinMiniFB.obj: lib/minifb/src/windows/WinMiniFB.c.obj
.PHONY : lib/minifb/src/windows/WinMiniFB.obj

# target to build an object file
lib/minifb/src/windows/WinMiniFB.c.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj
.PHONY : lib/minifb/src/windows/WinMiniFB.c.obj

lib/minifb/src/windows/WinMiniFB.i: lib/minifb/src/windows/WinMiniFB.c.i
.PHONY : lib/minifb/src/windows/WinMiniFB.i

# target to preprocess a source file
lib/minifb/src/windows/WinMiniFB.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.i
.PHONY : lib/minifb/src/windows/WinMiniFB.c.i

lib/minifb/src/windows/WinMiniFB.s: lib/minifb/src/windows/WinMiniFB.c.s
.PHONY : lib/minifb/src/windows/WinMiniFB.s

# target to generate assembly for a file
lib/minifb/src/windows/WinMiniFB.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.s
.PHONY : lib/minifb/src/windows/WinMiniFB.c.s

src/byte.obj: src/byte.c.obj
.PHONY : src/byte.obj

# target to build an object file
src/byte.c.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/byte.c.obj
.PHONY : src/byte.c.obj

src/byte.i: src/byte.c.i
.PHONY : src/byte.i

# target to preprocess a source file
src/byte.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/byte.c.i
.PHONY : src/byte.c.i

src/byte.s: src/byte.c.s
.PHONY : src/byte.s

# target to generate assembly for a file
src/byte.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/byte.c.s
.PHONY : src/byte.c.s

src/vm.obj: src/vm.c.obj
.PHONY : src/vm.obj

# target to build an object file
src/vm.c.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/vm.c.obj
.PHONY : src/vm.c.obj

src/vm.i: src/vm.c.i
.PHONY : src/vm.i

# target to preprocess a source file
src/vm.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/vm.c.i
.PHONY : src/vm.c.i

src/vm.s: src/vm.c.s
.PHONY : src/vm.s

# target to generate assembly for a file
src/vm.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\hackemu.dir\build.make CMakeFiles/hackemu.dir/src/vm.c.s
.PHONY : src/vm.c.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... hackemu
	@echo ... input_events
	@echo ... input_events_cpp
	@echo ... minifb
	@echo ... multiple_windows
	@echo ... noise
	@echo ... lib/minifb/src/windows/WinMiniFB.obj
	@echo ... lib/minifb/src/windows/WinMiniFB.i
	@echo ... lib/minifb/src/windows/WinMiniFB.s
	@echo ... src/byte.obj
	@echo ... src/byte.i
	@echo ... src/byte.s
	@echo ... src/vm.obj
	@echo ... src/vm.i
	@echo ... src/vm.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system
