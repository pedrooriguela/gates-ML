#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float data [][3] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

#define data_lenght sizeof(data)/sizeof(data[0])


float sigmoidf(float x)
{
    return 1/(1+expf(-x));
}

float cost(float x1, float x2, float b)
{
    float cost = 0;

    for (int j = 0; j<data_lenght; j++)
        {
            float y = sigmoidf(x1*data[j][0] + x2*data[j][1] + b);
            float d = y - data[j][2];
            cost += d*d;
        }
    cost = cost/data_lenght;
    return cost;
}

int main()
{
    srand(time(0));
    float x1 = (float) (rand()/ (float) RAND_MAX);
    float x2 = (float) (rand()/ (float) RAND_MAX);
    float b = (float) (rand()/ (float) RAND_MAX);


    float eps = 1e-1;
    float rate = 1e-1;

    for (int i = 0; i<10000000; i++){
        float c = cost(x1, x2, b);
        float dx1 = (cost(x1+eps, x2, b)-c)/eps;
        float dx2 = (cost(x1, x2+eps, b)-c)/eps;
        float db = (cost(x1, x2, b+eps)-c)/eps;
        x1 -= rate*dx1; 
        x2 -= rate*dx2;
        b -= rate*db;
    }
    printf("cost: %f\n", cost(x1, x2, b));
    printf("x1 = %f x2 = %f\n", x1, x2);

    
    printf("0 | 0 = %f\n", sigmoidf(x1*data[0][0]+x2*data[0][1]+b));
    printf("0 | 1 = %f\n", sigmoidf(x1*data[1][0]+x2*data[1][1]+b));
    printf("1 | 0 = %f\n", sigmoidf(x1*data[2][0]+x2*data[2][1]+b));
    printf("1 | 1 = %f\n", sigmoidf(x1*data[3][0]+x2*data[3][1]+b));
        
}