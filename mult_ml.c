#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float data [][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8}
};

#define data_lenght sizeof(data)/sizeof(data[0])

float cost(float x)
{
    float cost = 0;

    for (int j = 0; j<data_lenght; j++)
        {
            float y = x*data[j][0];
            float d = data[j][1] - y;
            cost += d*d;
        }
    cost = cost/data_lenght;
    return cost;
}

int main()
{
    srand(time(0));
    float x = (float) (rand()/ (float) RAND_MAX)*10.f;

    float eps = 1e-3;
    float rate = 1e-2;

    for (int i = 0; i<10000; i++){
        float c = cost(x);
        float dcost = (cost(x+eps)-cost(x))/eps;
        x -= rate*dcost; 
        printf("%f\n", cost(x));
    }
    printf("%f\n", x);
}