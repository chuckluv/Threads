#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int array[SIZE];

void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

//code inspiration: https://www.geeksforgeeks.org/merge-sort-using-multi-threading/
void merge(int left, int middle, int right)

{
int i, j, k;
int n1 = middle - left + 1;
int n2 = right - middle;
int L[n1], R[n2];

for (i = 0; i < n1; i++)
{
L[i] = array[left + i];
}
for (j = 0; j < n2; j++)
{
R[j] = array[middle + 1+ j];
}

i = 0; 
j = 0; 
k = left; 
while (i < n1 && j < n2)
{
if (L[i] <= R[j])
{

array[k] = L[i];
i++;
}

else

{
array[k] = R[j];
j++;
}
k++;
}



while (i < n1)

{

array[k] = L[i];

i++;

k++;

}

while (j < n2)

{
array[k] = R[j];
j++;
k++;

}
}

// Runs mergesort on the array segment described in the

// argument. Spawns two threads to mergesort each half

// of the array segment, and then merges the results.

void* mergeSort(void* args) {

// Dereference args

StartEndIndexes sei = *((StartEndIndexes*)args);

int error1, error2, midpoint;

// Check for base case

if (sei.start < sei.end)

{

// Find the midpoint

midpoint = (sei.start + sei.end) / 2;

// Create variables for subproblems

StartEndIndexes sei1, sei2;

sei1.start = sei.start;

sei1.end = midpoint;

sei2.start = midpoint + 1;

sei2.end = sei.end;

pthread_t left_tid, right_tid;

// Call threads to sort both subproblems

error1 = pthread_create(&left_tid, NULL, mergeSort, &sei1);

error2 = pthread_create(&right_tid, NULL, mergeSort, &sei2);

if (error1 != 0)

printf("Error sorting left tree.\n");

if (error2 != 0)

printf("Error sorting right tree.\n");

error1 = pthread_join(left_tid, NULL);

error2 = pthread_join(right_tid, NULL);

if (error1 != 0)

printf("Error sorting left tree.\n");

if (error2 != 0)

printf("Error sorting right tree.\n");
  

// Combine subproblems to form solution

merge(sei.start, midpoint, sei.end);

}

return NULL;

}

int main() {

srand(time(0));

StartEndIndexes sei;

sei.start = 0;

sei.end = SIZE - 1;

int error;

// 1. Fill array with random numbers.

fillArrayWithRandomNumbers(array);

// 2. Print the array.

printf("Unsorted array: ");

printArray(array);

// 3. Create a thread for merge sort.

pthread_t tid;

error = pthread_create(&(tid), NULL, &mergeSort, &sei);

if (error != 0)

printf("Error creating thread.\n");

// 4. Wait for mergesort to finish.

error = pthread_join(tid, NULL);

if (error != 0)

printf("Error joining thread.\n");

// 5. Print the sorted array.

printf("Sorted array: ");

printArray(array);

}


/*
// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.
void* mergeSort(void* args) {
    return NULL;
}

int main() {
    srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
    
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create a 2 threads for merge sort.
    
    // 4. Wait for mergesort to finish.
    
    // 5. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);
}
*/
