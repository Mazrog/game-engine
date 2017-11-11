cmake_minimum_required(VERSION 3.8)
set(project_name engine)
project(${project_name})

# Keep threads for later
# find_package( Threads )

find_package( OpenGL )
find_package( GLEW )

set(CMAKE_CXX_STANDARD 14)
set(CXX_FLAGS "-Wall -Wextra")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")

set(SOURCE_FILES
        sample/main.cpp
        src/engine.cpp
        src/display.cpp
        src/controller.cpp
        src/sg.cpp
)

include_directories( include )

add_executable(${project_name} ${SOURCE_FILES})

target_link_libraries(${project_name}
        SDL2
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        # pthread
)