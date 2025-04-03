cmake_minimum_required(VERSION 3.10)
project(glfeur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp)

# Add cpp files
add_library(stb_image third-party/stb_image.cpp)
add_library(glfeur ${SRC_FILES})

# Add hpp files
target_include_directories(glfeur PUBLIC src third-party)
target_link_libraries(glfeur PRIVATE stb_image)

# ---Add glm---
#target_include_directories(glfeur PUBLIC third-party/glm)
add_subdirectory(third-party/glm)
target_link_libraries(glfeur PUBLIC glm)

# Add quick_imgui for glad
target_link_libraries(glfeur PUBLIC quick_imgui)

