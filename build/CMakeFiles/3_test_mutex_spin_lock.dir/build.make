# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/cmake-3.9.1/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.9.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xuheding/share/linux_improve_study/7.3_cas_queue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuheding/share/linux_improve_study/7.3_cas_queue/build

# Include any dependencies generated for this target.
include CMakeFiles/3_test_mutex_spin_lock.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/3_test_mutex_spin_lock.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/3_test_mutex_spin_lock.dir/flags.make

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o: CMakeFiles/3_test_mutex_spin_lock.dir/flags.make
CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o: ../3_test_mutex_spin_lock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuheding/share/linux_improve_study/7.3_cas_queue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o"
	/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o -c /home/xuheding/share/linux_improve_study/7.3_cas_queue/3_test_mutex_spin_lock.cpp

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.i"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xuheding/share/linux_improve_study/7.3_cas_queue/3_test_mutex_spin_lock.cpp > CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.i

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.s"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xuheding/share/linux_improve_study/7.3_cas_queue/3_test_mutex_spin_lock.cpp -o CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.s

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.requires:

.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.requires

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.provides: CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.requires
	$(MAKE) -f CMakeFiles/3_test_mutex_spin_lock.dir/build.make CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.provides.build
.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.provides

CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.provides.build: CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o


# Object files for target 3_test_mutex_spin_lock
3_test_mutex_spin_lock_OBJECTS = \
"CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o"

# External object files for target 3_test_mutex_spin_lock
3_test_mutex_spin_lock_EXTERNAL_OBJECTS =

3_test_mutex_spin_lock: CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o
3_test_mutex_spin_lock: CMakeFiles/3_test_mutex_spin_lock.dir/build.make
3_test_mutex_spin_lock: CMakeFiles/3_test_mutex_spin_lock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuheding/share/linux_improve_study/7.3_cas_queue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 3_test_mutex_spin_lock"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/3_test_mutex_spin_lock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/3_test_mutex_spin_lock.dir/build: 3_test_mutex_spin_lock

.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/build

CMakeFiles/3_test_mutex_spin_lock.dir/requires: CMakeFiles/3_test_mutex_spin_lock.dir/3_test_mutex_spin_lock.cpp.o.requires

.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/requires

CMakeFiles/3_test_mutex_spin_lock.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/3_test_mutex_spin_lock.dir/cmake_clean.cmake
.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/clean

CMakeFiles/3_test_mutex_spin_lock.dir/depend:
	cd /home/xuheding/share/linux_improve_study/7.3_cas_queue/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuheding/share/linux_improve_study/7.3_cas_queue /home/xuheding/share/linux_improve_study/7.3_cas_queue /home/xuheding/share/linux_improve_study/7.3_cas_queue/build /home/xuheding/share/linux_improve_study/7.3_cas_queue/build /home/xuheding/share/linux_improve_study/7.3_cas_queue/build/CMakeFiles/3_test_mutex_spin_lock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/3_test_mutex_spin_lock.dir/depend

