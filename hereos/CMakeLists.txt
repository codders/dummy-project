cmake_minimum_required(VERSION 2.8.9)
include (grpc.cmake.inc)

# Proto file
get_filename_component(echo_proto "echo.proto" ABSOLUTE)
get_filename_component(echo_proto_path "${echo_proto}" PATH)
get_filename_component(ingestion_proto "ingestion.proto" ABSOLUTE)
get_filename_component(ingestion_proto_path "${ingestion_proto}" PATH)

# Generated sources
set(echo_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.cc")
set(echo_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.h")
set(echo_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.cc")
set(echo_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.h")
add_custom_command(
      OUTPUT "${echo_proto_srcs}" "${echo_proto_hdrs}" "${echo_grpc_srcs}" "${echo_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${echo_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${echo_proto}"
      DEPENDS "${echo_proto}")

set(ingestion_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/ingestion.pb.cc")
set(ingestion_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/ingestion.pb.h")
set(ingestion_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/ingestion.grpc.pb.cc")
set(ingestion_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/ingestion.grpc.pb.h")
add_custom_command(
      OUTPUT "${ingestion_proto_srcs}" "${ingestion_proto_hdrs}" "${ingestion_grpc_srcs}" "${ingestion_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${ingestion_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${ingestion_proto}"
      DEPENDS "${ingestion_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

add_library(hereos_echo echo.cc ${echo_proto_srcs} ${echo_grpc_srcs})
add_library(hereos_ingestion ingestion.cc ${ingestion_proto_srcs} ${ingestion_grpc_srcs})
