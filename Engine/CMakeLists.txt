# Set the project name
project (lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# Add a library with the above sources
add_library(${PROJECT_NAME} src/KenazEngine.cpp src/Texture.cpp include/Engine/Texture.h src/Map.cpp include/Engine/Map.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
