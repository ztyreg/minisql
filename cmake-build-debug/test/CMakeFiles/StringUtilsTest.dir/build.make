# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zty/Documents/Courses/Database/minisql

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug

# Include any dependencies generated for this target.
include test/CMakeFiles/StringUtilsTest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/StringUtilsTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/StringUtilsTest.dir/flags.make

test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o: test/CMakeFiles/StringUtilsTest.dir/flags.make
test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o: ../test/util/StringUtilsTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o"
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o -c /Users/zty/Documents/Courses/Database/minisql/test/util/StringUtilsTest.cpp

test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.i"
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zty/Documents/Courses/Database/minisql/test/util/StringUtilsTest.cpp > CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.i

test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.s"
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zty/Documents/Courses/Database/minisql/test/util/StringUtilsTest.cpp -o CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.s

# Object files for target StringUtilsTest
StringUtilsTest_OBJECTS = \
"CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o"

# External object files for target StringUtilsTest
StringUtilsTest_EXTERNAL_OBJECTS =

test/StringUtilsTest: test/CMakeFiles/StringUtilsTest.dir/util/StringUtilsTest.cpp.o
test/StringUtilsTest: test/CMakeFiles/StringUtilsTest.dir/build.make
test/StringUtilsTest: test/libgtest.a
test/StringUtilsTest: test/CMakeFiles/StringUtilsTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StringUtilsTest"
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StringUtilsTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/StringUtilsTest.dir/build: test/StringUtilsTest

.PHONY : test/CMakeFiles/StringUtilsTest.dir/build

test/CMakeFiles/StringUtilsTest.dir/clean:
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/StringUtilsTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/StringUtilsTest.dir/clean

test/CMakeFiles/StringUtilsTest.dir/depend:
	cd /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zty/Documents/Courses/Database/minisql /Users/zty/Documents/Courses/Database/minisql/test /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test /Users/zty/Documents/Courses/Database/minisql/cmake-build-debug/test/CMakeFiles/StringUtilsTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/StringUtilsTest.dir/depend
