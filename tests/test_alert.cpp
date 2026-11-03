#include <gtest/gtest.h>
#include "alert.h"

TEST(BatteryOverheatTest, AboveLimitIsOverheat) {
    EXPECT_TRUE(isBatteryOverheat(65.0));
}

TEST(BatteryOverheatTest, BelowLimitIsNormal) {
    EXPECT_FALSE(isBatteryOverheat(40.0));
}

TEST(BatteryOverheatTest, ExactlyAtLimitIsNormal) {
    EXPECT_FALSE(isBatteryOverheat(60.0));  // boundary: equal is not overheated
}

TEST(ShouldAlertTest, OnlyBatteryTempTriggersAlert) {
    EXPECT_TRUE(shouldAlert({"battery_temp", 70.0, 0}));
    EXPECT_FALSE(shouldAlert({"vehicle_speed", 70.0, 0}));
}
