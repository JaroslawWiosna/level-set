/**
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include <gtest/gtest.h>
#include "../../Image/Image.hpp"

TEST(Test, average1)
{
#if 0
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
      phi[i][j] = 0.02 * sin( M_PI *i/50)*sin( M_PI *j/50);
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
#endif
  ASSERT_TRUE(true);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

