file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_SOURCES "../src/*.cpp")
add_library(my_library STATIC ${LIB_SOURCES})


add_executable(music_play_list_test ${TEST_SOURCES})
target_link_libraries(music_play_list_test my_library ${GTEST_LIBRARIES} Threads::Threads)

add_dependencies(music_play_list_test music_play_list)
gtest_discover_tests(music_play_list_test)