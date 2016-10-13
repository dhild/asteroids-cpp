include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

cxx_test(player_tests
        asteroids_lib
        player_check.cpp)
