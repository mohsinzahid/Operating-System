#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<pthread.h>

void* sum(void* num)
{
	int* n = (int*)num;
	printf("Addition is %d \n",n[0]+n[1]);
	return NULL;
}

void* sub(void* num)
{
	int* n = (int*)num;
	printf("Subtraction is %d \n",n[0]-n[1]);
	return NULL;
}

void* mul(void* num)
{
	int* n = (int*)num;
	printf("multiplication is %d \n",n[0]*n[1]);
	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc == 4)
	{
		if(((argv[1][0] >= 48) && (argv[1][0] <= 57)) && ((argv[2][0] >= 48) && (argv[2][0] <= 57)) && ((argv[3][0] >= 65) && (argv[3][0] <= 90)))
		{
			int numbers[2] = {argv[1][0]-48,argv[2][0]-48};
			pthread_t pid1;
			if (argv[3][0] == 'A') //for addition
			{
				pthread_create(&pid1,NULL,&sum,(void*)numbers);
				pthread_join(pid1,NULL);
			}
			else if (argv[3][0] == 'S') //for subtraction
			{
				pthread_create(&pid1,NULL,&sub,(void*)numbers);
				pthread_join(pid1,NULL);
			}
			else if (argv[3][0] == 'M') //for multiplication
			{
				pthread_create(&pid1,NULL,&mul,(void*)numbers);
				pthread_join(pid1,NULL);
			}
			else
				printf("invalid command\n");
		}
		else
				printf("invalid command\n");
	}
	else
		printf("invalid command\n");
	return 0;
}