#pragma once

#include <string>

namespace converter {

enum class LengthUnit {
    Meter,
    Feet,
    Yard,
    Centimeter,
    Kilometer,
    Inch
};

// Parse input of the form "unit:value" (e.g., "meter:2.5").
// Returns true on success and fills out parameters.
bool parseInput(const std::string& input, std::string& unitString, double& value);

// Convert an input value in the given unit to meters.
double toMeters(double value, LengthUnit unit);

// Map lowercase unit string to enum; throws std::invalid_argument on unknown unit.
LengthUnit unitFromString(const std::string& unitLower);

// Compute all three representations given a value in meters.
struct LengthTriple {
    double inMeters;
    double inFeet;
    double inYards;
};

LengthTriple computeTripleFromMeters(double meters);

}


