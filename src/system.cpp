#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream> //for using cout for testing


#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;



// Return the system's CPU
Processor& System::Cpu()
{ 
return cpu_; 
}

void System::SetProcesses()
{
processes_.clear();
vector<int> pids= LinuxParser::Pids();
for (int i : pids)
  {
  Process proc (i);
  processes_.push_back(proc);
  }  
std::sort(processes_.begin(), processes_.end());
 /* for (Process a : processes_)
    std::cout<<"pid_="<<a.Pid()<<"\n";*/
  /* for (Process i : processes_)
   {std::cout<< "Pid=" << i.Pid()<<"\n";
   std::cout<< "User=" << i.user_<<"\n";
   }*/
/*std::cout<< "Pid=" <<processes_[1].Pid()<<"\n";
std::cout<< "User="<<processes_[1].User()<<"\n";
std::cout<< "uptime="<<processes_[1].UpTime()<<"\n";
std::cout<< "command="<<processes_[1].Command()<<"\n";
std::cout<< "ram="<<processes_[1].Ram()<<"\n"; */  
}


//Return a container composed of the system's processes
vector<Process>& System::Processes()
 { 
SetProcesses();
return processes_; 
}



// Return the system's kernel identifier (string)
std::string System::Kernel() 
{ 
return  LinuxParser::Kernel();
}

//  Return the system's memory utilization
float System::MemoryUtilization() 
{ 
float mu = LinuxParser::MemoryUtilization();
return mu; 
}

//  Return the operating system name
std::string System::OperatingSystem()
{ 
string os=LinuxParser::OperatingSystem();
return os; 
}

//  Return the number of processes actively running on the system
int System::RunningProcesses() 
{
int rp=LinuxParser::RunningProcesses();   
return rp; 
}

//  Return the total number of processes on the system
int System::TotalProcesses() 
{ 
int tp=LinuxParser::TotalProcesses();
return tp; 
}

//  Return the number of seconds since the system started running
long int System::UpTime() 
{
long ut=LinuxParser::UpTime();
//std::cout << "system.UpTime= "<< ut << "\n";
return ut; 
}