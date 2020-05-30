#include <dirent.h>
#include <unistd.h>

#include <regex>
#include <string>
#include <vector>
#include <iostream>

#define LOG_ERROR(msg) {\
    std::cerr << __FILE__ << ":" \
              << __LINE__ << " " \
              << msg << std::endl; \
}

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Given a string and a regex, return the first match
static std::string parseLine(std::string s, std::string r) {
  std::smatch match;
  std::regex pattern(r);

  if (!std::regex_search(s, match, pattern)) return "";

  return match[1];
}

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
std::string LinuxParser::Kernel() {
  std::string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);

  if (!stream.is_open()) {
    LOG_ERROR("Failed to open file")
    return "";
  }

    std::getline(stream, line);
    return parseLine(line, R"(Linux version\s(.*?)\s.*)");
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

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  std::string line;
  float MemTotal, MemFree;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (!stream.is_open()) {
    LOG_ERROR("Failed to open file")
    return -1;
  }

  std::getline(stream, line);
  MemTotal = std::stof(parseLine(line, R"(MemTotal:\s+([0-9]*)\s+kB)"));
    
  std::getline(stream, line);
  MemFree = std::stof(parseLine(line, R"(MemFree:\s+([0-9]*)\s+kB)"));
    
  return (MemTotal-MemFree)/(MemTotal);
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  std::string line, total;
  std::ifstream stream(kProcDirectory + kUptimeFilename);

  if (!stream.is_open()) {
    LOG_ERROR("Failed to open file")
    return -1;
  }
  
  std::getline(stream, line);
  return std::stol(parseLine(line, R"(^([0-9.]+)\s.*)"));
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string line;
  std::string temp, num;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (!stream.is_open()) {
    LOG_ERROR("Failed to open file")
    return -1;
  }

  while (stream) {
    std::getline(stream, line);
    if (line.find("processes") != std::string::npos) {
      std::istringstream linestream(line);
      linestream >> temp >> num;
    }
  }

  return std::stoi(num);
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line;
  std::string temp, num;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (!stream.is_open()) {
    LOG_ERROR("Failed to open file")
    return -1;
  }

  while (stream) {
    std::getline(stream, line);
    if (line.find("procs_running") != std::string::npos) {
      std::istringstream linestream(line);
      linestream >> temp >> num;
    }
  }

  return std::stoi(num);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }