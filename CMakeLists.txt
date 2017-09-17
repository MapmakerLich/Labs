add_executable(convex main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(convex PUBLIC cxx_std_17)
target_compile_definitions(convex PRIVATE SFML_STATIC)

target_link_libraries(convex ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})