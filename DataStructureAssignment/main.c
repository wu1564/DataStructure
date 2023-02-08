#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct listNode {
    int value;
    struct listNode *next;
} node;

node *deleteDuplicated(node *listArray, int listNumber) {
    node *prePtr, *curPtr, *data;
    int deleteNumber = 0;
    printf("\nDeleting duplicated.......\n");

    for (int i = 0; i < listNumber; i++) {

        for (data = listArray[i].next; data != NULL; data = data->next) {

            for (prePtr = data, curPtr = data->next; curPtr != NULL; prePtr = curPtr, curPtr = curPtr->next) {

                if (curPtr->value == data->value) {
                    prePtr->next = curPtr->next;
                    free(curPtr);
                    curPtr = prePtr;
                    deleteNumber++;
                }

            }

        }

        listArray[i].value -= deleteNumber;
        deleteNumber = 0;
    }

    printf("Finished !!!!\n\n");
    return listArray;
}

int largestNumber(node *listArray,int listNumber) {
    int maxNumber = INT_MIN;
    node *list = NULL;

    for (int i = 0; i < listNumber; ++i) {
        list = listArray[i].next;

        for (int j = 0; j < listArray[i].value; ++j) {
            maxNumber = (maxNumber > list->value) ? maxNumber : list->value;
            list = list->next;
        }

    }

    return maxNumber;
}

void printCount(node *listArray, int listNumber) {
    printf("\nIn Print Count Function\n");

    for (int i = 0; i < listNumber; ++i) {
        printf("Numbers of No.%d list : %d\n", i + 1, listArray[i].value);
    }

    printf("\n");
}

void printList(node *listArray, int listNumber) {
    node *list = NULL;

    printf("\nIn Print Function\n");

    for (int k = 0; k < listNumber; ++k) {
        list = listArray[k].next;
        printf("No.%d List :", k + 1);

        for (int i = 0; i < listArray[k].value; ++i) {
            printf("%d ", list->value);
            list = list->next;
        }

        printf("\n");
    }

    printf("\n");
}

void interface(node *listArray, int listNumber, void (*createList)()) {
    char str;

    while (1) {
        printf("Key the command to do specific things : ");
        scanf(" %c", &str);

        switch (str) {
            case 'c':
                printCount(listArray, listNumber);
                break;
            case 'p':
                printList(listArray, listNumber);
                break;
            case 'l':
                printf("\nThe largest number is %d\n\n", largestNumber(listArray,listNumber));
                break;
            case 'd':
                deleteDuplicated(listArray, listNumber);
                break;
            case 'n':
                for (int i = 0; i < listNumber; ++i) free(listArray[i].next);
                free(listArray);
                (*createList)();
                break;
            case '0':
                printf("\nProgram finished !");
                for (int i = 0; i < listNumber; ++i) free(listArray[i].next);
                free(listArray);
                exit(EXIT_SUCCESS);
            default :
                printf("Cannot find the command\n");
                break;
        }

    }

}

void createArrayList() {
    int listNumber = 0, number = 0, count = 0, sign = 1;
    char str;
    node *temp, *tail, *list = NULL, *listArray = NULL;
    FILE *file;
	
    printf("\nIn Create List Function\n\n");
    printf("Please input the number of files :");
    scanf("%d", &listNumber);
    char **fileName = (char **) malloc(sizeof(char *) * listNumber);
	
    for (int i = 0; i < listNumber; ++i) fileName[i] = (char *) malloc(sizeof(char) * MAX_SIZE);

    for (int i = 0; i < listNumber; ++i) {
        printf("Please input the name of No.%d file (Ex : File1) :", i + 1);
        scanf(" %s", fileName[i]);
    }

    listArray = (node *) malloc(sizeof(node) * listNumber);

    for (int k = 0; k < listNumber; k++) { // Create List
        strcat(fileName[k], ".txt");

        if (!(file = fopen(fileName[k], "r"))) {
            printf("Fail to open this file\n");
            exit(EXIT_FAILURE);
        }

        temp = (node *) malloc(sizeof(node));
        tail = temp;

        while ((str = (char) fgetc(file)) != EOF) {

            if (str == ' ') {
                list = (node *) malloc(sizeof(node));
                temp->next = list;
                list->value = number * sign;
                temp = temp->next;
                count++;
                number = 0;
                sign = 1;
            } else if (str >= '0' && str <= '9') {
                number = 10 * number + (str - '0');
            } else if (str == '-') {
                sign = -1;
            } else {
                number = 0;
            }

        }

        listArray[k].value = ++count;
        listArray[k].next = (count < 2) ? tail : tail->next; //connect to the listAry 
        temp->next = tail;  //deal with the last number of list
        tail->value = number * sign;
        tail->next = NULL;
        number = 0;
        count = 0;
        sign = 1;
        fclose(file);
    }

    for (int i = 0; i < listNumber; ++i) free(fileName[i]);
    free(fileName);
    interface(listArray, listNumber, &createArrayList);
}

int main() {
    printf("'c' to print how many numbers in each list\n");
    printf("'p' to print all of the lists\n");
    printf("'l' to find the largest number in all lists\n");
    printf("'d' to delete the duplicated number in each list\n");
    printf("'n' to create the new lists\n");
    printf("'0' to exit this program\n");
    createArrayList();
}
