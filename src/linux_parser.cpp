#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string memtotal, memfree, memavailable, buffers;
  string line;
  string key;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  float MemTotal = 1.0;
  float MemFree = 0.0;
  float utilization = 0.0;

  if (stream.is_open()) {
    while(std::getline(stream, line))
    {
    std::istringstream linestream(line);
    while (linestream >> key) {
        if (key == "MemTotal:") {
          
          linestream >> memtotal;
          MemTotal = std::stof(memtotal);
        }
        else if(key == "MemFree:"){
          linestream >> memfree;
          MemFree = std::stof(memfree);

        }
        else if (key == "MemAvailable:")
        {
          linestream >> memavailable;
        }
        else if ( key == "Buffers:")
        {
          linestream >> buffers;
        }
      }
  }
  }
  //std::cout<<memtotal;
  utilization = ( MemTotal - MemFree ) / MemTotal;

  return utilization; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
string uptime;
string line;
long uptimeinlong = 0;
std::ifstream stream(kProcDirectory + kUptimeFilename); 
if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }

  if(uptime != "")
  {
  uptimeinlong = std::stol(uptime);
  }
  return uptimeinlong; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 

  return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
  string key;

  string user; 
  string nice; 
  string system; 
  string irq;  
  string softirq; 
  string steal;

  long liuser = 0;
  long linice = 0;
  long lisystem = 0; 
  long liirq = 0;
  long lisoftirq = 0;
  long listeal = 0;

  string temp1;
  string temp2;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
        std::istringstream linestream(line);
        while (linestream >> key) {
        if (key == "cpu") {
            linestream >> user >> nice >> system >> temp1 >> temp2 >> irq >> softirq >> steal;
            if(user != "")
              liuser = std::stol(user);
            if (nice != "")
              linice = std::stol(nice);
            if(system != "")
              lisystem = std::stol(system);
            if(irq != "")
              liirq = std::stol(irq);
            if(softirq != "")
              lisoftirq = std::stol(softirq);
            if(steal != "")
              listeal = std::stol(steal);

            return (liuser + linice + lisystem + liirq + lisoftirq + listeal);
        }
    }
  }
  }  
  return (liuser + linice + lisystem + liirq + lisoftirq + listeal); }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line;
  string key;

  string user; 
  string nice; 
  string system; 
  string idle; 
  string iowait; 
  string irq;  
  string softirq; 
  string steal;

  long liidle = 0;
  long liiowait = 0;

  std::ifstream filestream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
        std::istringstream linestream(line);
        while (linestream >> key) {
        if (key == "cpu") {
            linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
            if(idle != "")
              liidle = std::stol(idle);
              
            if(iowait != "")
              liiowait = std::stol(iowait);
            
            return (liidle + liiowait);
        }
    }
  }
  }

  
  return (liidle + liiowait); }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  int totprocesses = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
      if (key == "processes") {
         if(value != "")
          totprocesses = std::stoi(value);
         
         return totprocesses;
        }
      }
    }
  }
  return totprocesses; 
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  int runprocesses = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
      if (key == "procs_running") {
         if(value != "")
          runprocesses = std::stoi(value);
         
         return runprocesses;
        }
      }
    }
  }
  return runprocesses; 
  }
  

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line;
  string proc_id = std::to_string(pid);
  string command;

  std::ifstream filestream(kProcDirectory + proc_id + kCmdlineFilename);
  if (filestream.is_open()) {
    if (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      linestream>>command;
   
    }
  }
  return command; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string proc_id = std::to_string(pid);
  string ram_kb = "";
  long int ramkb = 0;
  int rammb = 0;

  std::ifstream filestream(kProcDirectory + proc_id + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      
      while (linestream >> key >> ram_kb) 
      {
        if (key == "VmSize:") 
        {
           if(ram_kb != "")
            ramkb = std::stoi(ram_kb);
           
           rammb = ramkb / 1000;
           return std::to_string(rammb);
        }
      }
    }
 
  }
  return std::to_string(rammb); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string proc_id = std::to_string(pid);
  string uid = "";


  std::ifstream filestream(kProcDirectory + proc_id + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      
      while (linestream >> key >> uid) 
      {
        if (key == "Uid:") 
        {
           return uid;
        }
      }
    }
 
  }
  return uid;
}
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line;
  string key;
  string value;
  string proc_id = std::to_string(pid);
  string user = "";
  string uid; 
  //first get the uid
  uid = LinuxParser::Uid(pid);

  //second use the uid to get the user name
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      
      while (linestream >> user >> key >> value) 
      {
        if (value == uid) 
        {
           return user;
        }
      }
      //linestream>>command;
   
    }
  }
  return user; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line;
  string key[22];
  string value;
  long int uptime = 0;
  string proc_id = std::to_string(pid);
  
  std::ifstream filestream(kProcDirectory + proc_id + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      for(int i=0; i<22; i++){
        linestream >> key[i];
        }
      }
    }
 
  if (key[21] != "")
    uptime = std::stol(key[21]) / sysconf(_SC_CLK_TCK);
  
  return uptime; }