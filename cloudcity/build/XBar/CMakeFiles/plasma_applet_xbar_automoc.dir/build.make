# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thibaut/BespinMod/cloudcity

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thibaut/BespinMod/cloudcity/build

# Utility rule file for plasma_applet_xbar_automoc.

XBar/CMakeFiles/plasma_applet_xbar_automoc:
	cd /home/thibaut/BespinMod/cloudcity/build/XBar && /usr/bin/automoc4 /home/thibaut/BespinMod/cloudcity/build/XBar/plasma_applet_xbar_automoc.cpp /home/thibaut/BespinMod/cloudcity/XBar /home/thibaut/BespinMod/cloudcity/build/XBar /usr/bin/moc-qt4 /usr/bin/cmake

plasma_applet_xbar_automoc: XBar/CMakeFiles/plasma_applet_xbar_automoc
plasma_applet_xbar_automoc: XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/build.make
.PHONY : plasma_applet_xbar_automoc

# Rule to build all files generated by this target.
XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/build: plasma_applet_xbar_automoc
.PHONY : XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/build

XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/clean:
	cd /home/thibaut/BespinMod/cloudcity/build/XBar && $(CMAKE_COMMAND) -P CMakeFiles/plasma_applet_xbar_automoc.dir/cmake_clean.cmake
.PHONY : XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/clean

XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/depend:
	cd /home/thibaut/BespinMod/cloudcity/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thibaut/BespinMod/cloudcity /home/thibaut/BespinMod/cloudcity/XBar /home/thibaut/BespinMod/cloudcity/build /home/thibaut/BespinMod/cloudcity/build/XBar /home/thibaut/BespinMod/cloudcity/build/XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : XBar/CMakeFiles/plasma_applet_xbar_automoc.dir/depend

