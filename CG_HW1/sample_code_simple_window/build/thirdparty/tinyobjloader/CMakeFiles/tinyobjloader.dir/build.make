# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build

# Include any dependencies generated for this target.
include thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend.make

# Include the progress variables for this target.
include thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/flags.make

thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o: thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/flags.make
thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o: ../thirdparty/tinyobjloader/src/tiny_obj_loader.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/thirdparty/tinyobjloader/src/tiny_obj_loader.cc

thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/thirdparty/tinyobjloader/src/tiny_obj_loader.cc > CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.i

thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/thirdparty/tinyobjloader/src/tiny_obj_loader.cc -o CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.s

# Object files for target tinyobjloader
tinyobjloader_OBJECTS = \
"CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o"

# External object files for target tinyobjloader
tinyobjloader_EXTERNAL_OBJECTS =

thirdparty/tinyobjloader/libtinyobjloader.a: thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/src/tiny_obj_loader.cc.o
thirdparty/tinyobjloader/libtinyobjloader.a: thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/build.make
thirdparty/tinyobjloader/libtinyobjloader.a: thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtinyobjloader.a"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && $(CMAKE_COMMAND) -P CMakeFiles/tinyobjloader.dir/cmake_clean_target.cmake
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinyobjloader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/build: thirdparty/tinyobjloader/libtinyobjloader.a

.PHONY : thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/build

thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/clean:
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader && $(CMAKE_COMMAND) -P CMakeFiles/tinyobjloader.dir/cmake_clean.cmake
.PHONY : thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/clean

thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend:
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/thirdparty/tinyobjloader /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader /home/cgvsl/Class_P76111131/CV_Hw1/sample_code_simple_window/build/thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/tinyobjloader/CMakeFiles/tinyobjloader.dir/depend

