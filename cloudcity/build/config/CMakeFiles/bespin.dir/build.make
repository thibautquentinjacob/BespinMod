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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thibaut/BespinMod/cloudcity

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thibaut/BespinMod/cloudcity/build

# Include any dependencies generated for this target.
include config/CMakeFiles/bespin.dir/depend.make

# Include the progress variables for this target.
include config/CMakeFiles/bespin.dir/progress.make

# Include the compile flags for this target's objects.
include config/CMakeFiles/bespin.dir/flags.make

config/CMakeFiles/bespin.dir/main.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/main.o: ../config/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/main.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/main.o -c /home/thibaut/BespinMod/cloudcity/config/main.cpp

config/CMakeFiles/bespin.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/main.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/config/main.cpp > CMakeFiles/bespin.dir/main.i

config/CMakeFiles/bespin.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/main.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/config/main.cpp -o CMakeFiles/bespin.dir/main.s

config/CMakeFiles/bespin.dir/main.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/main.o.requires

config/CMakeFiles/bespin.dir/main.o.provides: config/CMakeFiles/bespin.dir/main.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/main.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/main.o.provides

config/CMakeFiles/bespin.dir/main.o.provides.build: config/CMakeFiles/bespin.dir/main.o

config/CMakeFiles/bespin.dir/bconfig.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/bconfig.o: ../config/bconfig.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/bconfig.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/bconfig.o -c /home/thibaut/BespinMod/cloudcity/config/bconfig.cpp

config/CMakeFiles/bespin.dir/bconfig.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/bconfig.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/config/bconfig.cpp > CMakeFiles/bespin.dir/bconfig.i

config/CMakeFiles/bespin.dir/bconfig.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/bconfig.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/config/bconfig.cpp -o CMakeFiles/bespin.dir/bconfig.s

config/CMakeFiles/bespin.dir/bconfig.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/bconfig.o.requires

config/CMakeFiles/bespin.dir/bconfig.o.provides: config/CMakeFiles/bespin.dir/bconfig.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/bconfig.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/bconfig.o.provides

config/CMakeFiles/bespin.dir/bconfig.o.provides.build: config/CMakeFiles/bespin.dir/bconfig.o

config/CMakeFiles/bespin.dir/config.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/config.o: ../config/config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/config.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/config.o -c /home/thibaut/BespinMod/cloudcity/config/config.cpp

config/CMakeFiles/bespin.dir/config.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/config.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/config/config.cpp > CMakeFiles/bespin.dir/config.i

config/CMakeFiles/bespin.dir/config.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/config.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/config/config.cpp -o CMakeFiles/bespin.dir/config.s

config/CMakeFiles/bespin.dir/config.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/config.o.requires

config/CMakeFiles/bespin.dir/config.o.provides: config/CMakeFiles/bespin.dir/config.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/config.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/config.o.provides

config/CMakeFiles/bespin.dir/config.o.provides.build: config/CMakeFiles/bespin.dir/config.o

config/CMakeFiles/bespin.dir/kdeini.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/kdeini.o: ../config/kdeini.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/kdeini.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/kdeini.o -c /home/thibaut/BespinMod/cloudcity/config/kdeini.cpp

config/CMakeFiles/bespin.dir/kdeini.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/kdeini.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/config/kdeini.cpp > CMakeFiles/bespin.dir/kdeini.i

config/CMakeFiles/bespin.dir/kdeini.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/kdeini.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/config/kdeini.cpp -o CMakeFiles/bespin.dir/kdeini.s

config/CMakeFiles/bespin.dir/kdeini.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/kdeini.o.requires

config/CMakeFiles/bespin.dir/kdeini.o.provides: config/CMakeFiles/bespin.dir/kdeini.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/kdeini.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/kdeini.o.provides

config/CMakeFiles/bespin.dir/kdeini.o.provides.build: config/CMakeFiles/bespin.dir/kdeini.o

config/CMakeFiles/bespin.dir/moc_bconfig.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/moc_bconfig.o: config/moc_bconfig.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/moc_bconfig.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/moc_bconfig.o -c /home/thibaut/BespinMod/cloudcity/build/config/moc_bconfig.cxx

config/CMakeFiles/bespin.dir/moc_bconfig.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/moc_bconfig.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/build/config/moc_bconfig.cxx > CMakeFiles/bespin.dir/moc_bconfig.i

config/CMakeFiles/bespin.dir/moc_bconfig.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/moc_bconfig.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/build/config/moc_bconfig.cxx -o CMakeFiles/bespin.dir/moc_bconfig.s

