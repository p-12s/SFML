add_executable(ws3.0.2 main.cpp packman.h packman.cpp field.h field.cpp)

target_include_directories(ws3.0.2 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws3.0.2 PUBLIC cxx_std_17)
target_compile_definitions(ws3.0.2 PRIVATE SFML_STATIC)

target_link_libraries(ws3.0.2 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})