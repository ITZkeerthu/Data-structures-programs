#include <stdio.h>
int LinearSearch(int a[], int n, int key); 

int main() 
{ 
int n, a[10], i, key, pos; 
printf("Enter the limit : "); 
scanf("%d", &n); 
printf("Enter the elements : "); 
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]); 
  printf("Enter the element to search : "); 
  scanf("%d", &key); 
  pos = LinearSearch(a, n, key); 
  if (pos != -1) 
    printf("Element found at location : %d", pos); 
  else
    printf("Element not found."); 
  return 0; 
} 
int LinearSearch(int a[], int n, int key) 
{ 
int i; 
for (i = 0; i < n; i++) 
  if (a[i] == key) 
    return i; 
return -1; 
}
/*____________________________________________________________________________________
Enter the limit : 5

Enter the elements : 30 40 50 20 10

Enter the element to search : 20

Element found at location : 3
  */
