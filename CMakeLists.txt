cmake_minimum_required(VERSION 3.5)

set(CXX_STANDARD 23)

project(KenazEngineGame)

#   Since lib location on Windows is custom, we need
# to indicate it for cmake
#   IMPORTANT: set directory to your own SDL2 and
# SDL2_IMAGE libraries download location
if (WIN32)
    set(SDL2_DIR C:/Libs/SDL/cmake)
    set(SDL2_IMAGE_DIR C:/Libs/SDL_image/cmake)
endif (WIN32)

# Add sub directories
add_subdirectory(Engine)
add_subdirectory(Game)
