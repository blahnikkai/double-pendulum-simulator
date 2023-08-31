cmake_minimum_required(VERSION 3.25)
project(PendulumSimulator)

set(CMAKE_CXX_STANDARD 17)
add_executable(main main.cpp pendulum.cpp simulation.cpp util.cpp resource_manager.cpp text_field.cpp double_pendulum.cpp image_button.cpp text_button.cpp button.cpp)

target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
