#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "function.h"


int main ()
{
	char* command = NULL;
	printf("If you want to quit press 'q'\n");
		while(1)
		{
			fseek(stdin,0,SEEK_END);
			printf("\nBobShell:~ $ ");
			command = get_line();
			if(((command[0] == 'q') || (command[0] == 'Q')) && (command[1] == '\n'))
				break;
			/*printf("%s", command);*/

			int argc = 0;
			char* argv[100];

			for(int i = 0; i < strlen(command);i++)
			{
				if ((command[i] == ' ') || (command[i] == '\n'))
				{
					argv[argc] = malloc(i+2);
					argc++;
				}
			}
			int j=0;
			for (int i = 0; i < argc; i++)
			{
				int z=0;
				while((command[j] != ' ') && (command[j] != '\n'))
				{
					argv[i][z] = command[j];
					z++;
					j++;
				}
				argv[i][z] = '\0';
				j++;
			}
			/*printf("The Strings are %d\n",argc);*/

			argv[argc+1]= NULL;

			char* fullpath =NULL;
			fullpath = Findpath(argv[0]);

			if(fullpath)
				{
					int pid = fork();
					// Parent

					if (pid > 0)
						{
							int status = 0 ;
							wait(&status);
							/*printf("Child exited with status of %d \n", status);*/
						}
					// Child
					else if (pid == 0)
						{
							/*printf("file open %s\n",fullpath);*/
							execvp(fullpath, argv);
						}
						else
						/*printf("path error\n");*/
						perror("error\n");
				}
			else
				{
					printf("File not Found\n");
				}


			free(command);
			for (int i = 0; i < argc; i++)
			{
				free(argv[i]);
			}
			free(fullpath);   		
		}
}