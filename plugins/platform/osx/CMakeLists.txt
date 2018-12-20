# ADD_SUBDIRECTORY(auth-helper)

FIND_PACKAGE(Qt5DBus REQUIRED)
FIND_PACKAGE(PkgConfig QUIET)

INCLUDE(BuildPlugin)

BUILD_PLUGIN(osx-platform
	OsXPlatformPlugin.cpp
	OsXCoreFunctions.cpp
	OsXFilesystemFunctions.cpp
	OsXInputDeviceFunctions.cpp
	OsXNetworkFunctions.cpp
	OsXServiceCore.cpp
	OsXServiceFunctions.cpp
	OsXUserFunctions.cpp
	OsXPlatformPlugin.h
	OsXCoreFunctions.h
	OsXDesktopIntegration.h
	OsXFilesystemFunctions.h
	OsXInputDeviceFunctions.h
	OsXKeyboardShortcutTrapper.h
	OsXNetworkFunctions.h
	OsXServiceCore.h
	OsXServiceFunctions.h
	OsXUserFunctions.h
)

TARGET_LINK_LIBRARIES(osx-platform
	Qt5::DBus
	)
