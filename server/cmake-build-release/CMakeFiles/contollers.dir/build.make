# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/bedilbek/INSTALL/CLion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/bedilbek/INSTALL/CLion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bedilbek/CLionProjects/os_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bedilbek/CLionProjects/os_project/server/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/contollers.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/contollers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/contollers.dir/flags.make

CMakeFiles/contollers.dir/server/controllers/login.c.o: CMakeFiles/contollers.dir/flags.make
CMakeFiles/contollers.dir/server/controllers/login.c.o: ../controllers/login.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bedilbek/CLionProjects/os_project/server/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/contollers.dir/server/controllers/login.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/contollers.dir/server/controllers/login.c.o   -c /home/bedilbek/CLionProjects/os_project/server/controllers/login.c

CMakeFiles/contollers.dir/server/controllers/login.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/contollers.dir/server/controllers/login.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bedilbek/CLionProjects/os_project/server/controllers/login.c > CMakeFiles/contollers.dir/server/controllers/login.c.i

CMakeFiles/contollers.dir/server/controllers/login.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/contollers.dir/server/controllers/login.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bedilbek/CLionProjects/os_project/server/controllers/login.c -o CMakeFiles/contollers.dir/server/controllers/login.c.s

CMakeFiles/contollers.dir/server/controllers/login.c.o.requires:

.PHONY : CMakeFiles/contollers.dir/server/controllers/login.c.o.requires

CMakeFiles/contollers.dir/server/controllers/login.c.o.provides: CMakeFiles/contollers.dir/server/controllers/login.c.o.requires
	$(MAKE) -f CMakeFiles/contollers.dir/build.make CMakeFiles/contollers.dir/server/controllers/login.c.o.provides.build
.PHONY : CMakeFiles/contollers.dir/server/controllers/login.c.o.provides

CMakeFiles/contollers.dir/server/controllers/login.c.o.provides.build: CMakeFiles/contollers.dir/server/controllers/login.c.o


CMakeFiles/contollers.dir/server/controllers/save_file.c.o: CMakeFiles/contollers.dir/flags.make
CMakeFiles/contollers.dir/server/controllers/save_file.c.o: ../controllers/save_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bedilbek/CLionProjects/os_project/server/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/contollers.dir/server/controllers/save_file.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/contollers.dir/server/controllers/save_file.c.o   -c /home/bedilbek/CLionProjects/os_project/server/controllers/save_file.c

CMakeFiles/contollers.dir/server/controllers/save_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/contollers.dir/server/controllers/save_file.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bedilbek/CLionProjects/os_project/server/controllers/save_file.c > CMakeFiles/contollers.dir/server/controllers/save_file.c.i

CMakeFiles/contollers.dir/server/controllers/save_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/contollers.dir/server/controllers/save_file.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bedilbek/CLionProjects/os_project/server/controllers/save_file.c -o CMakeFiles/contollers.dir/server/controllers/save_file.c.s

CMakeFiles/contollers.dir/server/controllers/save_file.c.o.requires:

.PHONY : CMakeFiles/contollers.dir/server/controllers/save_file.c.o.requires

CMakeFiles/contollers.dir/server/controllers/save_file.c.o.provides: CMakeFiles/contollers.dir/server/controllers/save_file.c.o.requires
	$(MAKE) -f CMakeFiles/contollers.dir/build.make CMakeFiles/contollers.dir/server/controllers/save_file.c.o.provides.build
.PHONY : CMakeFiles/contollers.dir/server/controllers/save_file.c.o.provides

CMakeFiles/contollers.dir/server/controllers/save_file.c.o.provides.build: CMakeFiles/contollers.dir/server/controllers/save_file.c.o


# Object files for target contollers
contollers_OBJECTS = \
"CMakeFiles/contollers.dir/server/controllers/login.c.o" \
"CMakeFiles/contollers.dir/server/controllers/save_file.c.o"

# External object files for target contollers
contollers_EXTERNAL_OBJECTS =

libcontollers.a: CMakeFiles/contollers.dir/server/controllers/login.c.o
libcontollers.a: CMakeFiles/contollers.dir/server/controllers/save_file.c.o
libcontollers.a: CMakeFiles/contollers.dir/build.make
libcontollers.a: CMakeFiles/contollers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bedilbek/CLionProjects/os_project/server/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libcontollers.a"
	$(CMAKE_COMMAND) -P CMakeFiles/contollers.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/contollers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/contollers.dir/build: libcontollers.a

.PHONY : CMakeFiles/contollers.dir/build

CMakeFiles/contollers.dir/requires: CMakeFiles/contollers.dir/server/controllers/login.c.o.requires
CMakeFiles/contollers.dir/requires: CMakeFiles/contollers.dir/server/controllers/save_file.c.o.requires

.PHONY : CMakeFiles/contollers.dir/requires

CMakeFiles/contollers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/contollers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/contollers.dir/clean

CMakeFiles/contollers.dir/depend:
	cd /home/bedilbek/CLionProjects/os_project/server/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bedilbek/CLionProjects/os_project /home/bedilbek/CLionProjects/os_project /home/bedilbek/CLionProjects/os_project/server/cmake-build-release /home/bedilbek/CLionProjects/os_project/server/cmake-build-release /home/bedilbek/CLionProjects/os_project/server/cmake-build-release/CMakeFiles/contollers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/contollers.dir/depend

