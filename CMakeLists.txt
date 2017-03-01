cmake_minimum_required(VERSION 2.6)
project(gamejam)

add_executable(gamejam main.cpp)

install(TARGETS gamejam RUNTIME DESTINATION bin)
