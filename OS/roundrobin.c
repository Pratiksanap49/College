#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct process
{
    int pid;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int start;
    int remaining;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    // sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival > p[j + 1].arrival)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currenttime = 0, completed = 0, i = 0;
    int timeQuantum;
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    while (completed < n)
    {
        int foundprocess = 0;
        for (int count = 0; count < n; count++)
        {
            i = i % n;
            if (p[i].arrival <= currenttime && p[i].remaining > 0)
            {
                foundprocess = 1;
                int execTime = (int)fmin(timeQuantum, p[i].remaining);
                p[i].remaining -= execTime;
                currenttime += execTime;

                if (p[i].remaining == 0)
                {
                    completed++;
                    p[i].completion = currenttime;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                }
                i++;
                break;
            }
            i++;
        }
        if (!foundprocess)
        {
            currenttime++;
        }
    }

    printf("Round Robin Scheduling\n\n");
    printf("%-5s %-8s %-7s %-11s %-13s %-7s\n", "PID", "Arrival", "Burst", "Completion", "Turn Around", "Waiting");
    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-8d %-7d %-11d %-13d %-7d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
    }
    double avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++)
    {
        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
    }
    printf("\nAverage turn around time: %.2f", avgTAT / n);
    printf("\nAverage waiting time: %.2f\n", avgWT / n);

    return 0;
}
