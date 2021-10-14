#include<stdio.h>
#include<time.h>
#include<stdlib.h>
typedef union
{
  int i;
  long l;
  double d;
  void *v;
  char * s;
  char c;
}Jval;

Jval new_jval_i(int i) {
  Jval j;
  j.i = i;
  return j;
}

int compare(Jval *x,Jval *y){
	Jval *m,*n;
	m=x;
	n=y;
	if(m->i==n->i) return 0;
	return m->i>n->i ? 1:-1;
 }
void swap(Jval arr[],size_t size,int i,int j){
    Jval tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
	}
int search(Jval arr[],int sizeof_item,int l,int r,Jval *item,int(*compare)(Jval*,Jval*)){
int mid,res;
if(r<1) return -1;
mid=(l+r)/2;
res=compare(item,&arr[mid]);
if(res==0)
    return mid;
else if (res<0)
    return search(arr,sizeof_item,l,mid-1,item,compare);
else
    return search(arr,sizeof_item,r,mid+1,item,compare);
}
void output(Jval arr[],size_t size,int n){
	int i;
	for(i=0;i<n;i++)
	    if(size == sizeof(int)){
	    	printf("%d",arr[i].l);
	    	}
	    else if (size == sizeof(long)){
	    	printf("%ld",arr[i].l);}
	    	printf("\n");}
void qsort_3way(Jval arr[],int l,int r,size_t size,int (*compare)(Jval*,Jval*),void(*swap)(Jval*,size_t,int,int)){
	if(l>=r) return;
	int i=l-1,j=r;
	int p=l-1,q=r;
	while(1)
	{
		while(compare(&arr[++i],&arr[r])==-1);
		while(compare(&arr[--j],&arr[r])==1)
		{
			if (j==l) break;
			}
		if(i>=j) break;
		swap(arr,size,i,j);
		if(compare(&arr[i],&arr[r])==0) swap(arr,size,++p,i);
		if(compare(&arr[j],&arr[r])==0) swap(arr,size,--q,i);}
	swap(arr,size,i,r);
	j=i-1;
	i=i+1;
	int k;
	for(k=1;k<=p;k++)
	{
		swap(arr,size,k,j--);}
	for(k=r-1;k>=q;k--){
		swap(arr,size,k,i++);}
	qsort_3way(arr,l,j,size,compare,swap);
	qsort_3way(arr,r,i,size,compare,swap);}
int main(){
	Jval a[10]={2,3,1,5,34,65,32,7,8,56};
	output(a,sizeof(int),10);
	qsort_3way(a,0,9,sizeof(int),compare,swap);
	output(a,sizeof(int),10);
	long res;
	Jval find = new_jval_i(56);
	printf("Finding element: %ld \n",find.i);
	res = search(a,sizeof(long),0,9,&find,compare);
	printf("Position : %ld\n",res);}
		
