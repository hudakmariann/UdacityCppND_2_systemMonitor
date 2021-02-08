#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <fstream>


/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process (int pid ) : pid_(pid) 
    {
    SetUser();
    SetCPUandUpTime();
    SetCommand();
    }
  
  
    std::string StatusPath{"/proc/" + std::to_string(pid_)+"/status"}; //if I declare these as constants, I get a "useing a deleted function " error when trying to sort the processes_ vector....
    std::string PasswdPath {"/etc/passwd"};
    std::string StatPath{"/proc/" + std::to_string(pid_)+"/stat"};
    std::string CommandPath{"/proc/" + std::to_string(pid_)+"/cmdline"};
    int Pid();                               
    std::string User();                      // : See src/process.cpp
    std::string Command();                   // : See src/process.cpp
    float CpuUtilization();                  // : See src/process.cpp
    std::string Ram();                       // : See src/process.cpp
    long int UpTime();                       // : See src/process.cpp
    bool operator<(Process const &  a) const ;  // : See src/process.cpp
  

  // : Declare any necessary private members
 private:
   std::string user_; 
   int pid_;
   long int uptime_;
   std::string ram_;
   std::string command_;
   float cpu_usage_ ;

   void SetUser();
   void SetCPUandUpTime();
   void SetCommand();

 
 
};

#endif