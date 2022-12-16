cmake_minimum_required(VERSION 3.10.0)
project(arbitrary_precision_calc VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE SRC_FILES src/*.cpp )
add_executable(arbitrary_precision_calc ${SRC_FILES})

set(JSON_BuildTests OFF CACHE INTERNAL "")

#target_link_libraries(arbitrary_precision_calc csv)

target_include_directories(arbitrary_precision_calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${CSV_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${LIBS})

include(CPack)