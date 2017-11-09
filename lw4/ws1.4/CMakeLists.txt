add_executable(ws1.4 main.cpp)

target_include_directories(ws1.4 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws1.4 PUBLIC cxx_std_17)
target_compile_definitions(ws1.4 PRIVATE SFML_STATIC)

target_link_libraries(ws1.4 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})