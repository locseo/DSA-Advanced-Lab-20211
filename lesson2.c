#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define N 16

typedef union
{
  int i;
  long l;
  double d;
  void *v;
  char * s;
  char c;
}Jval;

Jval new_jval_i(int i)
{
  Jval a;
  a.i=i;
  return a;
}

int jval_i(Jval a)
{
  int i= a.i;
  return i;
}

Jval *make_array_i(int n)
{
  srand(time(0)); 
  Jval * a= malloc(n*sizeof(Jval));
  for(int i=0; i<n; i++)
    {
      a[i]= new_jval_i(rand()%10+1);
     }
  return a;
}

int comfunc_i(Jval*  a, Jval* b)
{
  return jval_i(*a)-jval_i(*b);
}

void exch(Jval *array, int a,  int b)
{
  Jval temp= array[a];
  array[a]= array[b];
  array[b]= temp;
}



int search_gen(Jval * array, Jval *key, int left, int right, int (*compare)(Jval*,Jval*))
{
  if(left>right)
    {
      return -1;
    }
  int n= (left+right)/2;
  int comp= compare(&array[n], key);
  if(comp==0)
    {
      return n;
    }
  else if(comp>0)
    {
      search_gen(array, key, left, n-1, compare);
    }
  else
    {
      search_gen(array, key, n+1, right, compare);
    }
}

void sort_gen(Jval *array ,int left, int right, int (*compare)(Jval*, Jval*))
{
  if(left>=right)
    {
      return;
    }
  
  int l = left-1;
  int p= left-1;
  int r = right;
  int q= right;
  while(1==1){
    while(compare( &array[++l], &array[right])<0); 
    while(compare(&array[--r], &array[right])>0)
      {
	if(r==1) break;
      }
    if (l >= r) break; 
    exch(array, l, r);
    if(compare(&array[l], &array[right])==0)
      {
	exch(array, ++p, l);
      }
    if(compare(&array[r], &array[right])==0)
      {
	exch(array, --q, r);
      }
    }
 
  exch(array, l, right);
  r=l-1;
  l=l+1;
  for(int k=left; k<=p; k++) exch(array, k, r--);
  for(int k=right-1; k>=q; k--) exch(array,  k, l++);
  sort_gen(array, left, r, compare);
  sort_gen(array, l, right, compare);
}


void sort_i(Jval* array, int left, int right)
{
  sort_gen(array, left, right, comfunc_i);
}

int search_i(Jval* array, Jval* key, int left, int right)
{
  return search_gen(array, key, left, right, comfunc_i);
}

int main()
{
   Jval *a= make_array_i(N);
   sort_i(a, 0, N-1);
   for(int i=0; i<N; i++)
    {
      printf("%i ",jval_i(a[i]));
    }
  printf("\n");
  Jval k;
  k= new_jval_i(6);
  printf("%i\n",search_i(a, &k, 0, N-1));
}
