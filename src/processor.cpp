#include "processor.h"
#include "linux_parser.h"

#include <string>

enum {
    f_user = 0,
    f_nice,
    f_system,
    f_idle,
    f_iowait,
    f_irq,
    f_softirq,
    f_steal,
    f_guest,
    f_guest_nice
};

Processor::Processor()
    : prev(10, 0.0f)
    , curr(10, 0.0f) {}

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::vector<float> fields;
    auto jiffies = LinuxParser::CpuUtilization();

    for (auto j : jiffies)
        fields.push_back(std::stof(j));

    prev = curr;
    curr = fields;

    float PrevIdle = prev[f_idle] + prev[f_iowait];
    float Idle = curr[f_idle] + curr[f_iowait];

    float PrevNonIdle = prev[f_user] + prev[f_nice] + prev[f_system] + prev[f_irq] + prev[f_softirq] + prev[f_steal];
    float NonIdle = curr[f_user] + curr[f_nice] + curr[f_system] + curr[f_irq] + curr[f_softirq] + curr[f_steal];

    float PrevTotal = PrevIdle + PrevNonIdle;
    float Total = Idle + NonIdle;

    float totald = Total - PrevTotal;
    float idled = Idle - PrevIdle;

    return (totald - idled)/totald;
}