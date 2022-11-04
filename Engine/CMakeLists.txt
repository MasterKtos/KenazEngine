# Set the project name
project (Engine)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

add_library(${PROJECT_NAME}
        src/KenazEngine.cpp include/Engine/KenazEngine.h
        src/Texture.cpp include/Engine/Texture.h
        src/Map.cpp include/Engine/Map.h)

if (WIN32)
    set(SDL2_IMAGE_LIBRARIES SDL2_image::SDL2_image)
else()
    set(SDL2_IMAGE_LIBRARIES SDL2_image)
endif (WIN32)


target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
)