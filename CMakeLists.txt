cmake_minimum_required(VERSION 3.25.1)
project(MOTEUR_INFERENCE LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(moteur_inference
    src/main.cpp

    src/fact/fact.cpp
    src/fact/text_fact.cpp
    src/fact/numeric_fact.cpp
    src/fact/boolean_fact.cpp

    src/utils/fact_factory.cpp
    src/utils/cout.cpp

    src/algos/backwardChainingOutput.cpp
)
target_compile_features(moteur_inference PRIVATE cxx_std_17)
