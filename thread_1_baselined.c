/***************************************************************************
*       FILENAME :thread_1.c 
*       DESCRIPTION:Contains Code for a program that demonstrates the
*       use of pthread calls.The created threads will accept an 
*	argument and return the argument after adding a number.
*       Compile using gcc lfy_thread_1.c -o mythread -lpthread
*       run in the shell prompt providing a number as cmd line arg.
****************************************************************************/
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct ThreadIdAndData
{
    pthread_t   thread;       //Thread identifer 
    int         value;        //Value passed to Thread 
    int         status;       //keeps track if this is a valid thread 
} ThreadIdAndData;

void *thread_entry(void *arg)
{
	int *p;
	p=(int*)arg;
        *p = (*p) + 10;
	pthread_exit(p);
}

int main(int argc, char* argv[])
{
	ThreadIdAndData* threads;
	int t;
        int ret;
	int numthreads = 0;
        void* thread_result;

        if (( argc < 2 ) || ((numthreads = atoi(argv[1])) <= 0))
	{
    		printf("Usage: %s <number>\nThe number(should be > 0) represents the number of threads to start\n", argv[0]);
    		exit(1);
	}

	threads = calloc(numthreads,  sizeof(ThreadIdAndData));
	if (NULL == threads)
	{
		printf("Failed to alocate memory in malloc\n");
		exit(1);
	}

	/*Creating the Threads*/
	for(t=0; t < numthreads; t++)
	{
		printf("Creating Thread\n");
                threads[t].value = t;
		threads[t].status  = pthread_create(&threads[t].thread,NULL,thread_entry,(void*)&threads[t].value);
                //Non zero returns means the pthread_create failed
	 	if(threads[t].status )
		{ 
			printf("Error Creating Thread\n");
		}
		
	}
	//Now waiting for all the threads using pthread_join
	for(t=0; t < numthreads; t++)
	{
		
                if (threads[t].status == 0)//Threads which were created successfully
		{
                	ret  = pthread_join(threads[t].thread, &thread_result);
			if(ret)
			{ 
				printf("Error joining a thread");
			}
			else
			{
				printf("Joined thread returned %d\n", *((int*)thread_result));
			}
		}
	}
	free(threads);
 	
	return 0;	
}
