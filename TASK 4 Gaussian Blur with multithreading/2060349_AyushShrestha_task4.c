// Name : Ayush Shrestha	UniID : 2060349

#include<stdio.h>
#include<stdlib.h>
#include"lodepng.h"
#include<pthread.h>

pthread_mutex_t mutex1;
unsigned char* ImageOne,* ImageTwo;
unsigned int w, h, r, g, b, t;

// structure definition
struct thread
{
	int start;
	int end;
};

// gaussianBlur function applies gaussian blur filter on the image
void* gaussianBlur(void *p)
{
	struct thread *pt = (struct thread*)p;
	int start = pt->start;
	int end = pt->end;
	int i, j;
    
    // To prevent race condition
    pthread_mutex_lock(&mutex1);
	for(i = start; i < end; i++)
    {
        for(j = 0; j < w; j++)
        {
            r = ImageOne[4 * w * i + 4 * j + 0];
            g = ImageOne[4 * w * i + 4 * j + 1];
            b = ImageOne[4 * w * i + 4 * j + 2];
            t = ImageOne[4 * w * i + 4 * j + 3];

            if(i == 0 && j == 0)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * 1 + 0] + ImageOne[4 * w * 1 + 4 * j + 0] + ImageOne[4 * w * 1 + 4 * 1 + 0]) / 4;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * 1 + 1] + ImageOne[4 * w * 1 + 4 * j + 1] + ImageOne[4 * w * 1 + 4 * 1 + 1]) / 4;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * 1 + 2] + ImageOne[4 * w * 1 + 4 * j + 2] + ImageOne[4 * w * 1 + 4 * 1 + 2]) / 4;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * 1 + 3] + ImageOne[4 * w * 1 + 4 * j + 3] + ImageOne[4 * w * 1 + 4 * 1 + 3]) / 4;
            }
            if(i == 0 && j != 0 && j != w - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * (j - 1) + 0] + ImageOne[4 * w * i + 4 * (j + 1) + 0] + ImageOne[4 * w * (i+1) + 4 * j + 0] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * i + 4 * (j + 1) + 0]) / 6;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * (j - 1) + 1] + ImageOne[4 * w * i + 4 * (j + 1) + 1] + ImageOne[4 * w * (i+1) + 4 * j + 1] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * i + 4 * (j + 1) + 1]) / 6;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * (j - 1) + 2] + ImageOne[4 * w * i + 4 * (j + 1) + 2] + ImageOne[4 * w * (i+1) + 4 * j + 2] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * i + 4 * (j + 1) + 2]) / 6;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * (j - 1) + 3] + ImageOne[4 * w * i + 4 * (j + 1) + 3] + ImageOne[4 * w * (i+1) + 4 * j + 3] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * i + 4 * (j + 1) + 3]) / 6;	
            }
                
                
            if(i == 0 && j == w - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * (j - 1) + 0] + ImageOne[4 * w * 1 + 4 * (j - 1) + 0] + ImageOne[4 * w * 1 + 4 * j + 0]) / 4;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * (j - 1) + 1] + ImageOne[4 * w * 1 + 4 * (j - 1) + 1] + ImageOne[4 * w * 1 + 4 * j + 1]) / 4;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * (j - 1) + 2] + ImageOne[4 * w * 1 + 4 * (j - 1) + 2] + ImageOne[4 * w * 1 + 4 * j + 2]) / 4;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * (j - 1) + 3] + ImageOne[4 * w * 1 + 4 * (j - 1) + 3] + ImageOne[4 * w * 1 + 4 * j + 3]) / 4;
            }

            if(i == h - 1 && j == w - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 0] + ImageOne[4 * w * i + 4 * (j + 1) + 0]) / 4;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 1] + ImageOne[4 * w * i + 4 * (j + 1) + 1]) / 4;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 2] + ImageOne[4 * w * i + 4 * (j + 1) + 2]) / 4;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 3] + ImageOne[4 * w * i + 4 * (j + 1) + 3]) / 4;
            }

            if(j == 0 && i != 0 && i != h - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * (j + 1) + 0 ] + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4 * w * (i + 1) + 4 * j + 0]+ImageOne[ 4*w*(i-1) + 4 * (j + 1) + 0]+ ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 0]) / 6;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * (j + 1) + 1 ] + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4 * w * (i + 1) + 4 * j + 1]+ImageOne[ 4*w*(i-1) + 4 * (j + 1) + 1]+ ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 1]) / 6;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * (j + 1) + 2 ] + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4 * w * (i + 1) + 4 * j + 2]+ImageOne[ 4*w*(i-1) + 4 * (j + 1) + 2]+ ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 2]) / 6;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * (j + 1) + 3 ] + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4 * w * (i + 1) + 4 * j + 3]+ImageOne[ 4*w*(i-1) + 4 * (j + 1) + 3]+ ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 3]) / 6;
            }
            if(j == w - 1 && i != 0 && i != h - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4 * w * (i + 1) + 4 * j + 0] +ImageOne[4 * w * i + 4 * (j - 1) + 0] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 0]) / 6;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4 * w * (i + 1) + 4 * j + 1] +ImageOne[4 * w * i + 4 * (j - 1) + 1] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 1]) / 6;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4 * w * (i + 1) + 4 * j + 2] +ImageOne[4 * w * i + 4 * (j - 1) + 2] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 2]) / 6;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4 * w * (i + 1) + 4 * j + 3] +ImageOne[4 * w * i + 4 * (j - 1) + 3] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 3]) / 6;
            }

            if(i == h - 1 && j == 0)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * i + 4 * (j - 1) + 0]) / 4;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * i + 4 * (j - 1) + 1]) / 4;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * i + 4 * (j - 1) + 2]) / 4;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * i + 4 * (j - 1) + 3]) / 4;
            }

            if(i == h - 1 && j != 0 && j != w - 1)
            {
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * j + 0] + ImageOne[4 * w * i + 4 * (j + 1) + 0] + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 0]) / 6;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * j + 1] + ImageOne[4 * w * i + 4 * (j + 1) + 1] + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 1]) / 6;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * j + 2] + ImageOne[4 * w * i + 4 * (j + 1) + 2] + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 2]) / 6;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * j + 3] + ImageOne[4 * w * i + 4 * (j + 1) + 3] + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 3]) / 6;
            }

            if( i != 0 && i != h - 1 && j != 0 && j != w - 1 )
            {    
                ImageTwo[4 * w * i + 4 * j + 0] = (r + ImageOne[4 * w * i + 4 * (j - 1) + 0] + ImageOne[4 * w * i + 4 * (j + 1) + 0] + ImageOne[4 * w * (i - 1) + 4 * j + 0] + ImageOne[4*w*(i+1) + 4*j+0 ] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 0] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 0] + ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 0]) / 9;
                ImageTwo[4 * w * i + 4 * j + 1] = (g + ImageOne[4 * w * i + 4 * (j - 1) + 1] + ImageOne[4 * w * i + 4 * (j + 1) + 1] + ImageOne[4 * w * (i - 1) + 4 * j + 1] + ImageOne[4*w*(i+1) + 4*j+1 ] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 1] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 1] + ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 1]) / 9;
                ImageTwo[4 * w * i + 4 * j + 2] = (b + ImageOne[4 * w * i + 4 * (j - 1) + 2] + ImageOne[4 * w * i + 4 * (j + 1) + 2] + ImageOne[4 * w * (i - 1) + 4 * j + 2] + ImageOne[4*w*(i+1) + 4*j+2 ] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 2] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 2] + ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 2]) / 9;
                ImageTwo[4 * w * i + 4 * j + 3] = (t + ImageOne[4 * w * i + 4 * (j - 1) + 3] + ImageOne[4 * w * i + 4 * (j + 1) + 3] + ImageOne[4 * w * (i - 1) + 4 * j + 3] + ImageOne[4*w*(i+1) + 4*j+3 ] + ImageOne[4 * w * (i - 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * (i - 1) + 4 * (j + 1) + 3] + ImageOne[4 * w * (i + 1) + 4 * (j - 1) + 3] + ImageOne[4 * w * (i + 1) + 4 * (j + 1) + 3]) / 9;
            }
        }
    }
    pthread_mutex_unlock(&mutex1);
	pthread_exit(NULL);	
}


