IF(VEYON_BUILD_WIN32)
ADD_SUBDIRECTORY(windows)
ENDIF()

IF(VEYON_BUILD_LINUX)
ADD_SUBDIRECTORY(linux)
ENDIF()

IF(VEYON_BUILD_APPLE)
ADD_SUBDIRECTORY(osx)
ENDIF()
