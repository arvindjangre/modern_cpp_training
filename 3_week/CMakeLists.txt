cmake_minimum_required(VERSION 3.10.0)
project(parser VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC_FILES src/*.cpp )
add_executable(parser ${SRC_FILES})

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
find_library(MY_PROTOCOL libprotocol.so)
message(STATUS ${MY_PROTOCOL})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Boost 1.40.0 REQUIRED system)
find_package(Boost COMPONENTS thread system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(LIBS mysqlclient Threads::Threads ${MY_PROTOCOL} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

include(CPack)