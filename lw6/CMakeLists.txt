cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sfml-lab-6)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

# add_subdirectory(ws3.0.0)
# add_subdirectory(ws3.0.1)
# add_subdirectory(ws3.0.2)
# add_subdirectory(ws3.0.3)
# add_subdirectory(ws3.0.4)
# add_subdirectory(ws3.0.5)
#add_subdirectory(ws3.1)
#add_subdirectory(ws3.2)
add_subdirectory(ws3.3)
add_subdirectory(ws3.4)