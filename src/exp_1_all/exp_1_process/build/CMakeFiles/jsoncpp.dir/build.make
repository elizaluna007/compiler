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
CMAKE_SOURCE_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build

# Include any dependencies generated for this target.
include CMakeFiles/jsoncpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jsoncpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jsoncpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsoncpp.dir/flags.make

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj: CMakeFiles/jsoncpp.dir/flags.make
CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj: CMakeFiles/jsoncpp.dir/includes_CXX.rsp
CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj: D:/360MoveData/Users/Luna/Desktop/compiler/src/exp_1_all/exp_1_process/src/third_party/jsoncpp/jsoncpp.cpp
CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj: CMakeFiles/jsoncpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj -MF CMakeFiles\jsoncpp.dir\src\third_party\jsoncpp\jsoncpp.cpp.obj.d -o CMakeFiles\jsoncpp.dir\src\third_party\jsoncpp\jsoncpp.cpp.obj -c D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\src\third_party\jsoncpp\jsoncpp.cpp

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.i"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\src\third_party\jsoncpp\jsoncpp.cpp > CMakeFiles\jsoncpp.dir\src\third_party\jsoncpp\jsoncpp.cpp.i

CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.s"
	G:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\src\third_party\jsoncpp\jsoncpp.cpp -o CMakeFiles\jsoncpp.dir\src\third_party\jsoncpp\jsoncpp.cpp.s

# Object files for target jsoncpp
jsoncpp_OBJECTS = \
"CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj"

# External object files for target jsoncpp
jsoncpp_EXTERNAL_OBJECTS =

D:/360MoveData/Users/Luna/Desktop/compiler/src/exp_1_all/exp_1_process/bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/src/third_party/jsoncpp/jsoncpp.cpp.obj
D:/360MoveData/Users/Luna/Desktop/compiler/src/exp_1_all/exp_1_process/bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/build.make
D:/360MoveData/Users/Luna/Desktop/compiler/src/exp_1_all/exp_1_process/bin/libjsoncpp.a: CMakeFiles/jsoncpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\bin\libjsoncpp.a"
	$(CMAKE_COMMAND) -P CMakeFiles\jsoncpp.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\jsoncpp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsoncpp.dir/build: D:/360MoveData/Users/Luna/Desktop/compiler/src/exp_1_all/exp_1_process/bin/libjsoncpp.a
.PHONY : CMakeFiles/jsoncpp.dir/build

CMakeFiles/jsoncpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\jsoncpp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/jsoncpp.dir/clean

CMakeFiles/jsoncpp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build D:\360MoveData\Users\Luna\Desktop\compiler\src\exp_1_all\exp_1_process\build\CMakeFiles\jsoncpp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsoncpp.dir/depend
