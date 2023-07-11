cmake_minimum_required(VERSION 3.1)

project(GraphicLibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)

file(GLOB glib_SRC "Library/*/*.cpp")
file(GLOB glib_LIB "Library/*/*.hpp")

file(GLOB children "Library/*")
set(dirlist "")
foreach(child ${children})
  if(IS_DIRECTORY ${curdir}/${child})
    list(APPEND dirlist ${child})
  endif()
endforeach()

add_library(glib ${glib_SRC} ${glib_HPP})
target_include_directories(glib PUBLIC ${dirlist} Library/)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(glib PUBLIC sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()
