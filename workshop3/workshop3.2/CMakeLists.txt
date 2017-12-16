add_executable(workshop3.2 main.cpp main.hpp)

target_include_directories(workshop3.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(workshop3.2 PUBLIC cxx_std_17)
target_compile_definitions(workshop3.2 PRIVATE SFML_STATIC)

target_link_libraries(workshop3.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})