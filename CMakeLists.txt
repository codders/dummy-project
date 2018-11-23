cmake_minimum_required(VERSION 2.8.9)
project (hello-world)

add_subdirectory("hereos")

add_executable(hello-world main.cpp)
target_link_libraries(hello-world hereos_echo hereos_ingestion)
