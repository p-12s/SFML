add_executable(ws1.2.0 main.cpp)

target_include_directories(ws1.2.0 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws1.2.0 PUBLIC cxx_std_17)
target_compile_definitions(ws1.2.0 PRIVATE SFML_STATIC)

target_link_libraries(ws1.2.0 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})