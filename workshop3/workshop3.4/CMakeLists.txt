add_executable(workshop3.4 main.cpp main.hpp ship.cpp ship.hpp)

target_include_directories(workshop3.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3.4 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.4 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})