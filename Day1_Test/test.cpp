#include "pch.h"

#include "../Day1/Day1.h"

TEST(CalculateRestToDesiredNumberTestSuite, FunctionTest)
{
  EXPECT_EQ(CalculateRestToDesiredNumber(100, 1), 99);
  EXPECT_EQ(CalculateRestToDesiredNumber(611, 12), 599);
  EXPECT_EQ(CalculateRestToDesiredNumber(127, 27), 100);
  EXPECT_EQ(CalculateRestToDesiredNumber(2005, 1006), 999);

  EXPECT_EQ(CalculateRestToDesiredNumber(2020, 110), CalculateRestTo2020(110));
}