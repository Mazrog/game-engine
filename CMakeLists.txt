cmake_minimum_required(VERSION 3.8)
set(project_name engine)
project(${project_name})

# Keep threads for later
# find_package( Threads )

find_package( OpenGL )
find_package( GLEW )
find_package( glfw3 )

set(CMAKE_CXX_STANDARD 14)
set(CXX_FLAGS "-Wall -Wextra")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")

# #################################################################################################
# Library config
#                       ENGINE
set(LIB_SRC
        lib_engine/src/engine.cpp
        lib_engine/src/display.cpp
        lib_engine/src/controller.cpp
        lib_engine/src/gamestate.cpp
        lib_engine/src/utils.cpp

        lib_engine/src/scenegraph/scenegraph.cpp
        lib_engine/src/scenegraph/sg_logic.cpp
        lib_engine/src/scenegraph/sg_visual.cpp

        lib_engine/src/rendering/renderer.cpp
        lib_engine/src/rendering/camera.cpp
        lib_engine/src/rendering/light.cpp
        lib_engine/src/rendering/program.cpp
        lib_engine/src/rendering/texture.cpp
        lib_engine/src/rendering/model.cpp

        lib_engine/src/rendering/structs/uniform.cpp
        lib_engine/src/rendering/structs/ssbuffer.cpp
        lib_engine/src/rendering/structs/vao.cpp
        lib_engine/src/rendering/structs/vbo.cpp

        lib_engine/src/events/mouse.cpp
        lib_engine/src/events/keyboard.cpp

        lib_engine/src/gui/gui.cpp
        lib_engine/src/gui/guiManager.cpp
        lib_engine/src/gui/text.cpp
        lib_engine/src/gui/guiData.cpp
        lib_engine/src/gui/guiRender.cpp
        lib_engine/src/gui/textRender.cpp

        lib_engine/src/gui/elements/guibox.cpp
        lib_engine/src/gui/elements/textblock.cpp
        lib_engine/src/gui/elements/table.cpp
)

add_library(
        ${project_name}
        SHARED
        ${LIB_SRC}
)

target_include_directories( ${project_name}
        PRIVATE lib_engine/include
        PRIVATE lib_geom/include
        PUBLIC /usr/include/freetype2
)

target_link_libraries( ${project_name}
        ${GLFW3_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        IL
        freetype
        jsoncpp
)
# ####################################################
#                       GEOMETRY
set(LIB_GEOM_SRC
        lib_geom/src/base.cpp
        lib_geom/src/vector_utils.cpp
)

add_library(
        geom
        SHARED
        ${LIB_GEOM_SRC}
)

target_include_directories( geom
        PRIVATE lib_geom/include
)

# #################################################################################################
# Exec config
set(EXEC_SRC_FILES
        sample/main.cpp
        sample/src/terrain.cpp
        sample/src/character.cpp
        sample/src/skybox.cpp

        sample/src/gui/characterPanel.cpp

        sample/rendering/renderEntity.cpp
        sample/rendering/terrainRender.cpp
        sample/rendering/skyboxRender.cpp
)

add_executable(
        ${project_name}_sample
        ${EXEC_SRC_FILES}
)

target_include_directories( ${project_name}_sample
        PRIVATE lib_engine/include
        PRIVATE lib_geom/include

        PRIVATE sample/rendering
        PRIVATE sample/src
)

target_link_libraries( ${project_name}_sample
        engine
        geom
)