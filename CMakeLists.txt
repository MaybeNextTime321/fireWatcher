cmake_minimum_required(VERSION 4.2.3)

project(FileWatcher)
set(CMAKE_CXX_STANDARD 17) 

include(FetchContent)

FetchContent_Declare(
  RapidJSON
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG "v3.12.0"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
  SYSTEM
)

include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/build/_deps/rapidjson-src/include/)
link_directories(${CMAKE_SOURCE_DIR}/build/_deps/rapidjson-src/include/)




add_executable(FireWatcher src/main.cpp 
src/core/FileScanner.h src/core/FileScanner.cpp 
src/core/LangChecker.h src/core/LangChecker.cpp
src/core/JsonIdChecker.h src/core/JsonIdChecker.cpp)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FireWatcher)
FetchContent_MakeAvailable(RapidJSON)
