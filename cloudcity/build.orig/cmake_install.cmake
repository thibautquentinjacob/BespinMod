# Install script for directory: /home/thibaut/BespinMod/cloudcity

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so")
FILE(INSTALL DESTINATION "/usr/lib/i386-linux-gnu/qt4/plugins/styles" TYPE SHARED_LIBRARY FILES "/home/thibaut/BespinMod/cloudcity/build/lib/libbespin.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/i386-linux-gnu/qt4/plugins/styles/libbespin.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kde4/apps/kstyle/themes/bespin.themerc")
FILE(INSTALL DESTINATION "/usr/share/kde4/apps/kstyle/themes" TYPE FILE FILES "/home/thibaut/BespinMod/cloudcity/bespin.themerc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/thibaut/BespinMod/cloudcity/build/blib/cmake_install.cmake")
  INCLUDE("/home/thibaut/BespinMod/cloudcity/build/config/cmake_install.cmake")
  INCLUDE("/home/thibaut/BespinMod/cloudcity/build/kwin/cmake_install.cmake")
  INCLUDE("/home/thibaut/BespinMod/cloudcity/build/XBar/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/thibaut/BespinMod/cloudcity/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/thibaut/BespinMod/cloudcity/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
