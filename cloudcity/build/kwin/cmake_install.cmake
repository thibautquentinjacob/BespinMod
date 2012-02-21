# Install script for directory: /home/thibaut/Downloads/cloudcity/kwin

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
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/kde4/kwin3_bespin.so")
FILE(INSTALL DESTINATION "/usr/lib/kde4" TYPE MODULE FILES "/home/thibaut/Downloads/cloudcity/build/lib/kwin3_bespin.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/kde4/kwin3_bespin.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kde4/apps/kwin/bespin.desktop")
FILE(INSTALL DESTINATION "/usr/share/kde4/apps/kwin" TYPE FILE FILES "/home/thibaut/Downloads/cloudcity/kwin/bespin.desktop")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/kde4/kwin_bespin_config.so")
FILE(INSTALL DESTINATION "/usr/lib/kde4" TYPE MODULE FILES "/home/thibaut/Downloads/cloudcity/build/lib/kwin_bespin_config.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/kde4/kwin_bespin_config.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

