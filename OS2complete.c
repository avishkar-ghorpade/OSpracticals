
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min, temp;

    for(i = 0; i < n-1; i++)
    {
        min = i;

        for(j = i+1; j < n; j++)
        {
            if(arr[j] < arr[min])
                min = j;
        }

        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void display(int arr[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int n, i;
    int arr[100], arr2[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if(n <= 0 || n > 100)
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter elements:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }

    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Fork Failed\n");
        exit(1);
    }

    else if(pid == 0)
    {
        // CHILD PROCESS
        printf("\nChild Process\n");
        printf("Child PID = %d\n", getpid());

        selectionSort(arr, n);

        printf("Selection Sort:\n");
        display(arr, n);

        exit(0);
    }

    else
    {
        // PARENT PROCESS
        printf("\nParent Process\n");
        printf("Parent PID = %d\n", getpid());

        // ZOMBIE PROCESS DEMONSTRATION
        printf("\nZombie Process Demonstration\n");

        sleep(5);

        printf("Child may be in Zombie state\n");

        // Reap child process
        wait(NULL);

        printf("Child process terminated and reaped\n");

        // BUBBLE SORT
        bubbleSort(arr2, n);

        printf("\nBubble Sort:\n");
        display(arr2, n);

        // ORPHAN PROCESS DEMONSTRATION
        printf("\nOrphan Process Demonstration\n");

        pid_t pid2 = fork();

        if(pid2 == 0)
        {
            sleep(5);

            printf("\nOrphan Child Process\n");
            printf("Child PID = %d\n", getpid());
            printf("New Parent PID = %d\n", getppid());

            exit(0);
        }
        else if(pid2 > 0)
        {
            printf("Parent Exiting...\n");
            exit(0);
        }
    }

    return 0;
}
