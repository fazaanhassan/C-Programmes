# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fhassan/Downloads/RobotSim/Client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fhassan/Downloads/RobotSim/Client

# Include any dependencies generated for this target.
include Student_Submissions/CMakeFiles/task2.dir/depend.make

# Include the progress variables for this target.
include Student_Submissions/CMakeFiles/task2.dir/progress.make

# Include the compile flags for this target's objects.
include Student_Submissions/CMakeFiles/task2.dir/flags.make

# Object files for target task2
task2_OBJECTS =

# External object files for target task2
task2_EXTERNAL_OBJECTS =

Student_Submissions/task2: Student_Submissions/CMakeFiles/task2.dir/build.make
Student_Submissions/task2: src/libclient.a
Student_Submissions/task2: Student_Submissions/CMakeFiles/task2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fhassan/Downloads/RobotSim/Client/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX executable task2"
	cd /Users/fhassan/Downloads/RobotSim/Client/Student_Submissions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Student_Submissions/CMakeFiles/task2.dir/build: Student_Submissions/task2

.PHONY : Student_Submissions/CMakeFiles/task2.dir/build

Student_Submissions/CMakeFiles/task2.dir/requires:

.PHONY : Student_Submissions/CMakeFiles/task2.dir/requires

Student_Submissions/CMakeFiles/task2.dir/clean:
	cd /Users/fhassan/Downloads/RobotSim/Client/Student_Submissions && $(CMAKE_COMMAND) -P CMakeFiles/task2.dir/cmake_clean.cmake
.PHONY : Student_Submissions/CMakeFiles/task2.dir/clean

Student_Submissions/CMakeFiles/task2.dir/depend:
	cd /Users/fhassan/Downloads/RobotSim/Client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fhassan/Downloads/RobotSim/Client /Users/fhassan/Downloads/RobotSim/Client/Student_Submissions /Users/fhassan/Downloads/RobotSim/Client /Users/fhassan/Downloads/RobotSim/Client/Student_Submissions /Users/fhassan/Downloads/RobotSim/Client/Student_Submissions/CMakeFiles/task2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Student_Submissions/CMakeFiles/task2.dir/depend

