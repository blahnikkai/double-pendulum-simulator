cmake_minimum_required(VERSION 3.25)
project(PendulumSimulator)

set(CMAKE_CXX_STANDARD 17)
add_executable(main src/main.cpp src/pendulum.cpp src/simulation.cpp src/util.cpp src/resource_manager.cpp src/number_field.cpp src/double_pendulum.cpp src/image_button.cpp src/button.cpp)

target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
