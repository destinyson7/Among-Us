# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.6/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/tanish/Documents/Computer Graphics/assignments/1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/tanish/Documents/Computer Graphics/assignments/1/build"

# Include any dependencies generated for this target.
include CMakeFiles/assignment-0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment-0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment-0.dir/flags.make

CMakeFiles/assignment-0.dir/source/main.cpp.o: CMakeFiles/assignment-0.dir/flags.make
CMakeFiles/assignment-0.dir/source/main.cpp.o: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assignment-0.dir/source/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-0.dir/source/main.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp"

CMakeFiles/assignment-0.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-0.dir/source/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp" > CMakeFiles/assignment-0.dir/source/main.cpp.i

CMakeFiles/assignment-0.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-0.dir/source/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp" -o CMakeFiles/assignment-0.dir/source/main.cpp.s

# Object files for target assignment-0
assignment__0_OBJECTS = \
"CMakeFiles/assignment-0.dir/source/main.cpp.o"

# External object files for target assignment-0
assignment__0_EXTERNAL_OBJECTS =

assignment-0: CMakeFiles/assignment-0.dir/source/main.cpp.o
assignment-0: CMakeFiles/assignment-0.dir/build.make
assignment-0: libraries/glfw/src/libglfw3.a
assignment-0: libglad.a
assignment-0: /usr/local/lib/libGLEW.2.2.0.dylib
assignment-0: CMakeFiles/assignment-0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable assignment-0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment-0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment-0.dir/build: assignment-0

.PHONY : CMakeFiles/assignment-0.dir/build

CMakeFiles/assignment-0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assignment-0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assignment-0.dir/clean

CMakeFiles/assignment-0.dir/depend:
	cd "/Users/tanish/Documents/Computer Graphics/assignments/1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tanish/Documents/Computer Graphics/assignments/1" "/Users/tanish/Documents/Computer Graphics/assignments/1" "/Users/tanish/Documents/Computer Graphics/assignments/1/build" "/Users/tanish/Documents/Computer Graphics/assignments/1/build" "/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles/assignment-0.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/assignment-0.dir/depend

