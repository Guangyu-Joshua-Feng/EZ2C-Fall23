# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build

# Include any dependencies generated for this target.
include CMakeFiles/federate__c1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/federate__c1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/federate__c1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/federate__c1.dir/flags.make

CMakeFiles/federate__c1.dir/lib/schedule.c.o: CMakeFiles/federate__c1.dir/flags.make
CMakeFiles/federate__c1.dir/lib/schedule.c.o: ../lib/schedule.c
CMakeFiles/federate__c1.dir/lib/schedule.c.o: CMakeFiles/federate__c1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/federate__c1.dir/lib/schedule.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/federate__c1.dir/lib/schedule.c.o -MF CMakeFiles/federate__c1.dir/lib/schedule.c.o.d -o CMakeFiles/federate__c1.dir/lib/schedule.c.o -c /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/lib/schedule.c

CMakeFiles/federate__c1.dir/lib/schedule.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/federate__c1.dir/lib/schedule.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/lib/schedule.c > CMakeFiles/federate__c1.dir/lib/schedule.c.i

CMakeFiles/federate__c1.dir/lib/schedule.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/federate__c1.dir/lib/schedule.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/lib/schedule.c -o CMakeFiles/federate__c1.dir/lib/schedule.c.s

CMakeFiles/federate__c1.dir/_federate__c1_main.c.o: CMakeFiles/federate__c1.dir/flags.make
CMakeFiles/federate__c1.dir/_federate__c1_main.c.o: ../_federate__c1_main.c
CMakeFiles/federate__c1.dir/_federate__c1_main.c.o: CMakeFiles/federate__c1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/federate__c1.dir/_federate__c1_main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/federate__c1.dir/_federate__c1_main.c.o -MF CMakeFiles/federate__c1.dir/_federate__c1_main.c.o.d -o CMakeFiles/federate__c1.dir/_federate__c1_main.c.o -c /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_federate__c1_main.c

CMakeFiles/federate__c1.dir/_federate__c1_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/federate__c1.dir/_federate__c1_main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_federate__c1_main.c > CMakeFiles/federate__c1.dir/_federate__c1_main.c.i

CMakeFiles/federate__c1.dir/_federate__c1_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/federate__c1.dir/_federate__c1_main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_federate__c1_main.c -o CMakeFiles/federate__c1.dir/_federate__c1_main.c.s

CMakeFiles/federate__c1.dir/_count1.c.o: CMakeFiles/federate__c1.dir/flags.make
CMakeFiles/federate__c1.dir/_count1.c.o: ../_count1.c
CMakeFiles/federate__c1.dir/_count1.c.o: CMakeFiles/federate__c1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/federate__c1.dir/_count1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/federate__c1.dir/_count1.c.o -MF CMakeFiles/federate__c1.dir/_count1.c.o.d -o CMakeFiles/federate__c1.dir/_count1.c.o -c /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_count1.c

CMakeFiles/federate__c1.dir/_count1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/federate__c1.dir/_count1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_count1.c > CMakeFiles/federate__c1.dir/_count1.c.i

CMakeFiles/federate__c1.dir/_count1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/federate__c1.dir/_count1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_count1.c -o CMakeFiles/federate__c1.dir/_count1.c.s

CMakeFiles/federate__c1.dir/_networksender_0null.c.o: CMakeFiles/federate__c1.dir/flags.make
CMakeFiles/federate__c1.dir/_networksender_0null.c.o: ../_networksender_0null.c
CMakeFiles/federate__c1.dir/_networksender_0null.c.o: CMakeFiles/federate__c1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/federate__c1.dir/_networksender_0null.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/federate__c1.dir/_networksender_0null.c.o -MF CMakeFiles/federate__c1.dir/_networksender_0null.c.o.d -o CMakeFiles/federate__c1.dir/_networksender_0null.c.o -c /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_networksender_0null.c

CMakeFiles/federate__c1.dir/_networksender_0null.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/federate__c1.dir/_networksender_0null.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_networksender_0null.c > CMakeFiles/federate__c1.dir/_networksender_0null.c.i

CMakeFiles/federate__c1.dir/_networksender_0null.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/federate__c1.dir/_networksender_0null.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/_networksender_0null.c -o CMakeFiles/federate__c1.dir/_networksender_0null.c.s

CMakeFiles/federate__c1.dir/federate__c1.c.o: CMakeFiles/federate__c1.dir/flags.make
CMakeFiles/federate__c1.dir/federate__c1.c.o: ../federate__c1.c
CMakeFiles/federate__c1.dir/federate__c1.c.o: CMakeFiles/federate__c1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/federate__c1.dir/federate__c1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/federate__c1.dir/federate__c1.c.o -MF CMakeFiles/federate__c1.dir/federate__c1.c.o.d -o CMakeFiles/federate__c1.dir/federate__c1.c.o -c /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/federate__c1.c

CMakeFiles/federate__c1.dir/federate__c1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/federate__c1.dir/federate__c1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/federate__c1.c > CMakeFiles/federate__c1.dir/federate__c1.c.i

CMakeFiles/federate__c1.dir/federate__c1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/federate__c1.dir/federate__c1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/federate__c1.c -o CMakeFiles/federate__c1.dir/federate__c1.c.s

# Object files for target federate__c1
federate__c1_OBJECTS = \
"CMakeFiles/federate__c1.dir/lib/schedule.c.o" \
"CMakeFiles/federate__c1.dir/_federate__c1_main.c.o" \
"CMakeFiles/federate__c1.dir/_count1.c.o" \
"CMakeFiles/federate__c1.dir/_networksender_0null.c.o" \
"CMakeFiles/federate__c1.dir/federate__c1.c.o"

# External object files for target federate__c1
federate__c1_EXTERNAL_OBJECTS =

federate__c1: CMakeFiles/federate__c1.dir/lib/schedule.c.o
federate__c1: CMakeFiles/federate__c1.dir/_federate__c1_main.c.o
federate__c1: CMakeFiles/federate__c1.dir/_count1.c.o
federate__c1: CMakeFiles/federate__c1.dir/_networksender_0null.c.o
federate__c1: CMakeFiles/federate__c1.dir/federate__c1.c.o
federate__c1: CMakeFiles/federate__c1.dir/build.make
federate__c1: /usr/lib/x86_64-linux-gnu/libm.so
federate__c1: core/libcore.a
federate__c1: CMakeFiles/federate__c1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable federate__c1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/federate__c1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/federate__c1.dir/build: federate__c1
.PHONY : CMakeFiles/federate__c1.dir/build

CMakeFiles/federate__c1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/federate__c1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/federate__c1.dir/clean

CMakeFiles/federate__c1.dir/depend:
	cd /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1 /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1 /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build /home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__c1/build/CMakeFiles/federate__c1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/federate__c1.dir/depend

