#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
  Processor();
  float Utilization();

 private:
  std::vector<float> prev{10, 0.0};
  std::vector<float> curr{10, 0.0};
};

#endif