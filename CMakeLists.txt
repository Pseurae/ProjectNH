cmake_minimum_required(VERSION 3.5)
project(ProjectNH)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_subdirectory(ThirdParty)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(Engine)
