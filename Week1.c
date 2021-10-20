#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10
int *createArray(int n){
	int i;
	int *a =(int *)malloc (n*sizeof(int));
	srand(time(NULL));
	for (i=0; i<n;i++) *(a+i)= rand()%MAX;
	return a;
}
int *dumpArray(int *a, int n){
	int *b = (int*)malloc (n*sizeof(int));
	memcpy(b, a, n*sizeof(int));
	return b;
}
void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void sort3way (int a[], int l, int r){
	if (r<=l) return;
	int i= l-1, j= r;
	int p= l-1, q= r, pivot=a[r];
	for(;;){
		while(a[++i] < pivot);
		while(pivot<a[--j]) if (j==l) break;
		if (i>=j) break;
		swap(&a[i], &a[j]);
		if (a[i]==pivot) {
			p++;
			swap(&a[p], &a[i]);
		}
		if (a[j]==pivot) {
			q--;
			swap(&a[q], &a[j]);
		}
	}
	swap(&a[i], &a[r]);
	j = i-1;
	i++;
	int k;
	for (k= l; k< p; k++, j--) swap(&a[k], &a[j]);
	for (k= r-1; k >q; k--, i++) swap(&a[i], &a[k]);
	sort3way(a, l, j);
	sort3way(a, i, r);
}
void sort2way (int a[], int l, int r){
	if (r<=l) return;
	int i= l-1, j= r, pivot=a[r];
	for(;;){
		while (a[i++]< pivot);
		while (pivot< a[--j]) if (j==l) break;
		if (i>=j) break;
		swap (&a[i], &a[j]);
	}
	swap(&a[i], &a[r]);
	sort2way(a, l, i-1);
	sort2way(a, i+1, r);
}
void output(int a[], int n){
	int i;
	for (i=0; i<n; i++){
		printf("%d  ", a[i]);
	}
	printf("\n");
}
int int_compare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x);
	n = *((int*)y); 
	if ( m == n ) return 0;
	return m > n ? 1: -1;
}
int main(){
	int *a1, *a2, *a3;
	int n =1000000;
	a1= createArray(n);
	a2= dumpArray(a1, n);
	a3= dumpArray(a2, n);
	//output(a1, n);
	//output(a2, n);
	//output(a3, n);
	clock_t start, end;
	start = clock();
	qsort(a3, n, sizeof(int), int_compare);
	end= clock();
	printf("Sorting time of Qsort is: %f \n", (double)(end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	sort2way(a1, 0, n-1);
	end= clock();
	printf("Sorting time of Sort2way is: %f \n", (double)(end-start)/CLOCKS_PER_SEC);
	
	start = clock();
	sort3way(a2, 0, n-1);
	end= clock();
	printf("Sorting time of Sort3way is: %f \n", (double)(end-start)/CLOCKS_PER_SEC);
	
	
	//output(a1, n);
	//output(a2, n);
	//output(a3, n);
	free(a1);
	free(a2);
	free(a3);
	return 0;
}
