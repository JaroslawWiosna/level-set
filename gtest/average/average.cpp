#include <gtest/gtest.h>
#include "../../utils/utils.hpp"

TEST(MatrixTest, average1)
{
  constexpr int rows{40};  
  constexpr int cols{40};  

  float** phi = new float*[rows];
  for(int i = 0; i < rows; ++i)
    phi[i] = new float[cols];

  float** fimage = new float*[rows];
    for(int i = 0; i < rows; ++i)
        fimage[i] = new float[cols];

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      fimage[i][j] = 40;
    }

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      phi[i][j] = 0.02 * sin(3.1415*i/50)*sin(3.1415*j/50);
    }

  auto c = Average_c(phi, fimage, rows, cols);
  auto c1 = c.first;
  auto c2 = c.second;

  ASSERT_FLOAT_EQ(c1, 40.0);
  ASSERT_FLOAT_EQ(c2, 40.0);
  ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