config/CMakeFiles/bespin.dir/moc_bconfig.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/moc_bconfig.o.requires

config/CMakeFiles/bespin.dir/moc_bconfig.o.provides: config/CMakeFiles/bespin.dir/moc_bconfig.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/moc_bconfig.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/moc_bconfig.o.provides

config/CMakeFiles/bespin.dir/moc_bconfig.o.provides.build: config/CMakeFiles/bespin.dir/moc_bconfig.o

config/CMakeFiles/bespin.dir/moc_config.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/moc_config.o: config/moc_config.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/moc_config.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/moc_config.o -c /home/thibaut/BespinMod/cloudcity/build/config/moc_config.cxx

config/CMakeFiles/bespin.dir/moc_config.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/moc_config.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/build/config/moc_config.cxx > CMakeFiles/bespin.dir/moc_config.i

config/CMakeFiles/bespin.dir/moc_config.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/moc_config.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/build/config/moc_config.cxx -o CMakeFiles/bespin.dir/moc_config.s

config/CMakeFiles/bespin.dir/moc_config.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/moc_config.o.requires

config/CMakeFiles/bespin.dir/moc_config.o.provides: config/CMakeFiles/bespin.dir/moc_config.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/moc_config.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/moc_config.o.provides

config/CMakeFiles/bespin.dir/moc_config.o.provides.build: config/CMakeFiles/bespin.dir/moc_config.o

config/CMakeFiles/bespin.dir/moc_dialog.o: config/CMakeFiles/bespin.dir/flags.make
config/CMakeFiles/bespin.dir/moc_dialog.o: config/moc_dialog.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object config/CMakeFiles/bespin.dir/moc_dialog.o"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bespin.dir/moc_dialog.o -c /home/thibaut/BespinMod/cloudcity/build/config/moc_dialog.cxx

config/CMakeFiles/bespin.dir/moc_dialog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bespin.dir/moc_dialog.i"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thibaut/BespinMod/cloudcity/build/config/moc_dialog.cxx > CMakeFiles/bespin.dir/moc_dialog.i

config/CMakeFiles/bespin.dir/moc_dialog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bespin.dir/moc_dialog.s"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thibaut/BespinMod/cloudcity/build/config/moc_dialog.cxx -o CMakeFiles/bespin.dir/moc_dialog.s

config/CMakeFiles/bespin.dir/moc_dialog.o.requires:
.PHONY : config/CMakeFiles/bespin.dir/moc_dialog.o.requires

config/CMakeFiles/bespin.dir/moc_dialog.o.provides: config/CMakeFiles/bespin.dir/moc_dialog.o.requires
	$(MAKE) -f config/CMakeFiles/bespin.dir/build.make config/CMakeFiles/bespin.dir/moc_dialog.o.provides.build
.PHONY : config/CMakeFiles/bespin.dir/moc_dialog.o.provides

config/CMakeFiles/bespin.dir/moc_dialog.o.provides.build: config/CMakeFiles/bespin.dir/moc_dialog.o

config/moc_bconfig.cxx: ../config/bconfig.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_bconfig.cxx"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/moc-qt4 -I/usr/include -I/usr/include/KDE -I/usr/include/qt4/phonon -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtSvg -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtDBus -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/include/qt4/Qt -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -DQT3_SUPPORT -D_BSD_SOURCE -DBESPIN_ARGB_WINDOWS=1 -DVARYING_SHADOWS=1 -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -DQT_NO_STL -DQT_NO_CAST_TO_ASCII -D_REENTRANT -DKDE_DEPRECATED_WARNINGS -DKDE4_CMAKE_TOPLEVEL_DIR_LENGTH=23 -DBLIB_EXPORT=Q_DECL_IMPORT -o /home/thibaut/BespinMod/cloudcity/build/config/moc_bconfig.cxx /home/thibaut/BespinMod/cloudcity/config/bconfig.h

config/moc_config.cxx: ../config/config.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_config.cxx"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/moc-qt4 -I/usr/include -I/usr/include/KDE -I/usr/include/qt4/phonon -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtSvg -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtDBus -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/include/qt4/Qt -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -DQT3_SUPPORT -D_BSD_SOURCE -DBESPIN_ARGB_WINDOWS=1 -DVARYING_SHADOWS=1 -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -DQT_NO_STL -DQT_NO_CAST_TO_ASCII -D_REENTRANT -DKDE_DEPRECATED_WARNINGS -DKDE4_CMAKE_TOPLEVEL_DIR_LENGTH=23 -DBLIB_EXPORT=Q_DECL_IMPORT -o /home/thibaut/BespinMod/cloudcity/build/config/moc_config.cxx /home/thibaut/BespinMod/cloudcity/config/config.h

