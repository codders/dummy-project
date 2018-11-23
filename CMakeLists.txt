cmake_minimum_required(VERSION 2.8.9)
project (hello-world)

add_subdirectory("hereos")

include (hereos/grpc.cmake.inc)

include_directories("${GRPC_INCLUDES}")

add_executable(hello-world main.cpp)
target_link_libraries(hello-world hereos_echo hereos_ingestion ${GRPC_LIBS})
