cmake_minimum_required(VERSION 3.10)
project(maven)

# Setze den C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Füge Include-Verzeichnisse hinzu
include_directories(include)

# Erstelle die Shared Library
add_library(maven SHARED src/maven.cpp)

# Verlinke die dl-Bibliothek auf Linux
if (UNIX)
    target_link_libraries(maven PRIVATE dl)
endif()