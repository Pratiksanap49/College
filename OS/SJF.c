#include <stdio.h>
#include <limits.h>

struct process
{
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
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

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed != n)
    {
        int idx = -1;
        int minRemaining = INT_MAX;

        // find process with smallest remaining time among arrived ones
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival <= currentTime && p[i].remaining > 0)
            {
                if (p[i].remaining < minRemaining)
                {
                    minRemaining = p[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            // no process has arrived yet
            currentTime++;
            continue;
        }

        // run process for 1 unit
        p[idx].remaining--;
        currentTime++;

        // if process completed
        if (p[idx].remaining == 0)
        {
            p[idx].completion = currentTime;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            totalTAT += p[idx].turnaround;
            totalWT += p[idx].waiting;
            completed++;
        }
    }

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);

    return 0;
}
