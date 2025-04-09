
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 5

int hungry[MAX] = {0}; // Status of each philosopher (0 = not hungry, 1 = hungry)

void eat(int p) {
    printf("P %d is granted to eat\n", p);
    sleep(1); // Simulate eating
    printf("P %d has finished eating\n", p);
}

void oneCanEat(int numHungry, int philosophers[]) {
    for (int i = 0; i < numHungry; i++) {
        for (int j = 0; j < numHungry; j++) {
            printf("P %d is waiting\n", philosophers[j]);
        }
        eat(philosophers[i]);
    }
}

void twoCanEat(int numHungry, int philosophers[]) {
    int i = 0;
    while (i < numHungry) {
        for (int j = 0; j < numHungry; j++) {
            printf("P %d is waiting\n", philosophers[j]);
        }

        if (i + 1 < numHungry) {
            printf("P %d and P %d are granted to eat\n", philosophers[i], philosophers[i+1]);
            sleep(1);
            printf("P %d and P %d have finished eating\n", philosophers[i], philosophers[i+1]);
            i += 2;
        } else {
            eat(philosophers[i]);
            i++;
        }
    }
}

int main() {
    int n, numHungry, choice;
    int philosophers[MAX];

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    printf("How many are hungry: ");
    scanf("%d", &numHungry);

    for (int i = 0; i < numHungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &philosophers[i]);
        hungry[philosophers[i] - 1] = 1;
    }

    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                oneCanEat(numHungry, philosophers);
                break;
            case 2:
                printf("Allow two philosophers to eat at any time\n");
                twoCanEat(numHungry, philosophers);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }

    } while (choice != 3);

    return 0;
}
