#include <string>
#include <iostream>

#include "format.h"

using std::string;

//  Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{
string HH, MM, SS, timestamp;
int h, m, s, mod;
mod=seconds%3600;
h=(seconds-mod)/3600;
m=mod;
mod=m%60;
m=(m-mod)/60;
s=mod;
HH=std::to_string(h);
MM= std::to_string(m);
SS= std::to_string(s);
if (h<10) 
  HH="0"+HH;
if (m<10)
  MM="0"+MM;
if (s<10)
  SS="0"+SS;
timestamp=HH+":"+MM+":"+SS;  
//std::cout << timestamp << "\n";  
 return timestamp; 
}