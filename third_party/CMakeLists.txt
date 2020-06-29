cmake_minimum_required(VERSION 3.1)

set(ASIO_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/asio/asio")

add_library(asio INTERFACE)

target_include_directories(asio INTERFACE "${ASIO_SOURCE_DIR}/include")

