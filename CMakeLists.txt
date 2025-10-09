cmake_minimum_required(VERSION 3.28)
project(MOTEUR_INFERENCE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(moteur_inference
    src/main.cpp

    # src/class/fact.cpp
    # src/class/rule.cpp
)
target_compile_features(moteur_inference PRIVATE cxx_std_17)