int main()
{
    char input[100],output[100];
    unsigned int err,er;
    int numThread;

    printf("Enter image name : ");
    scanf("%s",input);
    err = lodepng_decode32_file(&ImageOne,&w,&h,input);
    
    if(err)
    {
        printf("%d %s",err,lodepng_error_text(err));
        exit(-1);
        // Program exits if err does not return 0;
    }
    else
	{
		printf("Height of image is: %d pixels\nWidth of image is: %d pixels.\n", h, w);
	}
    
    // Dynamic memory allocation
    ImageTwo = (char *)malloc(w * h * 4 * sizeof(char));

    printf("Enter output image name : ");
    scanf("%s",output);

    printf("Enter number of threads : ");
    scanf("%d",&numThread);
    
    // Initializing mutex
    pthread_mutex_init(&mutex1, NULL);
    pthread_t thrd[numThread];
    // Making an array of structure
    struct thread st[numThread];

    // Slicing the iterarions equally to all the threads 
    int slice[numThread],i;

    for(i=0;i<numThread;i++)
    {
        slice[i] = h / numThread;
    }

    int remainder = h % numThread;
    for(i=0;i<remainder;i++)
    {
        slice[i]=slice[i]+1;
    }
    // Division
    for(i=0;i<numThread;i++)
    {	
        for(i=0;i<numThread;i++)
        {	
            if(i==0)
            {
                st[i].start=0;
            }
            else
            {
                st[i].start=st[i-1].end;
            }
            st[i].end=st[i].start+slice[i];
        }
        // Creating threads
        for(i=0;i<numThread;i++)
        {
            er = pthread_create(&thrd[i],NULL,gaussianBlur,&st[i]);
            if (er != 0)
		    {
                printf("Can't create thread error = %d\n", err);
                exit(-1);
                // Program exits if er does not return 0;
            }
        }
        // Joining threads
        for(i=0;i<numThread;i++)
        {
            pthread_join(thrd[i],NULL);
        }
    }
    lodepng_encode32_file(output,ImageTwo,w,h);
    // Destroying mutex
    pthread_mutex_destroy(&mutex1);
    // Freeing the memory allocated by ImageTwo
    free(ImageTwo);
    
    return 0;
}