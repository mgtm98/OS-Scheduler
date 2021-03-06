#include "priority_nonpreemptive.h"

void PriorityNonpreemptive::addProcess(Process *process)
{
    processes.push_back(*process);
    arrivalTimeSum += process->getArrivalTime();
    burstTimeSum += process->getBurstTime();
    numberOfProcesses++;
}

Process *PriorityNonpreemptive::next(double currentTime, double timeSlice)
{
    if (currentProcessIndex == -1)
    {
        if (processes.empty())
        {
            return nullptr;
        }
        currentProcessIndex = 0;
        for (int i = 1; i < processes.size(); i++)
        {
            if (processes[i].getPriority() < processes[currentProcessIndex].getPriority())
            {
                currentProcessIndex = i;
            }
        }
        if (processes[currentProcessIndex].getRemainingBurstTime() == processes[currentProcessIndex].getBurstTime())
            processes[currentProcessIndex].setStartTime(currentTime);
        processes[currentProcessIndex].setRemainingBurstTime(processes[currentProcessIndex].getRemainingBurstTime() - timeSlice);
        if(processes[currentProcessIndex].getRemainingBurstTime() <= 0)
            processes[currentProcessIndex].setEndTime(currentTime);
        if (processes[currentProcessIndex].getRemainingBurstTime() < 0)
        {
            finishTimeSum += currentTime;
            processes[currentProcessIndex].setRemainingBurstTime(0);
            processes[currentProcessIndex].setEndTime(currentTime);
        }
        return &processes[currentProcessIndex];
    }
    else if (processes[currentProcessIndex].getRemainingBurstTime() <= 0)
    {
        processes.erase(processes.begin() + currentProcessIndex);
        currentProcessIndex = -1;
        if (processes.empty())
        {
            return nullptr;
        }
        currentProcessIndex = 0;
        for (int i = 1; i < processes.size(); i++)
        {
            if (processes[i].getPriority() < processes[currentProcessIndex].getPriority())
            {
                currentProcessIndex = i;
            }
        }
        if (processes[currentProcessIndex].getRemainingBurstTime() == processes[currentProcessIndex].getBurstTime())
            processes[currentProcessIndex].setStartTime(currentTime);
        processes[currentProcessIndex].setRemainingBurstTime(processes[currentProcessIndex].getRemainingBurstTime() - timeSlice);
        if(processes[currentProcessIndex].getRemainingBurstTime() <= 0)
            processes[currentProcessIndex].setEndTime(currentTime);
        if (processes[currentProcessIndex].getRemainingBurstTime() < 0)
        {
            finishTimeSum += currentTime;
            processes[currentProcessIndex].setRemainingBurstTime(0);
        }
        return &processes[currentProcessIndex];
    }
    else
    {
        if (processes[currentProcessIndex].getRemainingBurstTime() == processes[currentProcessIndex].getBurstTime())
            processes[currentProcessIndex].setStartTime(currentTime);
        processes[currentProcessIndex].setRemainingBurstTime(processes[currentProcessIndex].getRemainingBurstTime() - timeSlice);
        if(processes[currentProcessIndex].getRemainingBurstTime() <= 0)
            processes[currentProcessIndex].setEndTime(currentTime);
        if (processes[currentProcessIndex].getRemainingBurstTime() < 0)
        {
            finishTimeSum += currentTime;
            processes[currentProcessIndex].setRemainingBurstTime(0);
            processes[currentProcessIndex].setEndTime(currentTime);
        }
        return &processes[currentProcessIndex];
    }
}

ProcessEnum PriorityNonpreemptive::getProcessType()
{
    return ProcessEnum::PRIORITY;
}

PriorityNonpreemptive::~PriorityNonpreemptive()
{
    this->Scheduler::~Scheduler();
}
