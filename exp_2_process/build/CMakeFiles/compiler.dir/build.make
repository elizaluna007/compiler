# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = G:\CMake\bin\cmake.exe

# The command to remove a file.
RM = G:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

CMakeFiles/compiler.dir/main.cpp.obj: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/main.cpp.obj: CMakeFiles/compiler.dir/includes_CXX.rsp
CMakeFiles/compiler.dir/main.cpp.obj: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/main.cpp
CMakeFiles/compiler.dir/main.cpp.obj: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compiler.dir/main.cpp.obj"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/main.cpp.obj -MF CMakeFiles\compiler.dir\main.cpp.obj.d -o CMakeFiles\compiler.dir\main.cpp.obj -c D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\main.cpp

CMakeFiles/compiler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/main.cpp.i"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\main.cpp > CMakeFiles\compiler.dir\main.cpp.i

CMakeFiles/compiler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/main.cpp.s"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\main.cpp -o CMakeFiles\compiler.dir\main.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/main.cpp.obj"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: CMakeFiles/compiler.dir/main.cpp.obj
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: CMakeFiles/compiler.dir/build.make
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/libTools.a
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/libFront.a
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/libIR.a
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/libjsoncpp.a
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: CMakeFiles/compiler.dir/linklibs.rsp
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: CMakeFiles/compiler.dir/objects1.rsp
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\bin\compiler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\compiler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2_process/bin/compiler.exe
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\compiler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build D:\360MoveData\Users\Luna\Desktop\compiler\exp_2_process\build\CMakeFiles\compiler.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compiler.dir/depend

