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
    EXPECT_TRUE(shouldAlert({"vehicle_speed", 220.0, 0}));
}

TEST(OverspeedTest, AboveLimitIsOverspeed) {
    EXPECT_TRUE(isOverSpeeding(210.0));
}

TEST(OverspeedTest, BelowLimitIsNormal) {
    EXPECT_FALSE(isOverSpeeding(120.0));
}

TEST(OverspeedTest, ExactlyAtLimitIsNormal) {
    EXPECT_FALSE(isOverSpeeding(200.0));
}