cmake_minimum_required(VERSION 3.19)
project(RegularExpr VERSION 1.0 LANGUAGES CXX)

set(OUTPUT_NAME RegularExpr)
set(MYLIB_PATH ${PROJECT_SOURCE_DIR}/SecondFunk)
set(HEADERS wordSearch/wordSearch.h
			${MYLIB_PATH}/SecondaryFunction.h)
set(SOURCES main.cpp
			wordSearch/wordSearch.cpp
			${MYLIB_PATH}/SecondaryFunction.cpp)
# C/C++: доп. каталоги включаемых файлов (#include)
include_directories(${PROJECT_SOURCE_DIR}/wordSearch
					${MYLIB_PATH})

# Boost:
# Компоновщик: доп. каталоги библиотек
link_directories($ENV{BOOST_ROOT}/lib)
find_package(Boost 1.80.0 REQUIRED)
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Could not find Boost")
endif()

add_executable(${OUTPUT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${OUTPUT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${OUTPUT_NAME} PRIVATE ${Boost_LIBRARIES})

#[[ if (Visual Studio)
	настраиваю в качестве запускаемого проекта
	настройка на стандарт с++17 ]]
if(MSVC)
add_compile_definitions(_WIN32_WINNT=0x0601)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${OUTPUT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
