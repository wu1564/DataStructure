#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int value;
    struct node *next;
} node;

int listSize(node *list) {
    int count = 0;

    for (; list; list = list->next, count++);
    return count;
}

void swap(int *a, int *b) {
    *a =  *a + *b;
    *b = *a  - *b;
    *a = *a - *b;
}

void printHeap(int *array, int size) {
    const int digit = 4;
    int layer = log2(size) + 1;
    int halfNum = (pow(2, layer) - 2) / 2;
    int space = halfNum * digit;
    int space2 = 0, count = layer, index = 1, numberDigit = 0, temp;
    int *spaceArray = (int *) malloc(sizeof(int) * (layer + 1));

    printf("\nIn heap : \n");
    for (int i = 0; i <= layer; ++i) spaceArray[i] = 1;

    for (int i = 2; i <= layer; ++i) {
        space2 = (space2 * 2 + 1);
        spaceArray[i] = space2;
    }

    for (int i = 1; i <= layer; ++i) {

        for (int k = 0; k < space; ++k) printf(" ");

        for (int j = 0; j < pow(2, i - 1); ++j) {
            if (index > size) break;
            temp = array[index];

            while (temp) {
                temp /= 10;
                numberDigit++;
            }

            printf("%d", array[index]);
            for (int q = 1; q <= digit - numberDigit; ++q) printf(" ");
            if (i != 0) for (int k = spaceArray[count]; k > 0; --k) for (int l = 0; l < digit; ++l) printf(" ");
            index++;
            numberDigit = 0;
        }

        printf("\n");
        space = (halfNum /= 2) * digit;
        count = (i == 1) ? count : --count;
    }

    free(spaceArray);
}

void buildMinHeap(node *list, int size) {
    node *temp = list;
    int *array = (int *) malloc(sizeof(int) * (size + 1)), current = size, tempNum;

    for (int i = 1; temp; i++, temp = temp->next) {
        array[i] = temp->value;
    }

    while (current != 1 && array[current / 2] > array[current]) {
        tempNum = array[current];
        array[current] = array[current / 2];
        array[current / 2] = tempNum;
        current /= 2;
    }

    for (int i = 1; list; i++, list = list->next) list->value = array[i];
    printHeap(array, size);
    free(array);
}

void deleteLowest(int *array, int size) {
    int index = 1;

    swap(&array[1], &array[size]);

    while (index < size) {

        if (index * 2 + 1 > size)
            break;
        else if (index * 2 + 1 == size) {
            if (array[index] > array[index * 2]) swap(&array[index], &array[index * 2]);
            break;
        }

        if (array[index * 2] > array[index * 2 + 1]) {

            if (array[index] > array[index * 2 + 1]) {
                swap(&array[index], &array[index * 2 + 1]);
                index = index * 2 + 1;
            } else {
                break;
            }

        } else {

            if (array[index] > array[index * 2]) {
                swap(&array[index], &array[index * 2]);
                index = index * 2;
            } else {
                break;
            }

        }

    }

    printf("\nDeleting ~~~\n");
    printHeap(array, size - 1);
}

node *insertKey() {
    node *temp = (node *) malloc(sizeof(node)), *first = temp, *list;
    int inputNum = 0;

    printf("\nIn InsertKey Function\n");
    printf("Please insert a key into a heap (-1 to exit this function) : ");
    scanf("%d", &inputNum);

    while (inputNum != -1) {
        list = (node *) malloc(sizeof(node));
        list->value = inputNum;
        list->next = NULL;
        temp->next = list;
        temp = temp->next;
        buildMinHeap(first->next, listSize(first->next));
        printf("Please insert a key into a heap (-1 to exit this function) : ");
        scanf("%d", &inputNum);
    }

    list = first;
    first = first->next;
    free(list);
    return first;
}

void printKeys(int *array, int size) {
    printf("\nIn PrintKeys Function\n");
    for (int i = 1; i <= size; i++) printf("%d ", array[i]);
    printf("\n\n");
}

void interface() {
    char key;
    int size, times, *array;
    node *list;
    node *tmp;

    restart:
    printf("Key 'i' is to insert an integer into a min heap\n");
    printf("Key 'e' is to exit this program\n");
    scanf(" %c", &key);

    while (key != 'i') {
        if (key == 'e') exit(EXIT_SUCCESS);
        printf("Key 'i' is to insert an integer into a min heap\n");
        printf("Key 'e' is to exit this program\n");
        scanf(" %c", &key);
    }

    list = insertKey();
    size = listSize(list);
    array = (int *) malloc(sizeof(int) * (size + 1));
    tmp = list;

    for (int i = 1; list; ++i, free(tmp), tmp = list) {
        array[i] = tmp->value;
        list = list->next;
    }

    times = size - 1;

    while (1) {
        printf("Key 'r' is to restart this program\n");
        printf("Key 'e' is to exit this program\n");
        printf("Key 'd' is to delete the minimum number in the min heap\n");
        scanf(" %c", &key);

        switch (key) {
            case 'd':
                deleteLowest(array, times + 1);
                times--;
                if (!times) goto printFunction;
                break;
            case 'r':
                free(array);
                goto restart;
            case 'e':
                exit(EXIT_SUCCESS);
        }

    }

    printFunction:

    while (1) {
        printf("Key 'p' to print keys with decreasing order\n");
        printf("Key 'r' is to restart this program\n");
        printf("Key 'e' is to exit this program\n");
        scanf(" %c", &key);

        switch (key) {
            case 'p':
                printKeys(array, size);
                break;
            case 'r':
                free(array);
                goto restart;
            case 'e':
                exit(EXIT_SUCCESS);
        }

    }

}

int main() {
    interface();
}
