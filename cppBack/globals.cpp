#include "globals.hpp"
#include <string>
#include <time.h> //time library
#include <iomanip> //for put_time
#include <sstream>// to convert time to string
using namespace std;
string currentDate()
{
        time_t t =time(NULL);
        tm date=*localtime(&t);
        stringstream ss;
        ss<<put_time(&date, "%Y-%m-%d %H:%M:%S");
        string finalDate=ss.str();
        return finalDate;
}