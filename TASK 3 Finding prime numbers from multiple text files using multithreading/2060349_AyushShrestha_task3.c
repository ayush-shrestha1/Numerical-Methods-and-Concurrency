// Name : Ayush Shrestha	UniID : 2060349

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#define fileNUM 3

//defining mutex variable mutex1
pthread_mutex_t mutex1;
int totalPrime = 0;

// structure definition
struct thread
{
    int length;
	int start;
	int end;
	FILE *f;
	FILE *fp;

};

// primeCheck checks if number is prime or not
int primeCheck(int x)
{
	int i,count=1;
	for(i = 2; i <= sqrt(x); i++)
	{
		if(x % i == 0)
		{
			count = 0;
			break;
		}
	}
	if(x <= 1) 
	{
		count=0; 
	}
    else if(x == 2)
	{
		count = 1;
	} 
    if (count == 1) 
    { 
        return 1; 
    } 
    else 
	{ 
        return 0;
    } 
}

// primeFunc checks all the numbers from the files and stores the prime number in PrimeNumbers.txt file
void *primeFunc(void *p)
{	
	struct thread *t = (struct thread*)p;
	int start = t->start;
	int end = t->end;
	int lenTotal = t->length;
	FILE *mfile = t->f;
	FILE *outputFile = t->fp;
	int i;
	int *num = malloc(lenTotal*sizeof(int));

	// To prevent race condition            
	pthread_mutex_lock(&mutex1);
	for(i = start; i <= end; i++)
    {
		fscanf(mfile,"%d",&num[i]);
		if(primeCheck(num[i])==1)
		{
			fprintf(outputFile,"%d\n",num[i]);
			totalPrime = totalPrime + 1;

		}
	}
	pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
}

int main()
{
	int count = 0, numThread, x, i, err;
	FILE *fptr1, *fptr2, *fptr3;
	
	// Creating a new file that contains all the datas from the files
	fptr2 = fopen("mergedfile.txt","w+"); 
	// Creating a new file to store prime numbers
	fptr3 = fopen("PrimeNumbers.txt","w");
	
    for(i = 0; i < fileNUM; i++)
    {
        char file[20];
		// Generating the file name by using sprintf function
        sprintf(file,"PrimeData%d.txt",i+1); 
        // Opening the files in read mode
		fptr1 = fopen(file,"r");
		if (fptr1 == NULL)
        {
            printf("Error in %s\n",file);
            // Program exits if the file pointer returns NULL.exit(1);
            exit(-1);
        }   

		else
		{
			while(fscanf(fptr1, "%d", &x)!=EOF)
			{
                fprintf(fptr2, "%d\n",x);
				count++;
			}
		}
	}

	fclose(fptr1);
	// rewind the merged file
	rewind(fptr2);
	
	printf("\tTotal Data in File: %d\n",count);
	
	printf("Enter the number of thread: ");
	scanf("%d",&numThread);

	// Slicing the iterarions equally to all the threads 
	int *slice = malloc(numThread * sizeof(int));
	int remainder = count % numThread;

	for(i = 0; i < numThread; i++){
		slice[i] = count / numThread;
	}
	
	// Addition of remainder
	for(i = 0; i < remainder; i++)
    {
		slice[i] = slice[i]+1;
	}
	
	int *startSlice = malloc(numThread * sizeof(int));
	int *endSlice= malloc(numThread * sizeof(int));
	
	// determine start and end values for each thread
	for(i = 0; i < numThread; i++){
		if(i==0)
        {
			startSlice[i]=0;
		}
        else
        {
			startSlice[i]= endSlice[i - 1] + 1;
		}
		endSlice[i] = startSlice[i] + slice[i] - 1;
	}
	
	struct thread *st = malloc(numThread * sizeof(struct thread));
	// Division
	for(i = 0; i < numThread; i++)
    {
		st[i].f = fptr2;
		st[i].length = count;
		st[i].start = startSlice[i];
		st[i].end = endSlice[i];
		st[i].fp = fptr3;
	}
	
	// Initializing mutex
	pthread_mutex_init(&mutex1,NULL);
    // Creating threads
	pthread_t *threadIds = malloc(numThread * sizeof(pthread_t));
	
    for(i = 0; i < numThread; i++)
    {
		err = pthread_create(&threadIds[i],NULL,primeFunc,&st[i]);
		if (err != 0)
		{
			printf("Can't create thread error = %d\n", err);
			exit(-1);
			// Program exits if err does not return 0;
		}
	}
	
	// Joining threads
	for(i = 0; i < numThread; i++)
    {
		pthread_join(threadIds[i],NULL);
	}
	
	// Destroying mutex
	pthread_mutex_destroy(&mutex1);
	
	fprintf(fptr3,"Total number of Prime Numbers are : %d\n",totalPrime);
	printf("\nAll Prime Numbers have been saved in PrimeNumbers.txt\n");
    printf("\tTotal Number of Prime Numbers : %d", totalPrime);

	// Closing the file
	fclose(fptr2);
	fclose(fptr3);

	// Deleting merged file;
	remove("mergedfile.txt");
    // Freeing the memory allocated by slice, startSlice, endSlice, st, and threadIds
    free(slice);
    free(startSlice);
    free(endSlice);
	free(st);
    free(threadIds);
	return 0;
}
