add_executable(ws3.3 main.cpp tank.h tank.cpp bomb.h bomb.cpp bullet.h bullet.cpp gamescene.h gamescene.cpp utils.h utils.cpp constants.h)

target_include_directories(ws3.3 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(ws3.3 PUBLIC cxx_std_17)
target_compile_definitions(ws3.3 PRIVATE SFML_STATIC)

target_link_libraries(ws3.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})