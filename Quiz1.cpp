#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX 10000000

int *createArray(int n){
	int *a=(int*)malloc(n*sizeof(int));
	srand(time(NULL));
	for(int i=0;i<n;i++)
	*(a+i)=rand()%MAX;
	return a;
	}

int *dumpArray(int* a,int n){
	int *b=(int*)malloc(n*sizeof(int));
	memcpy(b,a,n*sizeof(int));
	return b;
	}

void swap(int *a,int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
	}

void qsort_2way(int a[], int l, int r)
{
    int i = l - 1, j = r;
    int pivot = a[r];

    if (r <= l)
        return;

    while(true)
    {
        while (a[++i] < pivot) ;
        while(pivot < a[--j])
        {
            if (j == l)
                break;
        }
        if (i >= j)
            break;

        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[r]);

    qsort_2way(a, l, i - 1);
    qsort_2way(a, i + 1, r);
}  

void qsort_3way(int a[],int l,int r){

    int i,j,p,q,pivot,k;

    i=l-1; j=r; p=l-1; q=r; pivot=a[r];

    if (r<=l) return;

    for (;;){

        while (a[++i]<pivot);

        while (a[--j]>pivot) if (j==l) break;

        if (i>=j) break;

        swap(&a[i],&a[j]);

        if (a[i]==pivot){

            p++;

            swap(&a[p],&a[i]);

        }

        if (a[j]==pivot){

            q--;

            swap(&a[q],&a[j]);

        }

    }

    swap(&a[i],&a[r]);

    j=i-1; i++;

    for (k=l;k<p;k++,j--) swap(&a[k],&a[j]);

    for (k=r-1;k>q;k--,i++) swap(&a[i],&a[k]); 
    

    qsort_3way(a,l,j);

    qsort_3way(a,i,r);

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
    qsort_2way(a, 0, MAX - 1);
    end = clock();
    printf("Runtime of 2-way quick sort: %f (s)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(a);
    
    start = clock();
    qsort_3way(b, 0, MAX - 1);
    end = clock();
    printf("Runtime of 3-way quick sort: %f (s)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(b);

    start = clock();
    qsort(c, MAX, sizeof(int), int_compare);
    end = clock();
    printf("Runtime of qsort function : %f (s)\n", (double) (end - start) / CLOCKS_PER_SEC);
    free(c);
    return 0;}

