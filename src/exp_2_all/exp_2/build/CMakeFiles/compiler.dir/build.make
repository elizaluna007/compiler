# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/elizaluna007/install/cmake-3.26.3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/elizaluna007/install/cmake-3.26.3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/shared_file/compiler/exp_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/shared_file/compiler/exp_2/build

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

CMakeFiles/compiler.dir/main.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/main.cpp.o: /mnt/hgfs/shared_file/compiler/exp_2/main.cpp
CMakeFiles/compiler.dir/main.cpp.o: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/shared_file/compiler/exp_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compiler.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/main.cpp.o -MF CMakeFiles/compiler.dir/main.cpp.o.d -o CMakeFiles/compiler.dir/main.cpp.o -c /mnt/hgfs/shared_file/compiler/exp_2/main.cpp

CMakeFiles/compiler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/shared_file/compiler/exp_2/main.cpp > CMakeFiles/compiler.dir/main.cpp.i

CMakeFiles/compiler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/shared_file/compiler/exp_2/main.cpp -o CMakeFiles/compiler.dir/main.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/main.cpp.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: CMakeFiles/compiler.dir/main.cpp.o
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: CMakeFiles/compiler.dir/build.make
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: /mnt/hgfs/shared_file/compiler/exp_2/bin/libTools.a
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: /mnt/hgfs/shared_file/compiler/exp_2/bin/libFront.a
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: /mnt/hgfs/shared_file/compiler/exp_2/bin/libIR.a
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: /mnt/hgfs/shared_file/compiler/exp_2/bin/libjsoncpp.a
/mnt/hgfs/shared_file/compiler/exp_2/bin/compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/shared_file/compiler/exp_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /mnt/hgfs/shared_file/compiler/exp_2/bin/compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: /mnt/hgfs/shared_file/compiler/exp_2/bin/compiler
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend:
	cd /mnt/hgfs/shared_file/compiler/exp_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/shared_file/compiler/exp_2 /mnt/hgfs/shared_file/compiler/exp_2 /mnt/hgfs/shared_file/compiler/exp_2/build /mnt/hgfs/shared_file/compiler/exp_2/build /mnt/hgfs/shared_file/compiler/exp_2/build/CMakeFiles/compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compiler.dir/depend
