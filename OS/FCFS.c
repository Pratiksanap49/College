#include <stdio.h>
#include <stdlib.h>

struct process
{
    int arrival;
    int pid;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int start;
};

int main()
{
    int n;
    printf("Enter number of process : ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", p[i].pid);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time for process %d: ", p[i].pid);
        scanf("%d", &p[i].burst);
    }

    // sort by arrival time
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

    int currenttime = 0, tat = 0, wt = 0, totalTAT = 0, totalWT = 0;

    // main logic
    for (int i = 0; i < n; i++)
    {
        if (currenttime < p[i].arrival)
        {
            currenttime = p[i].arrival;
        }

        p[i].start = currenttime;
        p[i].completion = currenttime + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;

        totalTAT += p[i].turnaround;
        totalWT += p[i].waiting;

        currenttime = p[i].completion;
    }

    printf("\nPID\tArrival\tBurst\tStart\tCompletion\tTurnAround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].start, p[i].completion, p[i].turnaround, p[i].waiting);
    }
}
