#include "converter.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <unordered_map>

namespace converter {

namespace {
    // Conversion constants centralized in this translation unit
    static constexpr double FEET_PER_METER = 3.28084;
    static constexpr double YARDS_PER_METER = 1.09361;
    static constexpr double INCHES_PER_METER = 39.37007874015748; // exact based on 0.0254 m per inch
    static constexpr double CENTIMETERS_PER_METER = 100.0;
    static constexpr double KILOMETERS_PER_METER = 0.001;

    inline void trimInPlace(std::string& text) {
        auto isSpace = [](unsigned char ch) { return static_cast<bool>(std::isspace(ch)); };
        // left trim
        text.erase(text.begin(), std::find_if(text.begin(), text.end(), [&](unsigned char ch) { return !isSpace(ch); }));
        // right trim
        text.erase(std::find_if(text.rbegin(), text.rend(), [&](unsigned char ch) { return !isSpace(ch); }).base(), text.end());
    }

    const std::unordered_map<std::string, LengthUnit> kUnitAliases = {
        // meters
        {"meter", LengthUnit::Meter}, {"meters", LengthUnit::Meter}, {"m", LengthUnit::Meter},
        // feet
        {"feet", LengthUnit::Feet}, {"foot", LengthUnit::Feet}, {"ft", LengthUnit::Feet},
        // yards
        {"yard", LengthUnit::Yard}, {"yards", LengthUnit::Yard}, {"yd", LengthUnit::Yard},
        // centimeters
        {"centimeter", LengthUnit::Centimeter}, {"centimeters", LengthUnit::Centimeter}, {"cm", LengthUnit::Centimeter},
        // kilometers
        {"kilometer", LengthUnit::Kilometer}, {"kilometers", LengthUnit::Kilometer}, {"km", LengthUnit::Kilometer},
        // inches
        {"inch", LengthUnit::Inch}, {"inches", LengthUnit::Inch}, {"in", LengthUnit::Inch}
    };

    const char* kSupportedUnitsMessage =
        "Supported units: meter(m), feet(ft), yard(yd), centimeter(cm), kilometer(km), inch(in)";
}

static std::string toLowerCopy(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return out;
}

bool parseInput(const std::string& input, std::string& unitString, double& value) {
    std::string working = input;
    trimInPlace(working);

    std::size_t colonPos = working.find(":");
    if (colonPos == std::string::npos || colonPos == 0 || colonPos + 1 >= working.size()) {
        return false;
    }

    std::string unitPart = working.substr(0, colonPos);
    std::string valuePart = working.substr(colonPos + 1);
    trimInPlace(unitPart);
    trimInPlace(valuePart);

    if (unitPart.empty() || valuePart.empty()) {
        return false;
    }

    unitString = toLowerCopy(unitPart);
    try {
        value = std::stod(valuePart);
    } catch (...) {
        return false;
    }
    return true;
}

LengthUnit unitFromString(const std::string& unitLower) {
    auto it = kUnitAliases.find(unitLower);
    if (it != kUnitAliases.end()) {
        return it->second;
    }
    throw std::invalid_argument(std::string("Unknown unit: ") + unitLower + ". " + kSupportedUnitsMessage);
}

double toMeters(double value, LengthUnit unit) {
    switch (unit) {
        case LengthUnit::Meter:
            return value;
        case LengthUnit::Feet:
            return value / FEET_PER_METER;
        case LengthUnit::Yard:
            return value / YARDS_PER_METER;
        case LengthUnit::Centimeter:
            return value / CENTIMETERS_PER_METER;
        case LengthUnit::Kilometer:
            return value / KILOMETERS_PER_METER;
        case LengthUnit::Inch:
            return value / INCHES_PER_METER;
        default:
            throw std::invalid_argument("Unsupported LengthUnit");
    }
}

LengthTriple computeTripleFromMeters(double meters) {
    LengthTriple t{};
    t.inMeters = meters;
    t.inFeet = meters * FEET_PER_METER;
    t.inYards = meters * YARDS_PER_METER;
    return t;
}

}


