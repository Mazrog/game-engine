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

# #################################################################################################
# Library config
set(LIB_SRC
        lib/src/engine.cpp
        lib/src/display.cpp
        lib/src/controller.cpp
        lib/src/gamestate.cpp

        lib/src/scenegraph/scenegraph.cpp
        lib/src/scenegraph/sg_logic.cpp
        lib/src/scenegraph/sg_visual.cpp

        lib/src/rendering/renderer.cpp
        lib/src/rendering/camera.cpp
        lib/src/rendering/program.cpp
)

add_library(
        ${project_name}
        SHARED
        ${LIB_SRC}
)

target_include_directories( ${project_name}
        PRIVATE lib/include
)

target_link_libraries( ${project_name}
        SDL2
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)

# #################################################################################################
# Exec config
set(EXEC_SRC_FILES
        sample/main.cpp

        sample/state/samplestate.cpp

        sample/rendering/simpleRender.cpp
        sample/rendering/renderElement.cpp
)

add_executable(
        ${project_name}_sample
        ${EXEC_SRC_FILES}
)

target_include_directories( ${project_name}_sample
        PRIVATE lib/include
        PRIVATE sample/rendering
        PRIVATE sample/src
        PRIVATE sample/state
)

target_link_libraries( ${project_name}_sample
        engine
)