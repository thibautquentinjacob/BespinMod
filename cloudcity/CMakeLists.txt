project(bespin)
cmake_minimum_required(VERSION 2.4)

add_definitions( ${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} -DQT3_SUPPORT )

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules )

option(ENABLE_ARGB "Enable translucent windows" ON)
option(ENABLE_KDE "Enable Bespin support for KDE4" ON)
option(ENABLE_KWIN "Build Bespin KWin decoration" ON)
option(ENABLE_XBAR "Enable the XBar plasmoid (Mac-Alike-Menubar)" ON)
option(ENABLE_474_SHADOWS "Enable shadows with variable pixmap size (requires KWin >= 4.7.4)" ON)

if (ENABLE_KDE)
    find_package(KDE4)
endif (ENABLE_KDE)

if (ENABLE_ARGB)
    message (STATUS "WARNING: *** ARGB windows are experimental, performance might suffer ***")
    add_definitions ( -DBESPIN_ARGB_WINDOWS=1 )
else (ENABLE_ARGB)
    add_definitions ( -DBESPIN_ARGB_WINDOWS=0 )
endif (ENABLE_ARGB)

if (ENABLE_474_SHADOWS)
    message (STATUS "WARNING: *** Variable shadow pixmap sizes will cause glitches on KWin < 4.7.4 and OpenGL ***")
    add_definitions ( -DVARYING_SHADOWS=1 )
else (ENABLE_474_SHADOWS)
    add_definitions ( -DVARYING_SHADOWS=0 )
endif (ENABLE_474_SHADOWS)

find_package(X11)

# add_definitions (-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII)

if (KDE4_FOUND)
   include (KDE4Defaults)
   include (MacroLibrary)
   add_definitions ( ${KDE4_DEFINITIONS} )
   include_directories (${KDE4_INCLUDES})
else (KDE4_FOUND)
   message (STATUS "WARNING: *** KDE4 not found, just the style will be built ***")
   set (QT_MIN_VERSION "4.4.0")
   find_package (Qt4 REQUIRED)
   include (UseQt4)
   set (CMAKE_INCLUDE_CURRENT_DIR ON)
endif (KDE4_FOUND)

add_subdirectory (blib)

add_definitions ( -DBLIB_EXPORT=Q_DECL_IMPORT )

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

# set (bespin_SOURCES animator/basic.cpp animator/aprogress.cpp animator/hover.cpp
# animator/hoverindex.cpp animator/hovercomplex.cpp animator/tab.cpp
# bespin.cpp buttons.cpp docks.cpp frames.cpp genpixmaps.cpp hacks.cpp init.cpp
# input_ng.cpp macmenu.cpp menus.cpp pixelmetric_ng.cpp polish.cpp progress_ng.cpp qsubcmetrics_ng.cpp
# scrollareas_ng.cpp indicators.cpp sizefromcontents.cpp slider_ng.cpp stdpix.cpp stylehint.cpp
# tabbing_ng.cpp toolbars.cpp views.cpp visualframe.cpp window.cpp )

set (bespin_SOURCES animator/basic.cpp animator/aprogress.cpp animator/hover.cpp
animator/hoverindex.cpp animator/hovercomplex.cpp animator/tab.cpp
bespin.cpp buttons.cpp docks.cpp frames.cpp genpixmaps.cpp hacks.cpp init.cpp
input.cpp macmenu.cpp menus.cpp pixelmetric.cpp polish.cpp progress.cpp qsubcmetrics.cpp
scrollareas.cpp indicators.cpp sizefromcontents.cpp slider.cpp stdpix.cpp stylehint.cpp
tabbing.cpp toolbars.cpp views.cpp visualframe.cpp window.cpp )

# if ( X11_FOUND )
#     set (bespin_SOURCES ${bespin_SOURCES} lib/xproperty.cpp)
# endif ( X11_FOUND )

set (bespin_MOC_HDRS animator/basic.h animator/aprogress.h animator/hover.h
animator/hoverindex.h animator/tab.h
bespin.h visualframe.h hacks.h macmenu.h macmenu-dbus.h)
qt4_wrap_cpp(bespin_MOC_SRCS ${bespin_MOC_HDRS})

add_library (bespin SHARED ${bespin_SOURCES} ${bespin_MOC_SRCS})


target_link_libraries(bespin QtBespin ${QT_QTDBUS_LIBRARY} ${QT_QT3SUPPORT_LIBRARY})
if ( X11_FOUND )
   target_link_libraries(bespin ${X11_LIBRARIES})
endif( X11_FOUND )
if (X11_Xrender_FOUND)
   target_link_libraries(bespin ${X11_Xrender_LIB})
endif (X11_Xrender_FOUND)

install (TARGETS bespin LIBRARY DESTINATION ${QT_PLUGINS_DIR}/styles)

add_subdirectory (config)

if (KDE4_FOUND)
    install (FILES bespin.themerc DESTINATION ${DATA_INSTALL_DIR}/kstyle/themes)
    if (X11_Xrender_FOUND)
        if(ENABLE_KWIN)
            add_subdirectory (kwin)
        else(ENABLE_KWIN)
            message (STATUS "WARNING: *** KWin decoration will not be built ***")
        endif(ENABLE_KWIN)
    endif (X11_Xrender_FOUND)
    if ( X11_FOUND )
        if(ENABLE_XBAR)
            add_subdirectory (XBar)
        else(ENABLE_XBAR)
            message (STATUS "WARNING: *** XBar plasmoid will not be built ***")
        endif(ENABLE_XBAR)
    endif ( X11_FOUND )
endif (KDE4_FOUND)
