#include <stdio.h>

void mycat(int);

char str1[] = "Hello";
char str2[] = "World";
char dest_buffer[100];

int main() {
  mycat(7);
  printf("%s\n", dest_buffer);
  mycat(30);
  printf("%s\n",dest_buffer);
  mycat(200);
  printf("%s\n", dest_buffer);
  mycat(99);
  printf("%s\n", dest_buffer);

  return 0;
}

void mycat(int n){
  int i = 0; 
  int end;
  if(n >= 100){
    printf("You have entered %d, which is bigger than 99, only the first 99 will be saved\n", n);
    end = 99;
  }else{
    end = n;
  }

  while(i < end){
    int h = 0;
    int w = 0; 

    for(h; h < 5; h++){
      if(i < end){
        dest_buffer[i] = str1[h];
        i += 1;
      }else{break;}
    }

    for(w; w < 5; w++){
      if(i < end){
        dest_buffer[i] = str2[w];
        i += 1;
      }else{break;}

    } 
  }
  dest_buffer[end] = 0x00;
  return ;
}
