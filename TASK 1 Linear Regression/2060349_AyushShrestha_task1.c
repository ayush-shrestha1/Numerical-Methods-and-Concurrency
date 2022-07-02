// Name : Ayush Shrestha	UniID : 2060349

#include <stdio.h>
#include <stdlib.h>
#define fileNUM 4

int main()
{
	char file[20];
	int x, y, n = 0;
	float sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;
	float a, b, X, Y;
	FILE *fptr;
	
    int i;

    for(i=0; i<fileNUM; i++)
    {
		// Generating the file name by using sprintf function
		sprintf(file,"datasetLR%d.txt",i+1); 
		// Opening the files in read mode
        fptr = fopen(file,"r");

        if (fptr == NULL)
        {
            printf("Error in %s\n",file);
            // Program exits if the file pointer returns NULL.exit(1);
            exit(-1);
        }   
        else
        {
			// Calculating the summation values of x, y, xy, and x square.
            while(fscanf(fptr, "%d, %d", &x, &y)!=EOF)
            {
                sumX = sumX + x;
                sumY = sumY + y;
                sumX2 = sumX2 + (x*x);
                sumXY = sumXY + (x*y);
                n++;
            }
        }
    }
	
    printf("\t%d datas has been loaded! \n",n);
    // Using Linear Regression formula
    a = ((sumY * sumX2)-(sumX*sumXY)) / ((n * sumX2) - (sumX * sumX));
    b = ((n * sumXY) - (sumX * sumY)) / ((n * sumX2) - (sumX * sumX));
    printf("Value of gradient(A) : %.4f\n",a);
    printf("Value of constant(B) : %.4f\n",b);
    printf("\nEquation of straight line :\n\ty = %.4f * x + %.4f\n", b, a);
    printf("\nEnter value of x : ");
    scanf("%f",&X);
    Y = b * X + a;
    printf("\tExpected value of y : %.4f\n",Y);
    
	// Closing the file
    fclose(fptr); 

	return 0;
}
