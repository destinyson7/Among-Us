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
include CMakeFiles/assignment-1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment-1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment-1.dir/flags.make

CMakeFiles/assignment-1.dir/source/game.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/game.cpp.o: ../source/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/assignment-1.dir/source/game.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/game.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/game.cpp"

CMakeFiles/assignment-1.dir/source/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/game.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/game.cpp" > CMakeFiles/assignment-1.dir/source/game.cpp.i

CMakeFiles/assignment-1.dir/source/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/game.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/game.cpp" -o CMakeFiles/assignment-1.dir/source/game.cpp.s

CMakeFiles/assignment-1.dir/source/main.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/main.cpp.o: ../source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/assignment-1.dir/source/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/main.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp"

CMakeFiles/assignment-1.dir/source/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp" > CMakeFiles/assignment-1.dir/source/main.cpp.i

CMakeFiles/assignment-1.dir/source/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/main.cpp" -o CMakeFiles/assignment-1.dir/source/main.cpp.s

CMakeFiles/assignment-1.dir/source/maze.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/maze.cpp.o: ../source/maze.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/assignment-1.dir/source/maze.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/maze.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/maze.cpp"

CMakeFiles/assignment-1.dir/source/maze.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/maze.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/maze.cpp" > CMakeFiles/assignment-1.dir/source/maze.cpp.i

CMakeFiles/assignment-1.dir/source/maze.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/maze.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/maze.cpp" -o CMakeFiles/assignment-1.dir/source/maze.cpp.s

CMakeFiles/assignment-1.dir/source/player.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/player.cpp.o: ../source/player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/assignment-1.dir/source/player.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/player.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/player.cpp"

CMakeFiles/assignment-1.dir/source/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/player.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/player.cpp" > CMakeFiles/assignment-1.dir/source/player.cpp.i

CMakeFiles/assignment-1.dir/source/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/player.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/player.cpp" -o CMakeFiles/assignment-1.dir/source/player.cpp.s

CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o: ../source/resource_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/resource_manager.cpp"

CMakeFiles/assignment-1.dir/source/resource_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/resource_manager.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/resource_manager.cpp" > CMakeFiles/assignment-1.dir/source/resource_manager.cpp.i

CMakeFiles/assignment-1.dir/source/resource_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/resource_manager.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/resource_manager.cpp" -o CMakeFiles/assignment-1.dir/source/resource_manager.cpp.s

CMakeFiles/assignment-1.dir/source/shader.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/shader.cpp.o: ../source/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/assignment-1.dir/source/shader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/shader.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/shader.cpp"

CMakeFiles/assignment-1.dir/source/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/shader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/shader.cpp" > CMakeFiles/assignment-1.dir/source/shader.cpp.i

CMakeFiles/assignment-1.dir/source/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/shader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/shader.cpp" -o CMakeFiles/assignment-1.dir/source/shader.cpp.s

CMakeFiles/assignment-1.dir/source/stb_image.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/stb_image.cpp.o: ../source/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/assignment-1.dir/source/stb_image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/stb_image.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/stb_image.cpp"

CMakeFiles/assignment-1.dir/source/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/stb_image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/stb_image.cpp" > CMakeFiles/assignment-1.dir/source/stb_image.cpp.i

CMakeFiles/assignment-1.dir/source/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/stb_image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/stb_image.cpp" -o CMakeFiles/assignment-1.dir/source/stb_image.cpp.s

CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o: ../source/text_renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/text_renderer.cpp"

CMakeFiles/assignment-1.dir/source/text_renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/text_renderer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/text_renderer.cpp" > CMakeFiles/assignment-1.dir/source/text_renderer.cpp.i

CMakeFiles/assignment-1.dir/source/text_renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/text_renderer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/text_renderer.cpp" -o CMakeFiles/assignment-1.dir/source/text_renderer.cpp.s

CMakeFiles/assignment-1.dir/source/texture.cpp.o: CMakeFiles/assignment-1.dir/flags.make
CMakeFiles/assignment-1.dir/source/texture.cpp.o: ../source/texture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/assignment-1.dir/source/texture.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/assignment-1.dir/source/texture.cpp.o -c "/Users/tanish/Documents/Computer Graphics/assignments/1/source/texture.cpp"

CMakeFiles/assignment-1.dir/source/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/assignment-1.dir/source/texture.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/tanish/Documents/Computer Graphics/assignments/1/source/texture.cpp" > CMakeFiles/assignment-1.dir/source/texture.cpp.i

CMakeFiles/assignment-1.dir/source/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/assignment-1.dir/source/texture.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/tanish/Documents/Computer Graphics/assignments/1/source/texture.cpp" -o CMakeFiles/assignment-1.dir/source/texture.cpp.s

# Object files for target assignment-1
assignment__1_OBJECTS = \
"CMakeFiles/assignment-1.dir/source/game.cpp.o" \
"CMakeFiles/assignment-1.dir/source/main.cpp.o" \
"CMakeFiles/assignment-1.dir/source/maze.cpp.o" \
"CMakeFiles/assignment-1.dir/source/player.cpp.o" \
"CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o" \
"CMakeFiles/assignment-1.dir/source/shader.cpp.o" \
"CMakeFiles/assignment-1.dir/source/stb_image.cpp.o" \
"CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o" \
"CMakeFiles/assignment-1.dir/source/texture.cpp.o"

# External object files for target assignment-1
assignment__1_EXTERNAL_OBJECTS =

assignment-1: CMakeFiles/assignment-1.dir/source/game.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/main.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/maze.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/player.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/resource_manager.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/shader.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/stb_image.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/text_renderer.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/source/texture.cpp.o
assignment-1: CMakeFiles/assignment-1.dir/build.make
assignment-1: libraries/glfw/src/libglfw3.a
assignment-1: libglad.a
assignment-1: /usr/local/lib/libGLEW.2.2.0.dylib
assignment-1: /usr/local/lib/libfreetype.dylib
assignment-1: CMakeFiles/assignment-1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable assignment-1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment-1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment-1.dir/build: assignment-1

.PHONY : CMakeFiles/assignment-1.dir/build

CMakeFiles/assignment-1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assignment-1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assignment-1.dir/clean

CMakeFiles/assignment-1.dir/depend:
	cd "/Users/tanish/Documents/Computer Graphics/assignments/1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/tanish/Documents/Computer Graphics/assignments/1" "/Users/tanish/Documents/Computer Graphics/assignments/1" "/Users/tanish/Documents/Computer Graphics/assignments/1/build" "/Users/tanish/Documents/Computer Graphics/assignments/1/build" "/Users/tanish/Documents/Computer Graphics/assignments/1/build/CMakeFiles/assignment-1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/assignment-1.dir/depend

