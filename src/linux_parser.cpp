#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream> //HM
//#include <experimental/filesystem> //HM Bonus task
#include <fstream>



#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

//See my solution for the bonus task below this function - I don't have Linux on my machine,
//so I could only use the workspace here, in which filesystem is not supported, however, my solution is included in a comment below this function, but I could not test it.
// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
} 


// BONUS: Update this to use std::filesystem
//Since I don't have any tools on which Linux is installed, I did this project in Udacity workspace. However, it turned out that filesystem is not available in the workspace. 
//So I did the bonus task based on c++ reference, however, I could not test whether it works.
//However, I leave my solution for the bonus task here in a comment, and I appreciate any feedback whether it woul have worked or not.

/*
vector<int> LinuxParser::Pids() {
vector<int> pids;
namespace fs = std::filesystem;
 for(fs::path& p: fs::directory_iterator(kProcDirectory))
 {
    //std::cout << p.path() << '\n';
    // Is this a directory?
    if (fs::is_directory(p)){
      // Is every character of the name a digit?
      string filename=p.string();
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
    return pids;
}
*/

//  Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  string line;
  string key;
  float value;
  float MemTotal, MemFree, MemUsed, MuPercent;
  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if (key == "MemTotal:") 
        {
          MemTotal=value;
        } 
        else
        if (key == "MemFree:")
        {
          MemFree=value;
        } 
      }
    }
  }
  MemUsed= MemTotal - MemFree;
  MuPercent=MemUsed/MemTotal; //NCursesDisplay::ProgressBar megszorozza 100-zal
  return MuPercent; 
}

//Read and return the system uptime

long LinuxParser::UpTime()
{ 
  string line;
  float ut;
  float it;
  long uptime;
  //long idletime;
  std::ifstream filestream(kProcDirectory+kUptimeFilename); //there are 2 floats in the file separated with space
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      //std::cout << " LinuxParser line = " << line << "\n"; 
      std::istringstream linestream(line);    
      while (linestream >> ut >> it) 
      {

      uptime=long(ut);
      //idletime=long(it); 
      }
    }
  }
  /*std::cout << " LinuxParser float ut = " << ut << "\n"; 
  std::cout << " LinuxParser float it = " << it << "\n"; 
  std::cout << " LinuxParser long uptime = " << uptime << "\n"; 
  std::cout << " LinuxParser long idletime = " << idletime << "\n"; */ 
  return  uptime;//+idletime;
}



//Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
string line, key ;
int value, ProcNum;
std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if (key == "processes") 
        {
          ProcNum=value;
        } 
      }
    }
  }
  return ProcNum; 
}

//Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
string line, key ;
int value, ProcActive;
std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if (key == "procs_running") 
        {
          ProcActive=value;
        } 
      }
    }
  }
return ProcActive;   
}
