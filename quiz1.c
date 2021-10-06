#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
int a[10000000];
int b[10000000];
int c[10000000];


void swap(int *a, int *b)
{
  int temp=*a;
  *a=*b;
  *b=temp;
}

void quicksort(int a[], int l, int r) {

    void sort(int a[], int l, int r) {
        
        if (r <=  l) {
            return;
        }
        int i = l - 1;
        int j = r;
        int pivot = a[r];
        while (1==1) {
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

void qsort_3way(int low, int heigh)
{
  
  if(low>=heigh)
    {
      return;
    }
  int i=low-1;  
  int j=low;
  int k= heigh-2;
  // chay đến k+1 vì giá trị k luôn nhỏ hơn 1 so với số các biên chưa xét  
  for(j ; j< k+1; j++)
    {
      if(a[j]== a[heigh-1])
	{
	  swap(&a[j], &a[k]); // dồn số bằng số đang xét về sau 
	  k=k-1; // số các phần tử còn lại  không trùng -1
	  j=j-1; // giữ nguyên giá trị j 
	}
      else if(a[heigh-1]>a[j])
	{
	  i=i+1;
	  swap( &a[i], &a[j]);
	}
    }

  
  int n=i+1; // số  thứ i là số bé hơn số đang xét , n là mốc heigh mới 
  k=k+1; // từ k+1 là số trùng với số đang xét 
  for(k; k<heigh; k++)
    {
      i=i+1;
      swap( &a[k], &a[i]); // đổi số trùng vào giữa 
    }
  
  qsort_3way(low, n);
  qsort_3way(i+1, heigh);	
}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int main()
{
  for(int i=0; i<10000000; i++)
    {
      a[i] = rand() % 10;
    }
  
  memcpy(b, a, sizeof(a));
  clock_t begin = clock();
  qsort_3way(0, 10000000);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time for 3- way: %f\n", time_spent);

   begin= clock();
  quicksort(b, 0, 10000000);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time for 2- way: %f\n", time_spent);

  begin= clock();
  qsort(b, 10000000, sizeof(int), cmpfunc);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time for qsort : %f\n", time_spent);
  
}
