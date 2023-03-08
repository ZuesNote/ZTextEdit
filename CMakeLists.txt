cmake_minimum_required(VERSION 3.1.0)

project(ZTextEdit)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_BUILD_TYPE "Debug")

IF (WIN32)
	MESSAGE(STATUS "Now is windows")
	set(CMAKE_PREFIX_PATH "D:\\Qt\\6.4.1\\msvc2019_64\\bin")

	#custom
	set(QT6_PLATFORMS "D:\\Qt\\6.4.1\\msvc2019_64\\plugins\\platforms")
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()


find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Svg)

qt_standard_project_setup()

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

target_link_libraries(ZTextEdit Qt6::Widgets Qt6::Core Qt6::GuiPrivate Qt6::CorePrivate Qt6::Network Qt6::Svg)

#拷贝对应的dll目录到
file(GLOB QT_DLL "${CMAKE_PREFIX_PATH}/*d.dll")

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory  ${Qt6_PLATFORMS} ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/platforms/)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${QT_DLL} ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)

#todo windows copy
add_custom_command(TARGET ${PROJECT_NAME}
  PRE_BUILD 
  COMMAND echo "executing a fake command"
  COMMENT "This command will be executed before building target Test1"
 )
