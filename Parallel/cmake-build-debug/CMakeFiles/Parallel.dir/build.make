# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /snap/clion/184/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/184/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Code/Graph_creation/Parallel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Code/Graph_creation/Parallel/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Parallel.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Parallel.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Parallel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Parallel.dir/flags.make

CMakeFiles/Parallel.dir/main.cpp.o: CMakeFiles/Parallel.dir/flags.make
CMakeFiles/Parallel.dir/main.cpp.o: ../main.cpp
CMakeFiles/Parallel.dir/main.cpp.o: CMakeFiles/Parallel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Code/Graph_creation/Parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Parallel.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Parallel.dir/main.cpp.o -MF CMakeFiles/Parallel.dir/main.cpp.o.d -o CMakeFiles/Parallel.dir/main.cpp.o -c /home/user/Code/Graph_creation/Parallel/main.cpp

CMakeFiles/Parallel.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Code/Graph_creation/Parallel/main.cpp > CMakeFiles/Parallel.dir/main.cpp.i

CMakeFiles/Parallel.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Code/Graph_creation/Parallel/main.cpp -o CMakeFiles/Parallel.dir/main.cpp.s

CMakeFiles/Parallel.dir/Graph.cpp.o: CMakeFiles/Parallel.dir/flags.make
CMakeFiles/Parallel.dir/Graph.cpp.o: ../Graph.cpp
CMakeFiles/Parallel.dir/Graph.cpp.o: CMakeFiles/Parallel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Code/Graph_creation/Parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Parallel.dir/Graph.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Parallel.dir/Graph.cpp.o -MF CMakeFiles/Parallel.dir/Graph.cpp.o.d -o CMakeFiles/Parallel.dir/Graph.cpp.o -c /home/user/Code/Graph_creation/Parallel/Graph.cpp

CMakeFiles/Parallel.dir/Graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel.dir/Graph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Code/Graph_creation/Parallel/Graph.cpp > CMakeFiles/Parallel.dir/Graph.cpp.i

CMakeFiles/Parallel.dir/Graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel.dir/Graph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Code/Graph_creation/Parallel/Graph.cpp -o CMakeFiles/Parallel.dir/Graph.cpp.s

CMakeFiles/Parallel.dir/methods.cpp.o: CMakeFiles/Parallel.dir/flags.make
CMakeFiles/Parallel.dir/methods.cpp.o: ../methods.cpp
CMakeFiles/Parallel.dir/methods.cpp.o: CMakeFiles/Parallel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/Code/Graph_creation/Parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Parallel.dir/methods.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Parallel.dir/methods.cpp.o -MF CMakeFiles/Parallel.dir/methods.cpp.o.d -o CMakeFiles/Parallel.dir/methods.cpp.o -c /home/user/Code/Graph_creation/Parallel/methods.cpp

CMakeFiles/Parallel.dir/methods.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Parallel.dir/methods.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/Code/Graph_creation/Parallel/methods.cpp > CMakeFiles/Parallel.dir/methods.cpp.i

CMakeFiles/Parallel.dir/methods.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Parallel.dir/methods.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/Code/Graph_creation/Parallel/methods.cpp -o CMakeFiles/Parallel.dir/methods.cpp.s

# Object files for target Parallel
Parallel_OBJECTS = \
"CMakeFiles/Parallel.dir/main.cpp.o" \
"CMakeFiles/Parallel.dir/Graph.cpp.o" \
"CMakeFiles/Parallel.dir/methods.cpp.o"

# External object files for target Parallel
Parallel_EXTERNAL_OBJECTS =

Parallel: CMakeFiles/Parallel.dir/main.cpp.o
Parallel: CMakeFiles/Parallel.dir/Graph.cpp.o
Parallel: CMakeFiles/Parallel.dir/methods.cpp.o
Parallel: CMakeFiles/Parallel.dir/build.make
Parallel: CMakeFiles/Parallel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/Code/Graph_creation/Parallel/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Parallel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Parallel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Parallel.dir/build: Parallel
.PHONY : CMakeFiles/Parallel.dir/build

CMakeFiles/Parallel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Parallel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Parallel.dir/clean

CMakeFiles/Parallel.dir/depend:
	cd /home/user/Code/Graph_creation/Parallel/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Code/Graph_creation/Parallel /home/user/Code/Graph_creation/Parallel /home/user/Code/Graph_creation/Parallel/cmake-build-debug /home/user/Code/Graph_creation/Parallel/cmake-build-debug /home/user/Code/Graph_creation/Parallel/cmake-build-debug/CMakeFiles/Parallel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Parallel.dir/depend

