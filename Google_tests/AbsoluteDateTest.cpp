#include "gtest/gtest.h"
#include "Log.h"

TEST(LogTestSuite, ExampleDate){ // 12/2/2020 -> 737761
    GregorianDate gregDate;
    gregDate.SetMonth(12);
    gregDate.SetDay(2);
    gregDate.SetYear(2020);

    EXPECT_EQ(gregDate.getAbsoluteDate(),737761);
}