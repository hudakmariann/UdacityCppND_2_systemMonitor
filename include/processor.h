#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


using std::string;

class Processor {
public:
float Utilization();  // : See src/processor.cpp
  
  //  Declare any necessary private members
private:
string line, key ;
float user ; //: normal processes executing in user mode
float nice ; //: niced processes executing in user mode
float system ; //: processes executing in kernel mode
float idle ; //: twiddling thumbs
float iowait; //: In a word, iowait stands for waiting for I/O to complete.

float irq;//: servicing interrupts
float softirq;//: servicing softirqs
float steal ;//: involuntary wait
float guest;//: running a normal guest
float guest_nice;//: running a niced guest
float Idle, NonIdle, Total;
float CPU_Percentage;
};

#endif