#include <iostream>
#include <string>
#include <iomanip>

#include "converter.h"

using namespace std;
using namespace converter;

int main() {
    string inputStr;
    cout << "Insert value for converting (ex: meter:2.5): ";
    if (!getline(cin, inputStr)) {
        cerr << "Failed to read input" << endl;
        return 1;
    }

    string unitStr;
    double value = 0.0;
    if (!parseInput(inputStr, unitStr, value)) {
        cerr << "Invalid input format. Use unit:value (e.g., meter:2.5)" << endl;
        return 1;
    }

    LengthUnit unit;
    try {
        unit = unitFromString(unitStr);
    } catch (const std::exception& ex) {
        cerr << ex.what() << endl;
        return 1;
    }

    double meters = toMeters(value, unit);
    LengthTriple out = computeTripleFromMeters(meters);

    cout.setf(std::ios::fixed);
    cout << setprecision(6);

    cout << value << " " << unitStr << " = " << out.inMeters << " meter" << endl;
    cout << value << " " << unitStr << " = " << out.inFeet << " feet" << endl;
    cout << value << " " << unitStr << " = " << out.inYards << " yard" << endl;

    return 0;
}


