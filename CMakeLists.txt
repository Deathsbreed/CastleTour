cmake_minimum_required(VERSION 2.6)
project(CastleTour)

set(CMAKE_CXX_FLAGS "-Wall -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

find_package(Irrlicht)
if(NOT Irrlicht_FOUND)
	message(FATAL_ERROR "Package Irrlicht is required, but not found!")
endif(NOT Irrlicht_FOUND)

include_directories(
	${IRRLICHT_INCLUDE_DIR}
)

file(GLOB SRCS src/*.cpp)
file(GLOB HDRS src/*.h)

include_directories(${IRRLICHT_INCLUDE_DIR})

add_executable(${CMAKE_PROJECT_NAME}
	${SRCS}
	${HDRS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	${IRRLICHT_LIBRARY}
)