config/moc_dialog.cxx: ../config/dialog.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_dialog.cxx"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/moc-qt4 -I/usr/include -I/usr/include/KDE -I/usr/include/qt4/phonon -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtSvg -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtDBus -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/include/qt4/Qt -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -DQT3_SUPPORT -D_BSD_SOURCE -DBESPIN_ARGB_WINDOWS=1 -DVARYING_SHADOWS=1 -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -DQT_NO_STL -DQT_NO_CAST_TO_ASCII -D_REENTRANT -DKDE_DEPRECATED_WARNINGS -DKDE4_CMAKE_TOPLEVEL_DIR_LENGTH=23 -DBLIB_EXPORT=Q_DECL_IMPORT -o /home/thibaut/BespinMod/cloudcity/build/config/moc_dialog.cxx /home/thibaut/BespinMod/cloudcity/config/dialog.h

config/ui_config.h: ../config/config.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_config.h"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/uic-qt4 -o /home/thibaut/BespinMod/cloudcity/build/config/ui_config.h /home/thibaut/BespinMod/cloudcity/config/config.ui

config/ui_uiDemo.h: ../config/uiDemo.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thibaut/BespinMod/cloudcity/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_uiDemo.h"
	cd /home/thibaut/BespinMod/cloudcity/build/config && /usr/bin/uic-qt4 -o /home/thibaut/BespinMod/cloudcity/build/config/ui_uiDemo.h /home/thibaut/BespinMod/cloudcity/config/uiDemo.ui

# Object files for target bespin
bespin_OBJECTS = \
"CMakeFiles/bespin.dir/main.o" \
"CMakeFiles/bespin.dir/bconfig.o" \
"CMakeFiles/bespin.dir/config.o" \
"CMakeFiles/bespin.dir/kdeini.o" \
"CMakeFiles/bespin.dir/moc_bconfig.o" \
"CMakeFiles/bespin.dir/moc_config.o" \
"CMakeFiles/bespin.dir/moc_dialog.o"

# External object files for target bespin
bespin_EXTERNAL_OBJECTS =

config/bespin: config/CMakeFiles/bespin.dir/main.o
config/bespin: config/CMakeFiles/bespin.dir/bconfig.o
config/bespin: config/CMakeFiles/bespin.dir/config.o
config/bespin: config/CMakeFiles/bespin.dir/kdeini.o
config/bespin: config/CMakeFiles/bespin.dir/moc_bconfig.o
config/bespin: config/CMakeFiles/bespin.dir/moc_config.o
config/bespin: config/CMakeFiles/bespin.dir/moc_dialog.o
config/bespin: /usr/lib/i386-linux-gnu/libQtCore.so
config/bespin: /usr/lib/i386-linux-gnu/libQtGui.so
config/bespin: config/CMakeFiles/bespin.dir/build.make
config/bespin: config/CMakeFiles/bespin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bespin"
	cd /home/thibaut/BespinMod/cloudcity/build/config && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bespin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
config/CMakeFiles/bespin.dir/build: config/bespin
.PHONY : config/CMakeFiles/bespin.dir/build

config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/main.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/bconfig.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/config.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/kdeini.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/moc_bconfig.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/moc_config.o.requires
config/CMakeFiles/bespin.dir/requires: config/CMakeFiles/bespin.dir/moc_dialog.o.requires
.PHONY : config/CMakeFiles/bespin.dir/requires

config/CMakeFiles/bespin.dir/clean:
	cd /home/thibaut/BespinMod/cloudcity/build/config && $(CMAKE_COMMAND) -P CMakeFiles/bespin.dir/cmake_clean.cmake
.PHONY : config/CMakeFiles/bespin.dir/clean

config/CMakeFiles/bespin.dir/depend: config/moc_bconfig.cxx
config/CMakeFiles/bespin.dir/depend: config/moc_config.cxx
config/CMakeFiles/bespin.dir/depend: config/moc_dialog.cxx
config/CMakeFiles/bespin.dir/depend: config/ui_config.h
config/CMakeFiles/bespin.dir/depend: config/ui_uiDemo.h
	cd /home/thibaut/BespinMod/cloudcity/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thibaut/BespinMod/cloudcity /home/thibaut/BespinMod/cloudcity/config /home/thibaut/BespinMod/cloudcity/build /home/thibaut/BespinMod/cloudcity/build/config /home/thibaut/BespinMod/cloudcity/build/config/CMakeFiles/bespin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : config/CMakeFiles/bespin.dir/depend

