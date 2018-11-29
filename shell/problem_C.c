#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "function.h"

extern int errno;
extern char *environ[];



int main ()
{
	char* command = NULL;
	printf("If you want to quit press 'q'\n");
		while(1)
		{
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

			argv[argc+1]= NULL;
			
			// getting fullpath of the command

			if((argv[argc-1][0] != '<') && (argv[argc-1][0] != '>'))
			{
				char* fullpath =NULL;

				fullpath = Findpath(argv[0]);

					if(fullpath)
					{
						/*int thePipe[2];
						pipe(thePipe);*/

						int choice=-1;  // 0 for I/O redirection and 1 for pipes and -1 for others
						int j;

						for(j = 1 ; j < argc ; j++)
							{
								if((argv[j][0] == '>') || (argv[j][0] == '<'))
									{
										choice = 0;
										break;
									}
								else if(argv[j][0] == '|')
									{
										choice = 1;
										break;
									}
							}
						// Child
							char * myfifo = "/tmp/myfifo";
							mkfifo(myfifo, 0666);
							int pid = fork();
						if (pid > 0)
						{
							if(choice == 1)
							{
								
								int pid2 = fork();
								if(pid2 == 0)
								{
									int newstdout = open(myfifo,O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
									close(1);
									dup(newstdout);
									close(newstdout);
									argv[j] = NULL;
									execvp(fullpath, argv);	
								}
								else if(pid2 > 0)
									waitpid(pid, NULL, 0);
							}
							waitpid(pid, NULL, 0);
							/*printf("%s\n",strerror(errno) );*/
						}

						else if (pid == 0)
						{
							if(choice == 0)
							{
									for(int i = 1 ; i < argc ; i++)
								{
									if(argv[i][0] == '>')
									{
										
										int newstdout = open(argv[i+1],O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
										close(1);
										dup(newstdout);
										close(newstdout);
										argv[i] = NULL;
									}
									else if(argv[i][0] == '<')
									{
										
										int newstdin = open(argv[i+1],O_RDONLY);
										close(0);
										dup(newstdin);
										close(newstdin);
										argv[i] = NULL;
									}
								}
								execvp(fullpath, argv);
							}
							else if(choice == 1)
							{
								int newstdin = open(myfifo,O_RDONLY);
								close(0);
								dup(newstdin);
								close(newstdin);
								argv[j] = NULL;
								execvp(Findpath(argv[j+1]), argv);
							}
							else
							{
								execvp(fullpath, argv);	
							}
						}
					}
					else
						/*printf("path error\n");*/
						perror("error\n");

					free(fullpath);

				}
				else
					/*printf("command errir\n");*/
					perror("error");


			free(command);
			for (int i = 0; i < argc; i++)
			{
				free(argv[i]);
			}
			
		}
}