#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // constructor
  Process(int pid);

  // accessors
  int Pid() const;                              
  std::string User() const;                     
  std::string Command() const;                  
  float CpuUtilization() const;                 
  std::string Ram() const;                      
  long int UpTime() const;                      
  bool operator<(Process const& a) const; 

 private:
  int pid_;
  float cpu_usage_;
  long int uptime_; 

  std::string ram_;                      
  std::string user_;
  std::string command_;
};

#endif