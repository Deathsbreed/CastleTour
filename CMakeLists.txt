cmake_minimum_required(VERSION 2.6)
project(CastleTour)

set(CMAKE_CXX_FLAGS "-Wall -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(X11)
if(NOT X11_FOUND)
	message(FATAL_ERROR "Package X11 is required, but not found!")
endif(NOT X11_FOUND)

find_package(GLUT)
if(NOT GLUT_FOUND)
	message(FATAL_ERROR "Package OpenGL is required, but not found!")
endif(NOT GLUT_FOUND)

find_package(ZLIB)
if(NOT ZLIB_FOUND)
	message(FATAL_ERROR "Package zlib is required, but not found!")
endif(NOT ZLIB_FOUND)

find_package(Irrlicht)
if(NOT Irrlicht_FOUND)
	message(FATAL_ERROR "Package Irrlicht is required, but not found!")
endif(NOT Irrlicht_FOUND)

include_directories(
	${IRRLICHT_INCLUDE_DIR}
	${X11_INCLUDE_DIR}
	${GLUT_INCLUDE_DIR}
	${ZLIB_INCLUDE_DIR}
)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS src/*.h)

add_executable(${CMAKE_PROJECT_NAME}
	${SRCS}
	${HDRS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	${X11_LIBRARIES}
	${GLUT_LIBRARIES}
	${ZLIB_LIBRARIES}
	${IRRLICHT_LIBRARY}
)
