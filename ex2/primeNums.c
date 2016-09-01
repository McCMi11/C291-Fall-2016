#include<stdio.h>

int main(){
  int i = 4;
  int primeNums[100];
  int j = 2;
  primeNums[0] = 2;
  primeNums[1] = 3;
  printf("2\n3\n");
  for(i; i<100;i++){
    int k = 1;
    int check = 0;
    /**  1 and 0 are acting like boolean operators.
         if 1 the number isnt prime
         if 0 it is prime

         it will check all the numbers to see if a prime
         number divides equally into it or not.
         if it does its not prime.
         then it adds prime numbers to list and increments j
         as the placeholder of index of empty slot in prime
         number list.
    */ 
    for(k;k<j;k++){
      if(i %  primeNums[k] ==  0){
        check = 1;
      }
    }
    if(check != 1){
      primeNums[j] = i;
      printf("%d\n",primeNums[j]);
      j++;
    }
  }
  return 0;
}
