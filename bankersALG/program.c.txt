
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];

    printf("Enter number of processes -- ");
    scanf("%d", &n);
    printf("Enter number of resources -- ");
    scanf("%d", &m);

    // Get allocation and maximum matrix details
    for (int i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation -- ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter Max -- ");
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            if (alloc[i][j] > max[i][j]) {
                printf("Error: Allocation > Max for P%d, resource %d\n", i, j);
                return 0;
            }
        }
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Available resources
    printf("Enter Available Resources -- ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // New request
    int req_pid, request[MAX_RESOURCES];
    printf("Enter New Request Details --\n");
    printf("Enter pid -- ");
    scanf("%d", &req_pid);
    printf("Enter Request for Resources -- ");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check if the request is valid
    for (int i = 0; i < m; i++) {
        if (request[i] > need[req_pid][i]) {
            printf("Request exceeds maximum need for process P%d\n", req_pid);
            return 0;
        }
        if (request[i] > avail[i]) {
            printf("Resources not available for process P%d\n", req_pid);
            return 0;
        }
    }

    // Temporarily allocate resources
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[req_pid][i] += request[i];
        need[req_pid][i] -= request[i];
    }

    // Safety Check and Process Allocation
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int safeSeq[MAX_PROCESSES];
    int count = 0;

    // Keep trying to find processes that can run until all are finished
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    // Simulate resource allocation for the process
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;

                }
            }
        }
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 0;  // If no progress can be made, it's a deadlock
        }
    }

    // Output section after safe state check
    printf("\nOUTPUT\n");

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    // Display the safe sequence with updated resource allocation
    for (int i = 0; i < n; i++) {
        int p = safeSeq[i];

        // First, release resources from the process (simulate it finishing)
        for (int j = 0; j < m; j++)
            work[j] += alloc[p][j];

        // Then print after release
        printf("P%d is visited( ", p);
        for (int j = 0; j < m; j++) {
            printf("%d ", work[j]);
        }
        printf(")\n");
    }

    printf("SYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is -- (");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i < n - 1) printf(" ");
    }
    printf(" )\n");

    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\t\t");
        for (int j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("\t");
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}
