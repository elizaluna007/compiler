# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /coursegrader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /coursegrader/build

# Include any dependencies generated for this target.
include CMakeFiles/Backend.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Backend.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Backend.dir/flags.make

CMakeFiles/Backend.dir/src/backend/generator.o: CMakeFiles/Backend.dir/flags.make
CMakeFiles/Backend.dir/src/backend/generator.o: ../src/backend/generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Backend.dir/src/backend/generator.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Backend.dir/src/backend/generator.o -c /coursegrader/src/backend/generator.cpp

CMakeFiles/Backend.dir/src/backend/generator.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Backend.dir/src/backend/generator.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /coursegrader/src/backend/generator.cpp > CMakeFiles/Backend.dir/src/backend/generator.i

CMakeFiles/Backend.dir/src/backend/generator.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Backend.dir/src/backend/generator.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /coursegrader/src/backend/generator.cpp -o CMakeFiles/Backend.dir/src/backend/generator.s

CMakeFiles/Backend.dir/src/backend/generator.o.requires:

.PHONY : CMakeFiles/Backend.dir/src/backend/generator.o.requires

CMakeFiles/Backend.dir/src/backend/generator.o.provides: CMakeFiles/Backend.dir/src/backend/generator.o.requires
	$(MAKE) -f CMakeFiles/Backend.dir/build.make CMakeFiles/Backend.dir/src/backend/generator.o.provides.build
.PHONY : CMakeFiles/Backend.dir/src/backend/generator.o.provides

CMakeFiles/Backend.dir/src/backend/generator.o.provides.build: CMakeFiles/Backend.dir/src/backend/generator.o


CMakeFiles/Backend.dir/src/backend/rv_def.o: CMakeFiles/Backend.dir/flags.make
CMakeFiles/Backend.dir/src/backend/rv_def.o: ../src/backend/rv_def.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Backend.dir/src/backend/rv_def.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Backend.dir/src/backend/rv_def.o -c /coursegrader/src/backend/rv_def.cpp

CMakeFiles/Backend.dir/src/backend/rv_def.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Backend.dir/src/backend/rv_def.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /coursegrader/src/backend/rv_def.cpp > CMakeFiles/Backend.dir/src/backend/rv_def.i

CMakeFiles/Backend.dir/src/backend/rv_def.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Backend.dir/src/backend/rv_def.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /coursegrader/src/backend/rv_def.cpp -o CMakeFiles/Backend.dir/src/backend/rv_def.s

CMakeFiles/Backend.dir/src/backend/rv_def.o.requires:

.PHONY : CMakeFiles/Backend.dir/src/backend/rv_def.o.requires

CMakeFiles/Backend.dir/src/backend/rv_def.o.provides: CMakeFiles/Backend.dir/src/backend/rv_def.o.requires
	$(MAKE) -f CMakeFiles/Backend.dir/build.make CMakeFiles/Backend.dir/src/backend/rv_def.o.provides.build
.PHONY : CMakeFiles/Backend.dir/src/backend/rv_def.o.provides

CMakeFiles/Backend.dir/src/backend/rv_def.o.provides.build: CMakeFiles/Backend.dir/src/backend/rv_def.o


CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o: CMakeFiles/Backend.dir/flags.make
CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o: ../src/backend/rv_inst_impl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o -c /coursegrader/src/backend/rv_inst_impl.cpp

CMakeFiles/Backend.dir/src/backend/rv_inst_impl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Backend.dir/src/backend/rv_inst_impl.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /coursegrader/src/backend/rv_inst_impl.cpp > CMakeFiles/Backend.dir/src/backend/rv_inst_impl.i

CMakeFiles/Backend.dir/src/backend/rv_inst_impl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Backend.dir/src/backend/rv_inst_impl.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /coursegrader/src/backend/rv_inst_impl.cpp -o CMakeFiles/Backend.dir/src/backend/rv_inst_impl.s

CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.requires:

.PHONY : CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.requires

CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.provides: CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.requires
	$(MAKE) -f CMakeFiles/Backend.dir/build.make CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.provides.build
.PHONY : CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.provides

CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.provides.build: CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o


# Object files for target Backend
Backend_OBJECTS = \
"CMakeFiles/Backend.dir/src/backend/generator.o" \
"CMakeFiles/Backend.dir/src/backend/rv_def.o" \
"CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o"

# External object files for target Backend
Backend_EXTERNAL_OBJECTS =

../bin/libBackend.a: CMakeFiles/Backend.dir/src/backend/generator.o
../bin/libBackend.a: CMakeFiles/Backend.dir/src/backend/rv_def.o
../bin/libBackend.a: CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o
../bin/libBackend.a: CMakeFiles/Backend.dir/build.make
../bin/libBackend.a: CMakeFiles/Backend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/coursegrader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../bin/libBackend.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Backend.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Backend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Backend.dir/build: ../bin/libBackend.a

.PHONY : CMakeFiles/Backend.dir/build

CMakeFiles/Backend.dir/requires: CMakeFiles/Backend.dir/src/backend/generator.o.requires
CMakeFiles/Backend.dir/requires: CMakeFiles/Backend.dir/src/backend/rv_def.o.requires
CMakeFiles/Backend.dir/requires: CMakeFiles/Backend.dir/src/backend/rv_inst_impl.o.requires

.PHONY : CMakeFiles/Backend.dir/requires

CMakeFiles/Backend.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Backend.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Backend.dir/clean

CMakeFiles/Backend.dir/depend:
	cd /coursegrader/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /coursegrader /coursegrader /coursegrader/build /coursegrader/build /coursegrader/build/CMakeFiles/Backend.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Backend.dir/depend

