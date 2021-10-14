#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define MAX 100

typedef union {
    int i;
    long l;
    float f;
    double d;
    void *v;
    char *s;
    char c;
} Jval;

Jval new_jval_i(int i) { 
    Jval j; 
    j.i = i; 
    return j; 
}

int jval_i(Jval j) {
    return j.i; 
}

void swap(Jval *a, Jval *b) {
    Jval temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(Jval *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i].i);
    }
    printf("\n");
}

int compare_i(Jval *a, Jval *b) {
    
    if (jval_i(*a) == jval_i(*b)) {
        return 0;
    } else if (jval_i(*a) < jval_i(*b)) {
        return -1;
    } else {
        return 1;
    }
}

Jval *create_array_i(int n) {
    Jval *array = (Jval *) malloc(sizeof(Jval) * n);
    for (int i = 0; i < n; i++) {
        array[i] = new_jval_i(rand() % 100);
    }
    return array;
}

void sort_gen(Jval a[], int l, int r, int (*compare_i)(Jval*, Jval*)) {
    Jval pivot;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    pivot = a[r];
    if (r <= l) { 
        return;
    }
    while (true) {
        while (compare_i(&a[++i], &pivot) < 0) {
        }
        while (compare_i(&a[--j], &pivot) > 0) {
            if (j == l) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        swap(&a[i], &a[j]);
        if (compare_i(&a[i], &pivot) == 0) {
            swap(&a[++p], &a[i]);
        }
        if (compare_i(&a[j], &pivot) == 0) {
            swap(&a[--q], &a[j]);
        }
    }

    swap(&a[i], &a[r]);
    j = i - 1;
    i++;
    for (int k = l; k < p; k++, j--) {
        swap(&a[k], &a[j]);
    } 
    for (int k = r - 1; k > q; k--, i++) {
        swap(&a[i], &a[k]);
    }
    sort_gen(a, l, j, compare_i);
    sort_gen(a, i, r, compare_i);
}

int search_gen(Jval a[], int l, int r, Jval item, int (*compare_i)(Jval*, Jval*)) {
    if (r < l) {
        return - 1;
    }
    int mid, res;
    mid = (l + r) / 2;
    res = compare_i(&item, &a[mid]);
    if (res == 0) {
        return mid;
    } else if (res < 0) {
        return search_gen(a, l, mid - 1, item, compare_i);
    } else {
        return search_gen(a, mid + 1, r, item, compare_i);
    }
}

void sort_i(Jval a[], int l, int r) {
    sort_gen(a, l, r, compare_i);
}

int search_i(Jval a[], int l, int r, int x) {
    return search_gen(a, l, r, new_jval_i(x), compare_i);
}

int main() {

    // Sorting
    Jval *array = create_array_i(MAX);
    printArray(array, MAX);
    printf("After sorting:\n");
    sort_i(array, 0, MAX - 1);

    printArray(array, MAX);

    // Searching
    printf("Enter a number: ");
    Jval key_j;
    scanf("%d%*c", &(key_j.i));
    printf("Index of element in array: %d\n", search_i(array, 0, MAX - 1, key_j.i));
    free(array);
    return 0;
}