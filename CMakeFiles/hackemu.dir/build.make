# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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

# Include any dependencies generated for this target.
include CMakeFiles/hackemu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hackemu.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hackemu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hackemu.dir/flags.make

CMakeFiles/hackemu.dir/src/byte.c.obj: CMakeFiles/hackemu.dir/flags.make
CMakeFiles/hackemu.dir/src/byte.c.obj: CMakeFiles/hackemu.dir/includes_C.rsp
CMakeFiles/hackemu.dir/src/byte.c.obj: src/byte.c
CMakeFiles/hackemu.dir/src/byte.c.obj: CMakeFiles/hackemu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hackemu.dir/src/byte.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/hackemu.dir/src/byte.c.obj -MF CMakeFiles\hackemu.dir\src\byte.c.obj.d -o CMakeFiles\hackemu.dir\src\byte.c.obj -c C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\byte.c

CMakeFiles/hackemu.dir/src/byte.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hackemu.dir/src/byte.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\byte.c > CMakeFiles\hackemu.dir\src\byte.c.i

CMakeFiles/hackemu.dir/src/byte.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hackemu.dir/src/byte.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\byte.c -o CMakeFiles\hackemu.dir\src\byte.c.s

CMakeFiles/hackemu.dir/src/vm.c.obj: CMakeFiles/hackemu.dir/flags.make
CMakeFiles/hackemu.dir/src/vm.c.obj: CMakeFiles/hackemu.dir/includes_C.rsp
CMakeFiles/hackemu.dir/src/vm.c.obj: src/vm.c
CMakeFiles/hackemu.dir/src/vm.c.obj: CMakeFiles/hackemu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hackemu.dir/src/vm.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/hackemu.dir/src/vm.c.obj -MF CMakeFiles\hackemu.dir\src\vm.c.obj.d -o CMakeFiles\hackemu.dir\src\vm.c.obj -c C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\vm.c

CMakeFiles/hackemu.dir/src/vm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hackemu.dir/src/vm.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\vm.c > CMakeFiles\hackemu.dir\src\vm.c.i

CMakeFiles/hackemu.dir/src/vm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hackemu.dir/src/vm.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\src\vm.c -o CMakeFiles\hackemu.dir\src\vm.c.s

CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj: CMakeFiles/hackemu.dir/flags.make
CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj: CMakeFiles/hackemu.dir/includes_C.rsp
CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj: lib/minifb/src/windows/WinMiniFB.c
CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj: CMakeFiles/hackemu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj -MF CMakeFiles\hackemu.dir\lib\minifb\src\windows\WinMiniFB.c.obj.d -o CMakeFiles\hackemu.dir\lib\minifb\src\windows\WinMiniFB.c.obj -c C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\lib\minifb\src\windows\WinMiniFB.c

CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\lib\minifb\src\windows\WinMiniFB.c > CMakeFiles\hackemu.dir\lib\minifb\src\windows\WinMiniFB.c.i

CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\lib\minifb\src\windows\WinMiniFB.c -o CMakeFiles\hackemu.dir\lib\minifb\src\windows\WinMiniFB.c.s

# Object files for target hackemu
hackemu_OBJECTS = \
"CMakeFiles/hackemu.dir/src/byte.c.obj" \
"CMakeFiles/hackemu.dir/src/vm.c.obj" \
"CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj"

# External object files for target hackemu
hackemu_EXTERNAL_OBJECTS =

hackemu.exe: CMakeFiles/hackemu.dir/src/byte.c.obj
hackemu.exe: CMakeFiles/hackemu.dir/src/vm.c.obj
hackemu.exe: CMakeFiles/hackemu.dir/lib/minifb/src/windows/WinMiniFB.c.obj
hackemu.exe: CMakeFiles/hackemu.dir/build.make
hackemu.exe: lib/minifb/libminifb.a
hackemu.exe: CMakeFiles/hackemu.dir/linklibs.rsp
hackemu.exe: CMakeFiles/hackemu.dir/objects1.rsp
hackemu.exe: CMakeFiles/hackemu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable hackemu.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hackemu.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hackemu.dir/build: hackemu.exe
.PHONY : CMakeFiles/hackemu.dir/build

CMakeFiles/hackemu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hackemu.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hackemu.dir/clean

CMakeFiles/hackemu.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator C:\Users\FUZEdevLG\Documents\GitHub\Hack_Emulator\CMakeFiles\hackemu.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hackemu.dir/depend
