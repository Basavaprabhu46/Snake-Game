#include "Types.h"
#include <gtest/gtest.h>

TEST(GridInitializationTest, DefaultsToTwentyByTwenty)
{
    snake::RenderData data{};

    EXPECT_EQ(data.gridCols, 20);
    EXPECT_EQ(data.gridRows, 20);
}
