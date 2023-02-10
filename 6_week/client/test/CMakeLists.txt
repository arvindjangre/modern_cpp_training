file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_SOURCES "../src/*.cpp")
add_library(client_library STATIC ${LIB_SOURCES})


add_executable(client_test ${TEST_SOURCES})
target_link_libraries(client_test client_library ${GTEST_LIBRARIES} Threads::Threads GTest::gtest_main GTest::gmock)

add_dependencies(client_test client)
gtest_discover_tests(client_test)