add_library(Common STATIC)
target_include_directories(Common PUBLIC include)
target_link_libraries(Common PUBLIC tomlplusplus::tomlplusplus glm Ethyl Tonic)

include(CMakeSources.cmake)

list(TRANSFORM COMMON_SOURCES PREPEND "source/")
list(TRANSFORM COMMON_HEADERS PREPEND "include/")

target_sources(Common PUBLIC ${COMMON_SOURCES} ${COMMON_HEADERS})
