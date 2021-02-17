// Required libraries
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>

// Structure to store the number value and whether it is marked
// It is called Element
typedef struct{
    int value;
    bool isMarked;
}Element;

// Structure for a process node
typedef struct Node{
    // Left and right values
    Element *lValue, *rValue;
    // Corresponding area
    int area;
    // Left and right neighbors
    struct Node *left;
    struct Node *right;
}Node;

// Structure to store arguments
typedef struct{
    Node *node;
}Arguments;

// Utility function to debug
void printListUtility(Node *root){
    Node *temp = root;
    while(temp != NULL){
        printf("%d - %d | ", temp->lValue->value, temp->lValue->isMarked);
        printf("%d - %d | %d\n", temp->rValue->value, temp->rValue->isMarked, temp->area);
        temp = temp->right;
    }
    printf("\n");
}

// Utility function to print the elements in order according to the rule based on area
void printListInOrder(Node *root){
    Node *temp = root;
    while(temp != NULL){
        if(temp->area == -1){
            printf("%d ", temp->rValue->value);
        }
        else{
            printf("%d ", temp->lValue->value);
        }
        temp = temp->right;
    }
    printf("\n\n");
}

// Comparison function used in each process
void *compare(void *arg){
    Arguments *args = (Arguments*)arg;
    if(args->node->left != NULL){
        if(args->node->left->rValue->value > args->node->lValue->value){
            // if marked element moves left, increase the area of the next one
            // if marked element moves right, decrease the area of the next one
            if(args->node->left->rValue->isMarked == true){
                args->node->area --;
            }

            if(args->node->lValue->isMarked == true){
                args->node->area ++;
            }
            // printf("Swapping %d and %d\n",args->node->left->rValue->value, args->node->lValue->value);
            Element *temp = args->node->left->rValue;
            args->node->left->rValue = args->node->lValue;
            args->node->lValue = temp;
        }
    }

    if(args->node->right != NULL){
        if(args->node->right->lValue->value < args->node->rValue->value){
            // if marked element moves left, increase the area of the next one
            // if marked element moves right, decrease the area of the next one
            if(args->node->right->lValue->isMarked == true){
                args->node->right->area ++;
            }

            if(args->node->rValue->isMarked == true){
                args->node->right->area --;
            }
            // printf("Swapping %d and %d\n",args->node->right->lValue->value, args->node->rValue->value);
            Element *temp = args->node->right->lValue;
            args->node->right->lValue = args->node->rValue;
            args->node->rValue = temp;
        }
    }

    if(args->node->lValue->value > args->node->rValue->value){
        // printf("Swapping %d and %d\n",args->node->lValue->value, args->node->rValue->value);
        Element *temp = args->node->lValue;
        args->node->lValue = args->node->rValue;
        args->node->rValue = temp;
    }
}

// Main function performing sasaki time optimal algorithm
void sasakiTimeOptimalSort(int arr[], int n){
    int max_threads = n;
    pthread_t threads[max_threads];
    Arguments *args = (Arguments*)malloc(sizeof(Arguments));
    Node *prev = NULL, *root;
    // Initializtion of process nodes in the linked list
    for(int i = 0; i < n; i ++){
        Node *node = (Node*)malloc(sizeof(Node));
        if(i == 0){
            Element *lElement = (Element*)malloc(sizeof(Element));
            lElement->value = INT_MIN;
            lElement->isMarked = false;
            Element *rElement = (Element*)malloc(sizeof(Element));
            rElement->value = arr[i];
            rElement->isMarked = true;
            node->lValue = lElement;
            node->rValue = rElement;
            node->area = -1;
            root = node;
        }
        else if(i == n - 1){
            Element *lElement = (Element*)malloc(sizeof(Element));
            lElement->value = arr[i];
            lElement->isMarked = true;
            Element *rElement = (Element*)malloc(sizeof(Element));
            rElement->value = INT_MAX;
            rElement->isMarked = false;
            node->lValue = lElement;
            node->rValue = rElement;
            node->area = 0;
        }
        else{
            Element *lElement = (Element*)malloc(sizeof(Element));
            lElement->value = arr[i];
            lElement->isMarked = false;
            Element *rElement = (Element*)malloc(sizeof(Element));
            rElement->value = arr[i];
            rElement->isMarked = false;
            node->lValue = lElement;
            node->rValue = rElement;
            node->area = 0;
        }
        node->left = prev;
        node->right = NULL;
        if(prev != NULL){
            prev->right = node;
        }
        prev = node;
    }
    // printListUtility(root);
    Node *temp = root;

    // For n - 1 rounds
    for(int i = 1; i < n; i ++){
        // printf(" --- %d --- \n", i);
        int j = 0;
        temp = root;
        while(j < n){
            args->node = temp;
            pthread_create(&threads[j], NULL, compare, (void *)args);
            temp = temp->right;
            pthread_join(threads[j], NULL);
            // printListUtility(root);
            j++;
        }
    }
    
    printListInOrder(root);
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
    // Output
    printf("By Sasaki's algorithm, the sorted sequence is:\n");
    sasakiTimeOptimalSort(arr,n);
    return 0;
}