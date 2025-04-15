cmake_minimum_required(VERSION 3.30)
project(bayes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG e814b5f
)

FetchContent_MakeAvailable(fmt)

include_directories(include)

add_executable(bayes src/main.cpp
        src/NaiveBayesClassifier.cpp
        src/NaiveBayesUtils.cpp)
target_link_libraries(bayes PRIVATE fmt::fmt)

