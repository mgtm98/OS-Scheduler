#include "priority_preemptive.h"

PriorityPreemptive::PriorityPreemptive() : processes(Process::lessPriority)
{
}

void PriorityPreemptive::addProcess(Process *process)
{
    processes.insert(*process);
    arrivalTimeSum += process->getArrivalTime();
    burstTimeSum += process->getBurstTime();
    numberOfProcesses++;
}

Process *PriorityPreemptive::next(double currentTime, double timeSlice)
{
    if (processes.size() == 0)
    {
        return nullptr;
    }
    if (processes.extractMin().getRemainingBurstTime() <= 0)
    {
        processes.deleteMin();
    }
    if (processes.size() == 0)
    {
        return nullptr;
    }
    if (processes.extractMin().getRemainingBurstTime() == processes.extractMin().getBurstTime())
        processes.extractMin().setStartTime(currentTime);
    processes.extractMin().setRemainingBurstTime(processes.extractMin().getRemainingBurstTime() - timeSlice);
    if(processes.extractMin().getRemainingBurstTime() <= 0)
        processes.extractMin().setEndTime(currentTime);
    if (processes.extractMin().getRemainingBurstTime() < 0)
    {
        finishTimeSum += currentTime;
        processes.extractMin().setRemainingBurstTime(0);
    }
    return &processes.extractMin();
}

ProcessEnum PriorityPreemptive::getProcessType()
{
    return ProcessEnum::PRIORITY;
}

PriorityPreemptive::~PriorityPreemptive()
{
    this->Scheduler::~Scheduler();
}
