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
CMAKE_SOURCE_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\exp_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build

# Include any dependencies generated for this target.
include CMakeFiles/Tools.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Tools.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Tools.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tools.dir/flags.make

CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj: CMakeFiles/Tools.dir/flags.make
CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj: CMakeFiles/Tools.dir/includes_CXX.rsp
CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2/src/tools/ir_executor.cpp
CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj: CMakeFiles/Tools.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj -MF CMakeFiles\Tools.dir\src\tools\ir_executor.cpp.obj.d -o CMakeFiles\Tools.dir\src\tools\ir_executor.cpp.obj -c D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\src\tools\ir_executor.cpp

CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.i"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\src\tools\ir_executor.cpp > CMakeFiles\Tools.dir\src\tools\ir_executor.cpp.i

CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.s"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\src\tools\ir_executor.cpp -o CMakeFiles\Tools.dir\src\tools\ir_executor.cpp.s

# Object files for target Tools
Tools_OBJECTS = \
"CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj"

# External object files for target Tools
Tools_EXTERNAL_OBJECTS =

D:/360MoveData/Users/Luna/Desktop/compiler/exp_2/bin/libTools.a: CMakeFiles/Tools.dir/src/tools/ir_executor.cpp.obj
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2/bin/libTools.a: CMakeFiles/Tools.dir/build.make
D:/360MoveData/Users/Luna/Desktop/compiler/exp_2/bin/libTools.a: CMakeFiles/Tools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\bin\libTools.a"
	$(CMAKE_COMMAND) -P CMakeFiles\Tools.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Tools.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tools.dir/build: D:/360MoveData/Users/Luna/Desktop/compiler/exp_2/bin/libTools.a
.PHONY : CMakeFiles/Tools.dir/build

CMakeFiles/Tools.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Tools.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Tools.dir/clean

CMakeFiles/Tools.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\360MoveData\Users\Luna\Desktop\compiler\exp_2 D:\360MoveData\Users\Luna\Desktop\compiler\exp_2 D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build D:\360MoveData\Users\Luna\Desktop\compiler\exp_2\build\CMakeFiles\Tools.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tools.dir/depend

