#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int search(int* arr, char* log, int length);

void print_array(int* arr, int length)
{
  for(int i = 0; i < length; i++) printf("%d, ", arr[i]);
  printf("\b\b  \n");
}

void copy_array(int* arr1, int* arr2, int length)
{
  for(int i = 0; i < length; i++)
    arr2[i] = arr1[i];
}

int search_operation(int* arr, int i, int j, char* log, int length, char operation)
{
  // calc value
  int temp[length-1];
  switch(operation)
  {
  case '+':
    temp[0] = arr[i] + arr[j];
    break;
  case '-':
    temp[0] = arr[i] - arr[j];
    if (temp[0] < 0) return false;
    break;
  case '*':
    temp[0] = arr[i] * arr[j];
    break;
  case '/':
    if (arr[j] <= 0) return false;
    temp[0] = arr[i] / arr[j];
    break;
  }

  // copy remaining values into temp 
  for(int k = 1; k < length - 1; k++)
  {
    if((j + k) % length == i) temp[k] = arr[(j + k + 1) % length];
    else temp[k] = arr[(j + k) % length];
  }

  // add log entry
  char entry[20];
  sprintf(entry, "%d %c %d = %d, ", arr[i], operation, arr[j], temp[0]);
  strcat(log, entry);

  // base case: no remaining calc available
  if(length == 2 && temp[0] == 24)
  {
    printf("%s\b\b  \n", log);
    return true;
  }
  else
  {
    search(temp, log, length - 1);
  }
}

int search(int* arr, char* log, int length)
{
  char str[80];
  // search non-commutative operations
  for(int i = 0; i < length; i++)
    {
      for(int j = 0; j < length; j++)
      {
	if(i != j)
	{
	  strcpy(str, log);
	  search_operation(arr, i, j, str, length, '-');
	  search_operation(arr, i, j, str, length, '/');
	}
      }
    }
  
  // search commutative operations
  for(int i = 0; i < length; i++)
  {
    for(int j = i + 1; j < length; j++)
    {
      strcpy(str, log);
      search_operation(arr, i, j, str, length, '+');
      strcpy(str, log);
      search_operation(arr, i, j, str, length, '*');
    }
  }
}

int main()
{
  int arr[] = {6,2,8,24};
  char log[200];
  search(arr, log, 4);
}
