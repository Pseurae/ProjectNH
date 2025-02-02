include(FetchContent)

FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY "https://github.com/marzer/tomlplusplus"
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(tomlplusplus)

FetchContent_Declare(nfd-extended
    GIT_REPOSITORY "https://github.com/btzy/nativefiledialog-extended"
    GIT_TAG v1.2.1
)

FetchContent_MakeAvailable(nfd-extended)

set(CAULDRON_TESTS_ENABLED OFF)
add_subdirectory(Cauldron)

add_subdirectory(stb_image)
add_subdirectory(imgui)
