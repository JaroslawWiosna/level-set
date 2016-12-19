#include <gtest/gtest.h>
#include "../../utils/utils.hpp"

TEST(Test, average1)
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

  for(int i = 0; i < rows; ++i)
  {
    delete [] phi[i];
    delete [] fimage[i];
  }

  ASSERT_FLOAT_EQ(c1, 40.0);
  ASSERT_FLOAT_EQ(c2, 40.0);
}

TEST(Test, average2)
{
  constexpr int rows{400};  
  constexpr int cols{400};  

  float** phi = new float*[rows];
  for(int i = 0; i < rows; ++i)
    phi[i] = new float[cols];

  float** fimage = new float*[rows];
    for(int i = 0; i < rows; ++i)
        fimage[i] = new float[cols];

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      fimage[i][j] = 0;
    }

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      phi[i][j] = 0.02 * sin(3.1415*i/50)*sin(3.1415*j/50);
    }

  auto c = Average_c(phi, fimage, rows, cols);
  auto c1 = c.first;
  auto c2 = c.second;

  for(int i = 0; i < rows; ++i)
  {
    delete [] phi[i];
    delete [] fimage[i];
  }

  ASSERT_FLOAT_EQ(c1, 0.0);
  ASSERT_FLOAT_EQ(c2, 0.0);
}

TEST(Test, average3)
{
  constexpr int rows{80};  
  constexpr int cols{80};  

  float** phi = new float*[rows];
  for(int i = 0; i < rows; ++i)
    phi[i] = new float[cols];

  float** fimage = new float*[rows];
    for(int i = 0; i < rows; ++i)
        fimage[i] = new float[cols];

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      fimage[i][j] = 7;
    }

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
    {
      phi[i][j] = 0.02 * sin(3.1415*i/50)*sin(3.1415*j/50);
    }

  auto c = Average_c(phi, fimage, rows, cols);
  auto c1 = c.first;
  auto c2 = c.second;

  for(int i = 0; i < rows; ++i)
  {
    delete [] phi[i];
    delete [] fimage[i];
  }

  ASSERT_FLOAT_EQ(c1, 7);
  ASSERT_FLOAT_EQ(c2, 7);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

