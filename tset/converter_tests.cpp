#include <stdio.h>
#include <gtest/gtest.h>

#include "converter.h"

using namespace converter;

TEST(ParseInput, ValidExamples) {
    std::string unit; double value = 0.0;
    EXPECT_TRUE(parseInput("meter:2.5", unit, value));
    EXPECT_EQ(unit, "meter");
    EXPECT_DOUBLE_EQ(value, 2.5);

    EXPECT_TRUE(parseInput("FEET:3.28084", unit, value));
    EXPECT_EQ(unit, "feet");
    EXPECT_DOUBLE_EQ(value, 3.28084);
}

TEST(ParseInput, InvalidExamples) {
    std::string unit; double value = 0.0;
    EXPECT_FALSE(parseInput("meter", unit, value));
    EXPECT_FALSE(parseInput(":2.0", unit, value));
    EXPECT_FALSE(parseInput("meter:", unit, value));
    EXPECT_FALSE(parseInput("meter:abc", unit, value));
}

TEST(UnitMapping, KnownUnits) {
    EXPECT_NO_THROW({ EXPECT_EQ(unitFromString("meter"), LengthUnit::Meter); });
    EXPECT_NO_THROW({ EXPECT_EQ(unitFromString("feet"), LengthUnit::Feet); });
    EXPECT_NO_THROW({ EXPECT_EQ(unitFromString("yard"), LengthUnit::Yard); });
}

TEST(UnitMapping, UnknownUnitThrows) {
    EXPECT_THROW(unitFromString("unknown"), std::invalid_argument);
}

TEST(Conversions, ToMeters) {
    EXPECT_DOUBLE_EQ(toMeters(1.0, LengthUnit::Meter), 1.0);

    const double feet = 3.28084;
    EXPECT_NEAR(toMeters(feet, LengthUnit::Feet), 1.0, 1e-9);

    const double yards = 1.09361;
    EXPECT_NEAR(toMeters(yards, LengthUnit::Yard), 1.0, 1e-9);
}

TEST(Conversions, TripleFromMeters) {
    LengthTriple t = computeTripleFromMeters(1.0);
    EXPECT_DOUBLE_EQ(t.inMeters, 1.0);
    EXPECT_DOUBLE_EQ(t.inFeet, 3.28084);
    EXPECT_DOUBLE_EQ(t.inYards, 1.09361);
}


