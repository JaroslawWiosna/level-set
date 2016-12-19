#include <chrono>
#include <gtest/gtest.h>

TEST(MatrixTest, dummytime1)
{
  auto begin = std::chrono::steady_clock::now();
    auto something = 1;
  auto end = std::chrono::steady_clock::now();
//  ASSERT_TRUE(static_cast<int>(end - begin) < 10000);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

