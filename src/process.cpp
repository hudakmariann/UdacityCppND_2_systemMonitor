#include <unistd.h>//clockticks to sec
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex> //replace is defined in this one

#include "process.h"
#include "format.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;




void Process::SetUser()
{
 string line;
 string idkey;
 string a;
 string Uidvalue;
 string VMvalue;
 string pwline[3];
 int ramMB;
  
 std::ifstream filestream (StatusPath);
 if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    { 
    std::istringstream linestream(line); 
    while (linestream >> idkey >> a )
      {
      if (idkey=="Uid:")
        {
        Uidvalue=a;
        //std::cout << "idvalue = " << idvalue << "\n"; 
        } else
      if (idkey=="VmSize:")
        {
         VMvalue=a;
         ramMB=stoi(VMvalue)/1000; // convert to MB
         ram_=std::to_string(ramMB);
         //std::cout << "ram_ = " << ram_ << "\n"; 
        }
      }
    }
  }
//===========
std::ifstream filestream2 (PasswdPath);
 if (filestream2.is_open()) 
  {
    while (std::getline(filestream2, line)) 
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream2(line);    
      while (linestream2 >> pwline[0] >> pwline[1]  >> pwline[2] ) 
      {
      if (pwline[2]==Uidvalue)
        {
        user_=pwline[0];
       // std::cout << "user_ = " << user_ << "\n"; 
        }
      }
    }
  }
}


void Process::SetCPUandUpTime()
{
long ut=LinuxParser::UpTime();
float utime; 	//#14 utime - CPU time spent in user code, measured in clock ticks
float stime; 	//#15 stime - CPU time spent in kernel code, measured in clock ticks
float cutime;    //#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
float cstime;    //#17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
float starttime; //#22 starttime - Time when the process started, measured in clock ticks  
float total_time, seconds;

string statline[23];
string line;

  
std::ifstream filestream (StatPath);
 if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream; 
      linestream.str(line);
      //std::cout <<"line= " << line;
        for (int i=0; i<23; i++)
          {
          (linestream >> statline[i]  ); 
      		{
           // std::cout<<"statline["<<i<<"]="<<statline[i]<<"\n";
      		if (i==21) 
              {
              starttime=stof(statline[21]); //the same as we need for the process's UpTime, too.
               
              } else
            if (i==13)
              {
              utime=stof(statline[13]);
              } else
            if (i==14)
              {
              stime=stof(statline[14]);
              } else
            if (i==15)
              {
              cutime=stof(statline[15]);
              } else
            if (i==16)
              {
              cstime=stof(statline[16]);
              }  
              
      		}
          }
    }
  }
if (sysconf(_SC_CLK_TCK)!=0)
  {
  uptime_=starttime/(sysconf(_SC_CLK_TCK));
  //StrUpTime=Format::ElapsedTime(uptime_);
  //std::cout << "uptime_ = " << uptime_ << "\n";
  //std::cout << "UpTime = " << StrUpTime << "\n";
  //---------------------
  //CPU calculations:
 
  total_time = utime + stime + cutime + cstime;

  seconds =  ut - uptime_; //seconds = uptime - (starttime / Hertz)
  if (seconds!=0)
  cpu_usage_ = (total_time / (sysconf(_SC_CLK_TCK)) / seconds);
 // std::cout << "cpu_usage_ = " << cpu_usage_ << "\n";
  }
}
  
void Process::SetCommand()
{
std::ifstream filestream (CommandPath);
if (filestream.is_open()) 
  {
  std::getline(filestream, command_);
  }  
}



//  Return this process's ID
int Process::Pid() 
{ 
//std::cout << "pid_ = " << pid_ << "\n"; 
return pid_; 
}

//  Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_usage_; }

//  Return the command that generated this process
string Process::Command() { return command_; }

//  Return this process's memory utilization
string Process::Ram() { return ram_; }

//  Return the user (name) that generated this process
string Process::User() { return user_; }

//  Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_;}

//  Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &  a) const
{  
return (a.cpu_usage_ < cpu_usage_); 
}