#include <string>
#include <sstream>
#include<iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    long int minutes;
    long int hours;
    string out;

    std::stringstream ss;
    
    //ss << std::setw(2) << std::setfill('0');


    minutes = seconds / 60; 
    seconds = seconds % 60;

    hours = minutes / 60;
    minutes = minutes % 60;

    ss << std::setw(2) << std::setfill('0')<<hours<<":";
    ss << std::setw(2) << std::setfill('0')<<minutes<<":";
    ss << std::setw(2) << std::setfill('0')<<seconds;

    //out = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds); 
    return ss.str(); }