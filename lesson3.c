#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ini_size 10
#define incre_size 10

typedef struct
{
  void* key;
  void* value;
}entry;

typedef struct
{
  entry *array;
  int total;
  int size;
  entry (*makenode)(void*, void*);
  int (*compare)(void*, void*);
}SymbolTable;

entry makePhone(void* name, void* phone)
{
  entry res;
  res.key = strdup( (char*)name );
  res.value = malloc(sizeof(long));
  memcpy( res.value, phone, sizeof(long) );
  return res;
}

int comparePhone(void * key1, void* key2) {
return strcmp((char*)key1, (char*)key2);
}

SymbolTable* make_table(entry (*makeNode)(void*, void*),  int (*compare)(void*, void*))
{
   SymbolTable *a= malloc(sizeof(SymbolTable));
  a->array= malloc(ini_size*sizeof(entry));
  a->total = 0;
  a->size= ini_size;
  a->makenode=makeNode;
  a->compare= compare;
  return a;
}



int BinarySearch(entry *array,int (*compare)(void*, void*), int start_index, int end_index, char *name, int *found)
{
   if (end_index >= start_index){
      int middle = start_index + (end_index - start_index )/2;
      if (compare(array[middle].key, name)==0)
	{
	  *found=1;
	  return middle;
	}
      if (compare(array[middle].key , name)>0)
	return BinarySearch(array, compare, start_index, middle-1, name, found);
      return BinarySearch(array, compare, middle+1, end_index, name, found);
   }
   *found=0;
   return start_index;
}



void add_phone(char* name, long number, SymbolTable *book)
{
  int found;
  int index=BinarySearch(book->array, book->compare , 0, book->total-1, name, &found);
  if(found==1)
    {
      book->array[index]=book->makenode(name, &number);
    }
  else
    {      
      if(book->total+1==book->size)
	{
	  book->array=realloc(book->array, (book->size+incre_size)*sizeof(entry));
	}
     
      memcpy(&(book->array[index+1]), &(book->array[index]), (book->total-index)*sizeof(entry));
      book->array[index]=book->makenode(name, &number);
      book->total=book->total+1;
    }
}

entry* getphone(char *name, SymbolTable* book)
{
  int found;
  int index=BinarySearch(book->array, book->compare, 0, book->total-1, name, &found);
  if(found=1)
    {
      return &(book->array[index]);
    }
  return NULL;
}

void print(SymbolTable* book)
{
  for(int i=0; i<book->total; i++)
    {
      printf("%s %li\n",(char*)book->array[i].key, *(long int*)(book->array[i].value) );
    }
}

int main()
{
  
  SymbolTable* book= make_table(makePhone, comparePhone);
  char s[30];
  long int a;
  printf("nhập số điện thoại \n");



  /*printf("========================\n");
  printf("nhập tên cần tìm: ");
  scanf("%s", s);
  entry* x=getphone(s, book);
  printf("%s %li\n",(char*)x->key, *(long int*)x->value) ;
  */
  while(1==1)
    {
      printf("========================\n");
      printf("nhập số mới:\n");
      scanf("%s %li", s,&a);
      add_phone(s, a, book);
      printf("========================\n");
      print(book);
    }
}
