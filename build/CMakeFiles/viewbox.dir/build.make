# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build

# Include any dependencies generated for this target.
include CMakeFiles/viewbox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/viewbox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/viewbox.dir/flags.make

CMakeFiles/viewbox.dir/main.cpp.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/viewbox.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/main.cpp.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/main.cpp

CMakeFiles/viewbox.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/main.cpp > CMakeFiles/viewbox.dir/main.cpp.i

CMakeFiles/viewbox.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/main.cpp -o CMakeFiles/viewbox.dir/main.cpp.s

CMakeFiles/viewbox.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/viewbox.dir/main.cpp.o.requires

CMakeFiles/viewbox.dir/main.cpp.o.provides: CMakeFiles/viewbox.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/main.cpp.o.provides

CMakeFiles/viewbox.dir/main.cpp.o.provides.build: CMakeFiles/viewbox.dir/main.cpp.o


CMakeFiles/viewbox.dir/player.cpp.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/player.cpp.o: ../player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/viewbox.dir/player.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/player.cpp.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.cpp

CMakeFiles/viewbox.dir/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/player.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.cpp > CMakeFiles/viewbox.dir/player.cpp.i

CMakeFiles/viewbox.dir/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/player.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.cpp -o CMakeFiles/viewbox.dir/player.cpp.s

CMakeFiles/viewbox.dir/player.cpp.o.requires:

.PHONY : CMakeFiles/viewbox.dir/player.cpp.o.requires

CMakeFiles/viewbox.dir/player.cpp.o.provides: CMakeFiles/viewbox.dir/player.cpp.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/player.cpp.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/player.cpp.o.provides

CMakeFiles/viewbox.dir/player.cpp.o.provides.build: CMakeFiles/viewbox.dir/player.cpp.o


CMakeFiles/viewbox.dir/player.h.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/player.h.o: ../player.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/viewbox.dir/player.h.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/player.h.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.h

CMakeFiles/viewbox.dir/player.h.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/player.h.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.h > CMakeFiles/viewbox.dir/player.h.i

CMakeFiles/viewbox.dir/player.h.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/player.h.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/player.h -o CMakeFiles/viewbox.dir/player.h.s

CMakeFiles/viewbox.dir/player.h.o.requires:

.PHONY : CMakeFiles/viewbox.dir/player.h.o.requires

CMakeFiles/viewbox.dir/player.h.o.provides: CMakeFiles/viewbox.dir/player.h.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/player.h.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/player.h.o.provides

CMakeFiles/viewbox.dir/player.h.o.provides.build: CMakeFiles/viewbox.dir/player.h.o


CMakeFiles/viewbox.dir/drawer.cpp.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/drawer.cpp.o: ../drawer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/viewbox.dir/drawer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/drawer.cpp.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.cpp

CMakeFiles/viewbox.dir/drawer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/drawer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.cpp > CMakeFiles/viewbox.dir/drawer.cpp.i

CMakeFiles/viewbox.dir/drawer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/drawer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.cpp -o CMakeFiles/viewbox.dir/drawer.cpp.s

CMakeFiles/viewbox.dir/drawer.cpp.o.requires:

.PHONY : CMakeFiles/viewbox.dir/drawer.cpp.o.requires

CMakeFiles/viewbox.dir/drawer.cpp.o.provides: CMakeFiles/viewbox.dir/drawer.cpp.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/drawer.cpp.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/drawer.cpp.o.provides

CMakeFiles/viewbox.dir/drawer.cpp.o.provides.build: CMakeFiles/viewbox.dir/drawer.cpp.o


CMakeFiles/viewbox.dir/drawer.h.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/drawer.h.o: ../drawer.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/viewbox.dir/drawer.h.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/drawer.h.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.h

CMakeFiles/viewbox.dir/drawer.h.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/drawer.h.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.h > CMakeFiles/viewbox.dir/drawer.h.i

CMakeFiles/viewbox.dir/drawer.h.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/drawer.h.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/drawer.h -o CMakeFiles/viewbox.dir/drawer.h.s

CMakeFiles/viewbox.dir/drawer.h.o.requires:

.PHONY : CMakeFiles/viewbox.dir/drawer.h.o.requires

CMakeFiles/viewbox.dir/drawer.h.o.provides: CMakeFiles/viewbox.dir/drawer.h.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/drawer.h.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/drawer.h.o.provides

CMakeFiles/viewbox.dir/drawer.h.o.provides.build: CMakeFiles/viewbox.dir/drawer.h.o


CMakeFiles/viewbox.dir/camera_handler.cpp.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/camera_handler.cpp.o: ../camera_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/viewbox.dir/camera_handler.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/camera_handler.cpp.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.cpp

