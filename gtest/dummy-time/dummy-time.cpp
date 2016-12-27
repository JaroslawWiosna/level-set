/**
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */


#include <chrono>
#include <gtest/gtest.h>

TEST(Test, dummytime1)
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

