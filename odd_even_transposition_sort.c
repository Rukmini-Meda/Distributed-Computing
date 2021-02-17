// Required libraries
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

// Structure for arguments
typedef struct{
    int *arr;
    int n;
    int index;
}arguments;

// Utility function to print the array
void printArray(int *arr, int n){
    for(int i = 0; i < n;i ++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}

// Comparison in each process
void *compare(void *arg){
    arguments *args = (arguments*)arg;
    int index = args->index;
    int temp = args->arr[index];
    if((index + 1 < args->n) && (args->arr[index + 1] < args->arr[index])){
        args->arr[index] = args->arr[index+1];
        args->arr[index + 1] = temp;
    }
}

// Main function performing the odd even transposition sort
void oddEvenTranspositionSort(int arr[], int n){
    
    int max_threads = (n + 1) / 2;
    pthread_t threads[max_threads];
    arguments *args = (arguments*)malloc(sizeof(arguments));
    args->arr = arr;
    args->n = n;
    
    // For n rounds
    for(int i = 1; i <= n; i ++){
        // Odd exchanges
        if(i % 2 == 1){
            int index = 0;
            for(int j = 0; j < max_threads; j ++){
                args->index = index;
                pthread_create(&threads[j], NULL, compare, (void *)args);
                index += 2;
                pthread_join(threads[j], NULL);
            }
        }
        // Even exchanges
        else{
            int index = 1;
            for(int j = 0; j < max_threads - 1; j ++){
                args->index = index;
                pthread_create(&threads[j], NULL, compare, (void *)args);
                index += 2;
                pthread_join(threads[j], NULL);
            }
        }
    }
}

// Driver function of the program
int main(){
    int n;
    // Input
    printf("Enter the number of elements in your sequence:\n");
    scanf("%d",&n);
    int arr[n];
    printf("Enter your sequence:\n");
    for(int i = 0;i < n; i ++){
        scanf("%d",&arr[i]);
    }
    oddEvenTranspositionSort(arr,n);
    // Output
    printf("By odd even transposition sort, the sorted sequence is:\n");
    printArray(arr,n);
    return 0;
}