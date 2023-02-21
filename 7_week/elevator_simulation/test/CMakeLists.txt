file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE LIB_SOURCES "../src/*.cpp")
add_library(my_lib STATIC ${LIB_SOURCES})


add_executable(elevator_simulation_test ${TEST_SOURCES})
target_link_libraries(elevator_simulation_test my_lib ${GTEST_LIBRARIES} Threads::Threads GTest::gtest_main GTest::gmock)

add_dependencies(elevator_simulation_test elevator_simulation)
gtest_discover_tests(elevator_simulation_test)