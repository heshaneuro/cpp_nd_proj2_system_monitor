#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

Process::Process(int processid){
    pid = processid;
}
// TODO: Return this process's ID
int Process::Pid() { 
    
    return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const{ 
  string line;
  string key[22];
  string value;
  long int totaltime;
  long int seconds;
  string proc_id = std::to_string(pid);
  long int up_time = LinuxParser::UpTime();
  std::ifstream filestream(LinuxParser::kProcDirectory + proc_id + LinuxParser::kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      for(int i=0; i<22; i++){
        linestream >> key[i];
        }
      }
    }
    totaltime = std::stol(key[13]) + std::stol(key[14]) + std::stol(key[15]) + std::stol(key[16]);
    seconds = (up_time - (std::stol(key[21]) / sysconf(_SC_CLK_TCK)));
    return ((float)totaltime / (float)(sysconf(_SC_CLK_TCK))) / (float)seconds;
 
   }

// TODO: Return the command that generated this process
string Process::Command() {
     
    return  LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    
    return  a.CpuUtilization() < this->CpuUtilization(); }
