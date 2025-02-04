# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

set (CMAKE_CXX_STANDARD 23)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

file(GLOB helloworld_SRC
     "*.h"
     "*.cpp"
)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(CMakeProject1 ${helloworld_SRC})

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
