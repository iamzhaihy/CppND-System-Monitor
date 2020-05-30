#include "format.h"

#include <string>

// stringify long with leading zero
static std::string to_string(long i) {
  std::string result;

  if (i < 10) result += "0";

  result += std::to_string(i);

  return result;
}

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long seconds) {
  long h, m;
  h = m = 0;

  while (seconds >= 3600) {
    seconds -= 3600;
    h++;
  }

  while (seconds >= 60) {
    seconds -= 60;
    m++;
  }

  return to_string(h) + ":" + to_string(m) + ":" + to_string(seconds);
}