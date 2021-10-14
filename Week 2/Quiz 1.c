#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100

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

void *memcpy(void *region1, const void *region2, size_t n) {

    const char *first = (const char*) region2;
    const char *last = ((const char*) region2) + n;
    char *result = (char*) region1;
    while (first != last) { 
        *result++ = *first++; 
    }
    return result;
}

void exch(void *buf, size_t size, int i, int j) {
    
    void *tmp = malloc(size);
    void *buf_i = buf + i * size;
    void *buf_j = buf + j * size;
    memcpy(tmp, buf_i, size);
    memcpy(buf_i, buf_j, size);
    memcpy(buf_j, tmp, size);
    free(tmp);
}

void sort(void* a, int size, int l, int r, int (*compare)(void*, void*)) {
    if (r <= l) {
        return;
    }
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (true) {
        while (compare((char*)a + (++i) * size, (char*)a + r * size) < 0);
        while (compare((char*)a + r * size, (char*)a + (--j) * size) < 0) {
            if (j == l) {
                break;
            }
        }

        if (i >= j) {
            break;
        }

        exch(a, size, i, j);
        if (compare((char*)a + i * size, (char*)a + r * size) == 0) {
            exch(a, size, ++p, i);
        }
        if (compare((char*)a + j * size, (char*)a + r * size) == 0) {
            exch(a, size, --q, j);
        }
    }
    exch(a, size, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l ; k <= p; k++) {
        exch(a, size, k, j--);
    }
    for (int k = r - 1; k >= q; k--) {
        exch(a, size, k, i++);
    }
    sort(a, size, l, j, compare);
    sort(a, size, i, r, compare);
}

int search(void *buf, int size, int l, int r, void *item, int (*compare)(void const *, void const *)) {
    
    int i, res;
    if (r < l) {
        return -1;
    }
    i = (l + r) / 2;
    res = compare(item, (char*) buf + (size * i));
    if (res == 0) {
        return i;
    } else if (res < 0) {
        return search(buf, size, l, i - 1, item, compare);
    } else {
        return search(buf, size, i + 1, r, item, compare);
    }
}

int compare(void const *x, void const *y) {
    int m, n;
    m = *((int *) x);
    n = *((int *) y);
    if (m == n) { 
        return 0;
    }
    return m > n ? 1 : -1;
}

int main() {

    int *a = createArray(MAX);
    printArray(a, MAX);

    sort(a, sizeof(int), 0, MAX - 1, compare);

    printf("After sorting:\n");
    printArray(a, MAX);
    free(a);
    return 0;
}