#include <gtest/gtest.h>

TEST(MatrixTest, dummy1)
{
  ASSERT_TRUE(true);
}

TEST(MatrixTest, dummy2)
{
  ASSERT_FALSE(5 > 2);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

