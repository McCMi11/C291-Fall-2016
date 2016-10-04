#include <stdio.h>

int main(int argc, char *argv[]){

  FILE * infile;
  FILE * outfile;
  int c;

  infile = fopen(argv[1], "r");
  outfile = fopen(argv[2], "w");

  while(1){
    c = fgetc(infile);
    if (feof(infile)){
	break;
      }
    fputc(c, outfile);
  }
   
  fclose(infile);
  fclose(outfile);

  return 0;
}
