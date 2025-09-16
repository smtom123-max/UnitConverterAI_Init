#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
    string input_str;
    cout << "Insert value for converting (ex: meter:2.5): ";
    getline(cin, input_str);

    size_t colon_pos = input_str.find(":");
    string unit = input_str.substr(0, colon_pos);
    string value_str = input_str.substr(colon_pos + 1);
    double value = atof(value_str.c_str());
    double meter_value = 0;

    if (unit == "meter") {
        meter_value = value;
    } else if (unit == "feet") {
        meter_value = value / 3.28084;
    } else if (unit == "yard") {
        meter_value = value / 1.09361;
    }

    double in_meters = meter_value;
    double in_feet = meter_value * 3.28084;
    double in_yards = meter_value * 1.09361;

    cout << value << " " << unit << " = " << in_meters << " meter" << endl;
    cout << value << " " << unit << " = " << in_feet << " feet" << endl;
    cout << value << " " << unit << " = " << in_yards << " yard" << endl;

    return 0;
}
