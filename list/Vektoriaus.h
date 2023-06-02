#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstdlib>
#include <numeric>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <stdio.h>

#include <list>
using std::list;

using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::setprecision;
using std::fixed;
using std::string;
using std::vector;
using std::numeric_limits;
using std::stringstream;
using std::to_string;
using std::stoi;
using std::advance;

struct studentas{
    string vardas, pavarde;
    list <int> paz;
    int egz;
    double bendr;
};
double mediana (studentas& temp);
