#include <iostream>
#include <time.h>
#include <iomanip>
#include <sstream> 
using namespace std;

int main() {
        //     srand(time(0));
        // string token="";
        // for(int i=0;i<26;i++){
        //     token+=(char)('A'+ rand() % 26);
        // }
        // cout<<token<<endl;

        time_t t =time(NULL);
        tm date=*localtime(&t);
        stringstream ss;
        ss<<put_time(&date, "%Y-%m-%d %H:%M:%S");
        string finalDate=ss.str();
        cout<<finalDate<<endl;
        
        

    return 0;
}
