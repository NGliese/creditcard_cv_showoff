#include <gtest/gtest.h>

int main(int argc, char **argv) {
  // Initialize the Google Test framework
  ::testing::InitGoogleTest(&argc, argv);

  // Run all tests
  int result = RUN_ALL_TESTS();

  return result;
}