#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#define buf 1024

int cp_file(char *src,char *dest)
{

	FILE *file1;
	FILE *file2;
	file1=fopen(src,"r");
	char *line;
	size_t len = 0;
	ssize_t input =0;
	int start=0;
		if(file1!=NULL)
		{
		file2=fopen(dest,"w");
			while((input = getline(&line,&len,file1)) !=-1)
			{

			fputs(line,file2);

			}
		}
		else
		{
		printf("connot open file (%s)\n",src);
		return 0;
		}
	fclose(file1);
	fclose(file2);
	return 0;
}

int cp_dir(char *src,char *dest,char *name)
{
	DIR *dp;
	struct dirent *dir;
	char *srcp;
	char *destp;
	char *d_name;
	struct stat std;
	srcp=malloc(buf);
	destp=malloc(buf);
	d_name=malloc(buf);
	strcpy(d_name,dest);
	strcat(d_name,"/");
	strcat(d_name,name);
	mkdir(d_name,0777);
		if((dp = opendir(src))!=NULL)
		{

			while((dir=readdir(dp))!=NULL)
			{
			stat(dir->d_name,&std);
				if(S_ISDIR(std.st_mode))
				{
					continue;
				}

				else
				{
					strcpy(destp,d_name);
					strcat(destp,"/");
					strcat(destp,dir->d_name);
					strcpy(srcp,src);
					strcat(srcp,"/");
					strcat(srcp,dir->d_name);
					cp_file(srcp,destp);
				}
			}

		}
		else
		{
		printf("cannot open directory\n");
		}
return 0;
}

int main(int argc,char *argv[])
{
	DIR *dp;
	struct dirent *dir;
	struct stat sts;
	struct stat std;
	int start=0;
	 
		if(argc<3)
		{
			printf("cp error");
			return 0;
		}
		else if(argc==3)
		{
			if(stat(argv[1],&sts)==0)
			{
				if(S_ISDIR(sts.st_mode))
				{
				printf(" cp cannot copy ad directory without -r flag\n");
				}
				else
				{
					char *file=malloc(strlen(argv[2])+1);
					strcpy(file,argv[2]);
					stat(argv[2],&std);
						if(S_ISDIR(std.st_mode))
						{
							strcat(file,"/");
							strcat(file,argv[1]);

							cp_file(argv[1],file);
						}
						else{
							cp_file(argv[1],file);
						}

				}
			}
			else
			{
			perror("cp");
			return 0;
			}
		}
		else
		{
			char *dest=malloc(1024);
			if(stat(argv[argc-1],&std)==0)
			{
				if(strcmp(argv[1],"-r")==0)
				{
				start=1;
				}

				if(S_ISDIR(std.st_mode))
				{
					for(int i=start+1;i<argc-1;i++)
					{
						strcpy(dest,argv[argc-1]);
						strcat(dest,"/");
						strcat(dest,argv[i]);

						if(stat(argv[i],&sts)==0)
						{
							if(S_ISDIR(sts.st_mode))
							{
								char *s_name=argv[i];
								cp_dir(argv[i],argv[argc-1],s_name);
							}
							else
							{
								cp_file(argv[i],dest);
							}
							
						}
						else
						{
							printf("File does not exists");
						}
					}
				}
				else
				{
				printf("error here");
				}
			}
			else
			{
			printf("error here");
			}
		}
return 0;	
}
