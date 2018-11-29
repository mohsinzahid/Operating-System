#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int errno;
extern char *environ[];

char * get_line(void) 
{
		//I get help from https://stackoverflow.com
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) 
    {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

char* Findpath(char* argv)  //if file found and open the it will return fullpath otherwise it will return null
{
	 char* fullpath;
	 FILE* fp;
			if(argv[0] == '/')
			{
				fullpath = argv;	
				fp = fopen(fullpath,"r");
				if(fp != NULL)
				{
					fclose(fp);
					return fullpath;
				}
			}
			else if(argv[0] == '.')
			{

				char* path = getenv("PWD");
				size_t len = strlen(path) + strlen(argv);
				fullpath = malloc(len);
				strcpy(fullpath, path);
				char * finalpath = malloc(strlen(argv));
				int i;
				if(argv[1] == '/')
				{
					for ( i = 0; i < strlen(argv)-1; i++)
					{
						finalpath[i] = argv[i+1];
					}
					finalpath[i] ='\0';
				}
				else if (argv[1] == '.')
				{
					for ( i = 0; i < strlen(argv)-2; i++)
					{
						finalpath[i] = argv[i+2];
					}
					finalpath[i] ='\0';
				}
				strcat(fullpath, finalpath);
				free(finalpath);
				fp = fopen(fullpath,"r");
				if(fp != NULL)
				{
					fclose(fp);
					return fullpath;
				}
			}
			else
			{
				char* path = getenv("PATH");
				if (path == NULL) perror("error");
				fullpath = malloc(strlen(path));
				if (fullpath == NULL) perror("error");
				
				int i=0;
				while(1)
				{
					int counter =0;
					for( ; (path[i]!=':') && (path[i]!='\0'); i++)
					{
							fullpath[counter] = path[i];
							counter++;
					}
					fullpath[counter]= '/';
					counter++;
					fullpath[counter]= '\0';
					strcat(fullpath, argv);
					fp = fopen(fullpath,"r");
					if(fp != NULL)
					{
						
						fclose(fp);
						return fullpath;
					}
					else if (path[i]=='\0')
					{
						break;
					}
					i++;
				}
			}
			return NULL;
}