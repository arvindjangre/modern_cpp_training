file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_SOURCES "../src/*.cpp")
add_library(my_library STATIC ${LIB_SOURCES})


add_executable(server ${TEST_SOURCES})
target_link_libraries(server my_library ${GTEST_LIBRARIES} Threads::Threads GTest::gtest_main GTest::gmock)

add_dependencies(server music_play_list)
gtest_discover_tests(server)