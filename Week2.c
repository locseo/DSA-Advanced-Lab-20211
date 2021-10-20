#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int Jval_i(Jval j) {
    return j.i; 
}
Jval *createArray(int n){
	int i;
	Jval *a =(Jval *)malloc (n*sizeof(Jval));
	srand(time(NULL));
	for (i=0; i<n; i++){
	a[i]= new_jval_i(rand()%100);
	}
	return a;
}
/*int *dumpArray(int *a, int n){
	int *b = (int*)malloc (n*sizeof(int));
	memcpy(b, a, n*sizeof(int));
	return b;
}*/
void swap(Jval *a, Jval *b){
	Jval temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
int compare_i(Jval *x, Jval* y) {
	int m, n;
	m = Jval_i(*x);
	n = Jval_i(*y); 
	if ( m == n ) return 0;
	return m > n ? 1: -1;
}
void output(Jval *a, int n){
	int k;
	for (k=0; k<n; k++){
		printf("%d  ", a[k].i);
	}
	printf("\n");
}
int search( Jval a[], int l, int r, Jval *item, int (*compare)(Jval*, Jval*)){
	int mid, res;
	if(r<l) return -1;
	mid = (l+r)/2;
	res= compare_i(item, &a[mid]);
	if (res==0) return mid;
	else if (res<0) return search(a, 1, mid-1, item, compare_i);
	else return search(a, mid+1, r, item, compare_i);
}
void sort(Jval a[], int l, int r, int (*compare_i)(Jval*, Jval*)){
	if(r<=l) return;
	int i= l-1, j=r;
	int p= l-1, q=r; 
	Jval pivot;
	pivot =a[r];
	while(1){
		while(compare_i(&a[i++], &pivot)<0);
		while (compare_i(&a[j--], &pivot)>0){
		if (j==l) break;}
		if(i>=j) break;
		swap(&a[i], &a[j]);
		if (compare_i(&a[i], &pivot)==0){
			++p;
			swap(&a[p], &a[i]);
		}
		if (compare_i(&a[j], &pivot)==0){
			--q;
			swap(&a[q], &a[j]);
		}
	}
	swap(&a[i], &a[r]);
	j= i-1;
	i= i+1;
	int k;
	for (k= 1; k<=p; k++, j--) swap(&a[k], &a[j]);
	for (k= r-1; k>=q; k--, i++) swap(&a[k], &a[i]);
	sort(a, l, j, compare_i);
	sort(a, i, r, compare_i);
}
int main(){
	Jval *a1;
	int i, res;
	int n= 100;
	a1= createArray(n);
	output(a1, n);
	printf("Result:\n");
	sort(a1, 0, n-1, compare_i);
	output(a1, n);
	printf("Enter a number: ");
    Jval key;
    scanf("%d%*c", &(key.i));
    printf("Position of element in array: %d\n", search(a1, 0, n-1, key.i, compare_i));
	free(a1);
}
