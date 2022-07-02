// Name : Ayush Shrestha	UniID : 2060349

#include<stdio.h>
#include<pthread.h>

double pi = 0;
pthread_mutex_t mutex1;

// structure definition
struct thread
{
	long long start;
	long long end;
};

// piValue function stores the value of pi
void *piValue(void *p)
{
	struct thread *t = p;
	long long start = t->start;
	long long end = t->end;
	long long n;
	int sign;
	double sum = 0;

	// To prevent race condition
	pthread_mutex_lock(&mutex1);
	for (n = start; n <= end; n++)
	{   
		if (n % 2)
		{
			sign = -1;
		}
		else 
		{
			sign = 1;
		}
		
		sum = ((double)sign) / (2 * n + 1);	   
		pi += 4* sum;       
	}
	pthread_mutex_unlock(&mutex1);
	pthread_exit(NULL);	
}

int main()
{
	long long iteration;
	int numThread;
	int err;
	
	printf("Enter the number of iterations : ");
	scanf("%lld",&iteration);
	printf("Enter the number of threads : ");
	scanf("%d",&numThread);
	
	// Slicing the iterarions equally to all the threads 
	int slice[numThread];	
	int remainder = iteration % numThread;
	int i;
	
	for (i = 0; i < numThread; i++)
	{
		slice[i] = iteration / numThread;
	}

	for (i = 0; i < remainder; i++){
		slice[i] = slice[i]+1;
	}
	
	// Addition of remainder
	for(i = 0; i < remainder; i++)
	{
		slice[i] = slice[i] + 1; 
	}
	
	// Making an array of structure
	struct thread st[numThread];
	for(i = 0; i < numThread; i++)
	{
		if (i == 0)
		{
			st[i].start = 0;
		}
		else
		{
			st[i].start = st[i-1].end + 1;
		}
		st[i].end = st[i].start + slice[i] - 1;
	}

	// Initializing mutex
	pthread_mutex_init(&mutex1, NULL);
	pthread_t thrd[numThread];
	
	// Creating threads
	for (i = 0; i < numThread; i++)
	{
		err = pthread_create(&thrd[i],NULL,piValue,&st[i]);
		if (err != 0)
		{
			printf("Can't create thread error = %d\n", err);
			exit(-1);
			 // Program exits if err does not return 0;
		}
	}
	// Joining threads
	for (i = 0; i < numThread; i++)
	{
		pthread_join(thrd[i],NULL);
	}

	// Destroying mutex
	pthread_mutex_destroy(&mutex1);
	printf("\nUsing Leibniz formula with %lld iterations and %d threads\n",iteration,numThread);
	printf("\tApproximate value of PI is: %lf",pi);
	
	return 0;
}

