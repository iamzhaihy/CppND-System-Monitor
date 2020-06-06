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

Process::Process(int pid): pid_(pid) {
  cpu_usage_ = LinuxParser::ProcCpuUtilization(pid_);
  uptime_ = LinuxParser::UpTime(pid_); 

  ram_ = LinuxParser::Ram(pid_);            
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
}

// DONE: Return this process's ID
int Process::Pid() const { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_usage_; }

// DONE: Return the command that generated this process
string Process::Command() const { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() const {
    return std::to_string((int) (std::stof(ram_)/1024));
}

// DONE: Return the user (name) that generated this process
string Process::User() const { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const { return uptime_; }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return this->CpuUtilization() < a.CpuUtilization();
}