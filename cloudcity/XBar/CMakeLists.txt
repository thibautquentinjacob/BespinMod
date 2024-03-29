project(plasma-xbar)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include(MacroOptionalAddSubdirectory)

if (KDE_VERSION_MINOR LESS 2 AND KDE_VERSION_RELEASE LESS 96)
    message("(Harmless) note:\nYou're about to compile for the unstable Plasma ABI.\nUse KDE4.2 or above if you want this to be binary compatible for future releases\n\n")
    find_package(Plasma REQUIRED)
endif()

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PLASMA_INCLUDE_DIR})

set(xbar_SRCS menubar.cpp xbar.cpp)

kde4_add_plugin(plasma_applet_xbar ${xbar_SRCS})
if (KDE_VERSION_MINOR LESS 2 AND KDE_VERSION_RELEASE LESS 96)
    target_link_libraries(plasma_applet_xbar kworkspace ${KDE4_KDEUI_LIBS} ${KDE4_KFILE_LIBS} ${PLASMA_LIBS} QtXml ${KDE4_KIO_LIBS} X11 )
else()
    target_link_libraries(plasma_applet_xbar kworkspace ${KDE4_KDEUI_LIBS} ${KDE4_KFILE_LIBS} ${KDE4_PLASMA_LIBS} QtXml ${KDE4_KIO_LIBS} X11 )
endif()

install(TARGETS plasma_applet_xbar DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-applet-xbar.desktop DESTINATION ${SERVICES_INSTALL_DIR})
