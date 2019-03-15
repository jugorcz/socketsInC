cmake_minimum_required(VERSION 3.13)
project(token_ring C)

set(CMAKE_C_STANDARD 99)

add_executable(token_ring client.c clientTCP.c clientTCP.h clientUDP.c clientUDP.h common.c common.h)