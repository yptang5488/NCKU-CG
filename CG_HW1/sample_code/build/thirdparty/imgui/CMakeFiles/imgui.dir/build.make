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
CMAKE_SOURCE_DIR = /home/cgvsl/Class_P76111131/CV_Hw1/sample_code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build

# Include any dependencies generated for this target.
include thirdparty/imgui/CMakeFiles/imgui.dir/depend.make

# Include the progress variables for this target.
include thirdparty/imgui/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include thirdparty/imgui/CMakeFiles/imgui.dir/flags.make

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: ../thirdparty/imgui/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui/imgui.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui/imgui.cpp.s

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: ../thirdparty/imgui/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_demo.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: ../thirdparty/imgui/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_draw.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o: ../thirdparty/imgui/imgui/imgui_impl_glfw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_glfw.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_glfw.cpp > CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_glfw.cpp -o CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.s

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o: ../thirdparty/imgui/imgui/imgui_impl_opengl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_opengl3.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_opengl3.cpp > CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.s

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o: thirdparty/imgui/CMakeFiles/imgui.dir/flags.make
thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o: ../thirdparty/imgui/imgui/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o -c /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_widgets.cpp

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i

thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_glfw.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_impl_opengl3.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/build.make
thirdparty/imgui/libimgui.a: thirdparty/imgui/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libimgui.a"
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
thirdparty/imgui/CMakeFiles/imgui.dir/build: thirdparty/imgui/libimgui.a

.PHONY : thirdparty/imgui/CMakeFiles/imgui.dir/build

thirdparty/imgui/CMakeFiles/imgui.dir/clean:
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : thirdparty/imgui/CMakeFiles/imgui.dir/clean

thirdparty/imgui/CMakeFiles/imgui.dir/depend:
	cd /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cgvsl/Class_P76111131/CV_Hw1/sample_code /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/thirdparty/imgui /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui /home/cgvsl/Class_P76111131/CV_Hw1/sample_code/build/thirdparty/imgui/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/imgui/CMakeFiles/imgui.dir/depend

