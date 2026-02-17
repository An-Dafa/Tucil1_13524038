cmake_minimum_required(VERSION 3.10)
project(QueensSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(solver
    src/main.cpp
    src/core/board.cpp
    src/core/solve.cpp
    src/utils/file_utils.cpp
    src/utils/tinyfiledialogs.c 
)

target_link_libraries(solver
    raylib 
    opengl32 
    gdi32 
    winmm 
    comdlg32 
    ole32
)