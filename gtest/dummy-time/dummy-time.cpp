#include <chrono>
#include <gtest/gtest.h>

TEST(MatrixTest, dummy-time1)
{
  auto begin = std::chrono::steady_clock::now();
    auto something = 1;
  auto end = std::chrono::steady_clock::now();
  ASSERT_TRUE(end - begin < 10000);
}

TEST(MatrixTest, dummy-time2)
{
  ASSERT_FALSE(5 > 2);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

