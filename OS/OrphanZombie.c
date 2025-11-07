#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void)
{

    int n;

    printf("Enter number of elements : ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    pid_t pid;
    pid = fork();

    if (pid == 0)
    {
        sleep(3);
        printf("Child Process");
        printf("Child PID : %d\n", getpid());
        printf("Parent PID : %d\n ", getppid());

        bubblesort(arr, n);

        printf("Child Sorted Array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        exit(0);
    }
    else
    {

        sleep(2);
        printf("Parent Process");
        printf("Parent PID : %d\n", getpid());
        printf(" parent's Parent PID : %d\n ", getppid());

        system("ps");

        bubblesort(arr, n);

        printf("Parent Sorted Array: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        system("ps");
    }

    return 0;
}