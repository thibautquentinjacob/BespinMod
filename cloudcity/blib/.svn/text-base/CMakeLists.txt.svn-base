project(QtBespin)

add_definitions( ${QT_DEFINITIONS} )

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules )

find_package(X11)

# add_definitions (-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII)

set (QT_MIN_VERSION "4.3.0")
find_package (Qt4 REQUIRED)
include (UseQt4)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions ( -DBLIB_EXPORT=Q_DECL_EXPORT )

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

set (QtBespin_SOURCES colors.cpp dpi.cpp elements.cpp FX.cpp gradients.cpp shapes.cpp tileset.cpp shadows.cpp)

if ( X11_FOUND )
    set (QtBespin_SOURCES ${QtBespin_SOURCES} xproperty.cpp)
endif ( X11_FOUND )

if (X11_Xrender_FOUND)
   message (STATUS "INFO: XRender was found - kwin deco & FX via GPU available!")
endif (X11_Xrender_FOUND)

add_library (QtBespin SHARED ${QtBespin_SOURCES})


target_link_libraries(QtBespin  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

if ( X11_FOUND )
    target_link_libraries(QtBespin ${X11_LIBRARIES})
endif( X11_FOUND )
if (X11_Xrender_FOUND)
    target_link_libraries(QtBespin ${X11_Xrender_LIB})
endif (X11_Xrender_FOUND)

install (TARGETS QtBespin LIBRARY DESTINATION ${LIB_INSTALL_DIR})
