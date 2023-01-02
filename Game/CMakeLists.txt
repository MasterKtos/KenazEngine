project(SDLProject)

find_package(SDL2 REQUIRED)

if(UNIX)
    include_directories(${SDL2_INCLUDE_DIRS}/SDL)
endif()

# Create the executable
add_executable(${PROJECT_NAME} main.cpp Scenes/game.cpp Ball.cpp Ball.h BallManager.cpp BallManager.h Scenes/balls_bouncing.cpp Maze.cpp Maze.h)


# Link the static library from subproject1 using its alias sub::lib1
# Link the header only library from subproject2 using its alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    Engine
    ${SDL2_LIBRARIES}
)
