@echo off

if not exist Build/build.ninja (
cmake -GNinja -B Build .
)

cd Build

cmake --build .