CMakeFiles/viewbox.dir/camera_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/camera_handler.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.cpp > CMakeFiles/viewbox.dir/camera_handler.cpp.i

CMakeFiles/viewbox.dir/camera_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/camera_handler.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.cpp -o CMakeFiles/viewbox.dir/camera_handler.cpp.s

CMakeFiles/viewbox.dir/camera_handler.cpp.o.requires:

.PHONY : CMakeFiles/viewbox.dir/camera_handler.cpp.o.requires

CMakeFiles/viewbox.dir/camera_handler.cpp.o.provides: CMakeFiles/viewbox.dir/camera_handler.cpp.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/camera_handler.cpp.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/camera_handler.cpp.o.provides

CMakeFiles/viewbox.dir/camera_handler.cpp.o.provides.build: CMakeFiles/viewbox.dir/camera_handler.cpp.o


CMakeFiles/viewbox.dir/camera_handler.h.o: CMakeFiles/viewbox.dir/flags.make
CMakeFiles/viewbox.dir/camera_handler.h.o: ../camera_handler.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/viewbox.dir/camera_handler.h.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/viewbox.dir/camera_handler.h.o -c /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.h

CMakeFiles/viewbox.dir/camera_handler.h.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewbox.dir/camera_handler.h.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.h > CMakeFiles/viewbox.dir/camera_handler.h.i

CMakeFiles/viewbox.dir/camera_handler.h.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewbox.dir/camera_handler.h.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/camera_handler.h -o CMakeFiles/viewbox.dir/camera_handler.h.s

CMakeFiles/viewbox.dir/camera_handler.h.o.requires:

.PHONY : CMakeFiles/viewbox.dir/camera_handler.h.o.requires

CMakeFiles/viewbox.dir/camera_handler.h.o.provides: CMakeFiles/viewbox.dir/camera_handler.h.o.requires
	$(MAKE) -f CMakeFiles/viewbox.dir/build.make CMakeFiles/viewbox.dir/camera_handler.h.o.provides.build
.PHONY : CMakeFiles/viewbox.dir/camera_handler.h.o.provides

CMakeFiles/viewbox.dir/camera_handler.h.o.provides.build: CMakeFiles/viewbox.dir/camera_handler.h.o


# Object files for target viewbox
viewbox_OBJECTS = \
"CMakeFiles/viewbox.dir/main.cpp.o" \
"CMakeFiles/viewbox.dir/player.cpp.o" \
"CMakeFiles/viewbox.dir/player.h.o" \
"CMakeFiles/viewbox.dir/drawer.cpp.o" \
"CMakeFiles/viewbox.dir/drawer.h.o" \
"CMakeFiles/viewbox.dir/camera_handler.cpp.o" \
"CMakeFiles/viewbox.dir/camera_handler.h.o"

# External object files for target viewbox
viewbox_EXTERNAL_OBJECTS =

viewbox: CMakeFiles/viewbox.dir/main.cpp.o
viewbox: CMakeFiles/viewbox.dir/player.cpp.o
viewbox: CMakeFiles/viewbox.dir/player.h.o
viewbox: CMakeFiles/viewbox.dir/drawer.cpp.o
viewbox: CMakeFiles/viewbox.dir/drawer.h.o
viewbox: CMakeFiles/viewbox.dir/camera_handler.cpp.o
viewbox: CMakeFiles/viewbox.dir/camera_handler.h.o
viewbox: CMakeFiles/viewbox.dir/build.make
viewbox: /usr/local/lib/libopencv_videostab.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_superres.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_stitching.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_shape.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_photo.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_objdetect.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_hal.a
viewbox: /usr/local/lib/libopencv_calib3d.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_features2d.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_ml.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_highgui.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_videoio.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_imgcodecs.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_flann.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_video.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_imgproc.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_core.3.0.0.dylib
viewbox: /usr/local/lib/libopencv_hal.a
viewbox: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
viewbox: CMakeFiles/viewbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable viewbox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/viewbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/viewbox.dir/build: viewbox

.PHONY : CMakeFiles/viewbox.dir/build

CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/main.cpp.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/player.cpp.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/player.h.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/drawer.cpp.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/drawer.h.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/camera_handler.cpp.o.requires
CMakeFiles/viewbox.dir/requires: CMakeFiles/viewbox.dir/camera_handler.h.o.requires

.PHONY : CMakeFiles/viewbox.dir/requires

CMakeFiles/viewbox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/viewbox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/viewbox.dir/clean

CMakeFiles/viewbox.dir/depend:
	cd /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build /Users/Eplemaskin/Dropbox/Skole/4.klasse/augmentedreality/portal-play/build/CMakeFiles/viewbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/viewbox.dir/depend

