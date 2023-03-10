cmake_minimum_required(VERSION 3.1.0)

project(ZTextEdit)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_BUILD_TYPE "Debug")

IF (WIN32)
	MESSAGE(STATUS "Now is windows")
	set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\msvc2019_64\\bin")
	set(Qt5_DIR "D:\\Qt\\5.15.2\\msvc2019_64\\lib\\cmake\\Qt5")

	#custom
	set(QT5_PLATFORMS "D:\\Qt\\5.15.2\\msvc2019_64\\plugins\\platforms")
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
get_target_property(QtCore_location Qt5::Widgets LOCATION)


find_package(Qt5 COMPONENTS Core REQUIRED)
get_target_property(QtCore_location Qt5::Core LOCATION)

find_package(Qt5 COMPONENTS Network REQUIRED)
get_target_property(QtCore_location Qt5::Network LOCATION)

find_package(Qt5 COMPONENTS Svg REQUIRED)
get_target_property(QtCore_location Qt5::Svg LOCATION)

add_executable(ZTextEdit
	main.cpp

    #include
    
    #gui
    ./gui/ztextedit.h
    ./gui/ztextedit.cpp
    ./gui/zmainwindow.h
    ./gui/zmainwindow.cpp

    #core
    ./core/ztextblockuserdata.h
    ./core/ztextblockuserdata.cpp
    ./core/zimagetextobject.h
    ./core/zimagetextobject.cpp
    ./core/ztextdocument.h
    ./core/ztextdocument.cpp
)

target_link_libraries(ZTextEdit Qt5::Widgets Qt5::Core Qt5::GuiPrivate Qt5::CorePrivate Qt5::Network Qt5::Svg)

#拷贝对应的dll目录到
file(GLOB QT_DLL "${CMAKE_PREFIX_PATH}/*d.dll")

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory  ${QT5_PLATFORMS} ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/platforms/)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${QT_DLL} ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)

#todo windows copy
add_custom_command(TARGET ${PROJECT_NAME}
  PRE_BUILD 
  COMMAND echo "executing a fake command"
  COMMENT "This command will be executed before building target Test1"
 )
