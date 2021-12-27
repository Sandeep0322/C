#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#define MAX 8024

int main(int argc, char *argv[])
{

struct dirent* files;
DIR* dir ;
DIR* dir1 ;

dir = opendir(argv[1]);

if(!dir)
printf("error");

else
{
int n=0;
while(files = readdir(dir))
{
	if(n == 0)
	n= errno;  
	printf("%s",files->d_name);
	printf("%s/%s",argv[2],files->d_name);
	struct stat st_buf;
	stat(files->d_name,&st_buf);
	if(S_ISDIR (st_buf.st_mode))
	{
		continue;
	}
	else if(S_ISREG (st_buf.st_mode))
	{
		FILE* file = fopen(files->d_name,"r");
		if(file)
		{
			char file2[MAX] = {0};
			sprintf(file2, "%s/%s",argv[2],files->d_name);

			FILE* file3 = fopen(file2,"w");
			if(file3)
			{
				char buffer[MAX] ={0};
				while(fgets(buffer,MAX,file))
				{
					fputs(buffer,file3);
				}
				fclose(file3);
			}
			else
			{
				printf("%s",file2);
			}
			fclose(file);
		}
	}
	else
	{
		printf("error in");
	}

if(n != errno)
	printf("error oc");
else
	printf(" -- copied\n");
	printf("\n");
}
}
closedir(dir);
return 0;
}

