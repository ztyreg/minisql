# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ec2-user/minisql

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ec2-user/minisql/cmake-build

# Include any dependencies generated for this target.
include test/CMakeFiles/BufferPoolManagerTest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/BufferPoolManagerTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/BufferPoolManagerTest.dir/flags.make

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o: test/CMakeFiles/BufferPoolManagerTest.dir/flags.make
test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o: ../test/buffer/BufferPoolManagerTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ec2-user/minisql/cmake-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o"
	cd /home/ec2-user/minisql/cmake-build/test && /usr/bin/clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o -c /home/ec2-user/minisql/test/buffer/BufferPoolManagerTest.cpp

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.i"
	cd /home/ec2-user/minisql/cmake-build/test && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ec2-user/minisql/test/buffer/BufferPoolManagerTest.cpp > CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.i

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.s"
	cd /home/ec2-user/minisql/cmake-build/test && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ec2-user/minisql/test/buffer/BufferPoolManagerTest.cpp -o CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.s

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.requires:
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.requires

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.provides: test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/BufferPoolManagerTest.dir/build.make test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.provides.build
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.provides

test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.provides.build: test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o

# Object files for target BufferPoolManagerTest
BufferPoolManagerTest_OBJECTS = \
"CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o"

# External object files for target BufferPoolManagerTest
BufferPoolManagerTest_EXTERNAL_OBJECTS =

test/BufferPoolManagerTest: test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o
test/BufferPoolManagerTest: test/CMakeFiles/BufferPoolManagerTest.dir/build.make
test/BufferPoolManagerTest: test/libgtest.a
test/BufferPoolManagerTest: test/CMakeFiles/BufferPoolManagerTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable BufferPoolManagerTest"
	cd /home/ec2-user/minisql/cmake-build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BufferPoolManagerTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/BufferPoolManagerTest.dir/build: test/BufferPoolManagerTest
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/build

test/CMakeFiles/BufferPoolManagerTest.dir/requires: test/CMakeFiles/BufferPoolManagerTest.dir/buffer/BufferPoolManagerTest.cpp.o.requires
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/requires

test/CMakeFiles/BufferPoolManagerTest.dir/clean:
	cd /home/ec2-user/minisql/cmake-build/test && $(CMAKE_COMMAND) -P CMakeFiles/BufferPoolManagerTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/clean

test/CMakeFiles/BufferPoolManagerTest.dir/depend:
	cd /home/ec2-user/minisql/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ec2-user/minisql /home/ec2-user/minisql/test /home/ec2-user/minisql/cmake-build /home/ec2-user/minisql/cmake-build/test /home/ec2-user/minisql/cmake-build/test/CMakeFiles/BufferPoolManagerTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/BufferPoolManagerTest.dir/depend

