cmake_minimum_required(VERSION 3.17)
project(TestProj)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH "/usr/include/tmxlite/cmake/modules/")

# Find packages we're using in the project
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(Boost 1.75.0 COMPONENTS filesystem REQUIRED )
find_package(TMXLITE 1.2.1 REQUIRED)

#Log the versions of the boost libraries we have
message("Found SFML Version - @${SFML_VERSION}")
message("Found Boost Version - @${Boost_VERSION}")
message("Found TMXLite Version - @${TMXLITE_VERSION}")

# Add executables
add_executable(TestProj main.cpp core/Game.hpp core/Rendering/Renderer.hpp core/Rendering/AssetLoader.hpp)

# Link libraries
target_link_libraries(TestProj sfml-graphics sfml-audio Boost::filesystem ${TMXLITE_LIBRARIES})