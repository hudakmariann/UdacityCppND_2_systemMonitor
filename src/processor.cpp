#include "processor.h"
#include "linux_parser.h"


//  Return the aggregate CPU utilization


float Processor::Utilization() 
{
std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  if (filestream.is_open()) 
    {
      std::getline(filestream, line); //HM
      std::istringstream linestream(line);
      //std::cout << line<<"\n";
       while (linestream >>key >>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal>>guest>>guest_nice);
      {
      Idle = idle + iowait; 
      NonIdle = user + nice + system + irq + softirq + steal;
      Total = Idle + NonIdle;
      CPU_Percentage =(Total - Idle)/Total;
      }
    }
//--------------------------------    
/* //TODO - once I return to this project - make the system monitor infos more up to date.
//These formulas below can be used:
PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

// differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald*/

//These are for testing this function (I leave these here for future development)
 /*std::cout<<"key= "<<key<<".\n";
 std::cout<<"user= "<<user<<".\n"; 
 std::cout << "nice=" << nice << "\n";
 std::cout<<"system= "<<system<<".\n"; 
 std::cout << "idle=" << idle << "\n";
  std::cout<<"iowait= "<< iowait <<".\n"; 
 std::cout << "irq=" << irq << "\n";
 std::cout<<"Total= "<<Total<<".\n"; 
 std::cout << "CPU_Percentage=" << CPU_Percentage << "\n";*/
return  CPU_Percentage;
}