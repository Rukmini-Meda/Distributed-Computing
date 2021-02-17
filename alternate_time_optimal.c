// Required libraries
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//Structure for arguments
typedef struct{
    int *arr;
    int n;
    int center;
}Arguments;

// Utility function to print the array
void printArray(int *arr, int n){
    for(int i = 0; i < n;i ++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// Utility function to swap two numbers
void swap(int *arr, int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Utility function to find the minimum of two numbers
int minimum(int a,int b){
    if(a < b){
        return a;
    }
    else{
        return b;
    }
}

// Utility function to find the maximum of two numbers
int maximum(int a,int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

// Comparison function used while performing an individual process
void *compare(void *arg){
    Arguments *args = (Arguments*)arg;
    // edge case
    if(args->center - 1 < 0){
        if(args->arr[args->center] > args->arr[args->center + 1]){
            swap(args->arr, args->center, args->center + 1);
        }
    }
    else if(args->center + 1 >= args->n){
        if(args->arr[args->center] < args->arr[args->center - 1]){
            swap(args->arr, args->center, args->center - 1);
        }
    }
    // non - edge case
    else{
        int minValue = minimum(args->arr[args->center], minimum(args->arr[args->center - 1], args->arr[args->center + 1]));
        int maxValue = maximum(args->arr[args->center], maximum(args->arr[args->center - 1], args->arr[args->center + 1]));
        int midValue = args->arr[args->center] + args->arr[args->center - 1] + args->arr[args->center + 1] - minValue - maxValue;
        args->arr[args->center - 1] = minValue;
        args->arr[args->center + 1] = maxValue;
        args->arr[args->center] = midValue;
    }
}

// Main function performing the alternate time optimal sorting
void alternateTimeOptimalSorting(int arr[], int n){
    int max_threads = n;
    pthread_t threads[max_threads];
    Arguments *args = (Arguments*)malloc(sizeof(Arguments));
    args->arr = arr;
    args->n = n;
    // For n - 1 rounds
    for(int i = 1; i < n; i ++){
        int remainder = (i + 1) % 3;
        int j;
        if(remainder == 0){
            j = 2;
        }
        else if(remainder == 1){
            j = 0;
        }
        else{
            j = 1;
        }
        int id = 0;
        // For all centers possible at a distance of 3
        while(j < n){
            args->center = j;
            // Thread creation
            pthread_create(&threads[id], NULL, compare, (void *)args);
            // Thread waiting
            pthread_join(threads[id], NULL);
            // Incrementing by 3 to find the next center
            j += 3;
            id ++;
        }
    }
}

// Driver function of the program
int main(){
    // Input
    int n;
    printf("Enter the number of elements in your sequence:\n");
    scanf("%d",&n);
    int arr[n];
    printf("Enter your sequence:\n");
    for(int i = 0;i < n; i ++){
        scanf("%d",&arr[i]);
    }
    alternateTimeOptimalSorting(arr,n);
    // Output
    printf("By alternate time optimal sorting method, the sorted sequence is:\n");
    printArray(arr,n);
    return 0;
}