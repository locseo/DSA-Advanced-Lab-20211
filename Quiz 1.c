#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#define MAX 10000000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int *createArray(int size) {
    __auto_type array = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }
    return array;
}

int * dumpArray(int *p, int size) {
    size_t array_size = size * sizeof(int);
    __auto_type array = (int *)malloc(array_size);
    memcpy(array, p, array_size);
    return array;
}

void quicksort_2_way(int a[], int l, int r) {

    void sort(int a[], int l, int r) {
        
        if (r <=  l) {
            return;
        }
        int i = l - 1;
        int j = r;
        int pivot = a[r];
        while (true) {
            while (a[++i] < pivot) {
            }
            while (pivot < a[--j]) {
                if (j == l) {
                    break;
                }
            }
            if (i >= j) {
                break;
            }
            swap(&a[i], &a[j]);
        }

        swap(&a[i], &a[r]);

        sort(a, l, i - 1);
        sort(a, i + 1, r);
    }
    sort(a, l, r);
}

void quicksort_3_way(int a[], int l, int r) {
    
    void sort(int a[], int l, int r) {
        
        if (r <= l) {
            return;
        }
        int i = l - 1;
        int j = r;
        int p = l - 1;
        int q = r;

        while (true) {
            while (a[++i] < a[r]) {
            }
            while (a[r] < a[--j]) {
                if (j == l) {
                    break;
                }
            }
            if (i >= j) {
                break;
            }
            swap(&a[i], &a[j]);
            if (a[i] == a[r]) {
                swap(&a[++p], &a[i]);
            }
            if (a[j] == a[r]) {
                swap(&a[--q], &a[j]);
            }
        }

        swap(&a[i], &a[r]);
        j = i - 1;
        ++i;

        for (int k = 1; k <= p; k++) {
            swap(&a[k], &a[j--]);
        } 
        for (int k = r - 1; k >= q; k--) {
            swap(&a[k], &a[i++]);
        }
        sort(a, l, j);
        sort(a, i, r);
    }

    sort(a, l, r);
}

int int_compare(void const * x, void const * y) {
    int m, n;
    m = *((int *) x);
    n = *((int *) y);
    if (m == n) {
        return 0;
    }
    return m > n ? 1 : -1;
}


int main() {
    
    srand(time(NULL));
    clock_t start, end;

    int *a = createArray(MAX);
    int *b = dumpArray(a, MAX);
    int *c = dumpArray(a, MAX);
    
    start = clock();
    quicksort_2_way(a, 0, MAX - 1);
    end = clock();
    printf("Runtime when using 2-way quick sort: %f (second)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(a);
    
    start = clock();
    quicksort_3_way(b, 0, MAX - 1);
    end = clock();
    printf("Runtime when using 3-way quick sort: %f (second)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(b);

    start = clock();
    qsort(c, MAX, sizeof(int), int_compare);
    end = clock();
    printf("Runtime when using qsort function of cstdlib library: %f (second)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(c);
    return 0;
}

