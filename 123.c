#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  FILE *src;
  char word[100], ch, replace[100];
  char *read;
  int p;
    src = fopen("a.out","rb+");                                //Opening the task.c output file         
    read = (char *)malloc(sizeof(src));
    
    puts("\n\nEnter the word to find:");
    fgets(word, 100, stdin);                                   //Enter word to be find 
    word[strlen(word) - 1] = word[strlen(word)];
    
    puts("Enter the word to replace it with :");
    fgets(replace, 100, stdin);                                //Enter the word to replace
    replace[strlen(replace) - 1] = replace[strlen(replace)];
    rewind(src);
    
    while (!feof(src)) {
        fscanf(src, "%s", read);                               //Output file content copy to read
        if (strcmp(read, word) == 0) {                         //Comparing the word and output file
	    fseek(src,0,SEEK_CUR);                             //Declearing the location by using seek cur
	    p=ftell(src);                                      //p is the position of the word
            printf("loaction of searched word - %d\n",p);
	    fseek(src,p-strlen(word),SEEK_SET);                         
	    fputs(replace,src);                                        //Replacing the word
	    printf("changes done");
	    fseek(src,0,SEEK_CUR);
        }

    }
}
