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
CMAKE_SOURCE_DIR = /example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /example/build

# Include any dependencies generated for this target.
include CMakeFiles/enviroment.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/enviroment.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/enviroment.dir/flags.make

CMakeFiles/enviroment.dir/boost.cpp.o: CMakeFiles/enviroment.dir/flags.make
CMakeFiles/enviroment.dir/boost.cpp.o: ../boost.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/enviroment.dir/boost.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/enviroment.dir/boost.cpp.o -c /example/boost.cpp

CMakeFiles/enviroment.dir/boost.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/enviroment.dir/boost.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /example/boost.cpp > CMakeFiles/enviroment.dir/boost.cpp.i

CMakeFiles/enviroment.dir/boost.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/enviroment.dir/boost.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /example/boost.cpp -o CMakeFiles/enviroment.dir/boost.cpp.s

CMakeFiles/enviroment.dir/boost.cpp.o.requires:

.PHONY : CMakeFiles/enviroment.dir/boost.cpp.o.requires

CMakeFiles/enviroment.dir/boost.cpp.o.provides: CMakeFiles/enviroment.dir/boost.cpp.o.requires
	$(MAKE) -f CMakeFiles/enviroment.dir/build.make CMakeFiles/enviroment.dir/boost.cpp.o.provides.build
.PHONY : CMakeFiles/enviroment.dir/boost.cpp.o.provides

CMakeFiles/enviroment.dir/boost.cpp.o.provides.build: CMakeFiles/enviroment.dir/boost.cpp.o


# Object files for target enviroment
enviroment_OBJECTS = \
"CMakeFiles/enviroment.dir/boost.cpp.o"

# External object files for target enviroment
enviroment_EXTERNAL_OBJECTS =

enviroment: CMakeFiles/enviroment.dir/boost.cpp.o
enviroment: CMakeFiles/enviroment.dir/build.make
enviroment: /usr/local/lib/libboost_filesystem.a
enviroment: /usr/local/lib/libboost_atomic.a
enviroment: CMakeFiles/enviroment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/example/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable enviroment"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enviroment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/enviroment.dir/build: enviroment

.PHONY : CMakeFiles/enviroment.dir/build

CMakeFiles/enviroment.dir/requires: CMakeFiles/enviroment.dir/boost.cpp.o.requires

.PHONY : CMakeFiles/enviroment.dir/requires

CMakeFiles/enviroment.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/enviroment.dir/cmake_clean.cmake
.PHONY : CMakeFiles/enviroment.dir/clean

CMakeFiles/enviroment.dir/depend:
	cd /example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /example /example /example/build /example/build /example/build/CMakeFiles/enviroment.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/enviroment.dir/depend

