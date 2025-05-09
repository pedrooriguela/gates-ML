#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
    float or_w1;
    float or_w2;
    float or_b;
    float nand_w1;
    float nand_w2;
    float nand_b;
    float and_w1;
    float and_w2;
    float and_b;
} Xor;

typedef float train[3];

train data_xor [] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

train data_and [] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1}
};

train data_or [] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}
};

train data_nand [] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}
};

train data_nor [] = {
    {0, 0, 1},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 0}
};

train *data = data_xor;

int data_lenght = 4;

float sigmoidf(float x)
{
    return 1/(1+expf(-x));
}

float foward(float x, float y, Xor m){
    float a = sigmoidf(m.or_w1*x + m.or_w2*y + m.or_b);
    float b = sigmoidf(m.nand_w1*x +m.nand_w2*y + m.nand_b);
    return sigmoidf(m.and_w1*a+m.and_w2*b+m.and_b);
}


float cost(Xor m)
{
    float cost = 0;

    for (int j = 0; j<data_lenght; j++)
        {
            float x1 = data[j][0];
            float x2 = data[j][1];
            float y = foward(x1, x2, m);
            float d = y - data[j][2];
            cost += d*d;
        }
    cost = cost/data_lenght;
    return cost;
}

Xor rand_xor()
{
    Xor m;
    m.or_w1 = (float) (rand()/ (float) RAND_MAX);
    m.or_w2 = (float) (rand()/ (float) RAND_MAX);
    m.or_b = (float) (rand()/ (float) RAND_MAX);
    m.nand_w1 = (float) (rand()/ (float) RAND_MAX);
    m.nand_w2 = (float) (rand()/ (float) RAND_MAX);
    m.nand_b = (float) (rand()/ (float) RAND_MAX);
    m.and_w1 = (float) (rand()/ (float) RAND_MAX);
    m.and_w2 = (float) (rand()/ (float) RAND_MAX);
    m.and_b = (float) (rand()/ (float) RAND_MAX);
    return m;
}

void print_xor (Xor m)
{
    printf("or_w1: %f\n", m.or_w1);
    printf("or_w2: %f\n", m.or_w2);
    printf("or_b: %f\n", m.or_b);
    printf("nand_w1: %f\n", m.nand_w1);
    printf("nand_w2: %f\n", m.nand_w2);
    printf("nand_b: %f\n", m.nand_b);
    printf("and_w1: %f\n", m.and_w1);
    printf("and_w2: %f\n", m.and_w2);
    printf("and_b: %f\n", m.and_b);
    
}

Xor gradiente (Xor m, float eps)
{
    Xor g;
    float c = cost(m);
    float saved;

    saved = m.or_w1;
    m.or_w1 +=eps;
    g.or_w1 = (cost(m)-c)/eps;
    m.or_w1 = saved;

    saved = m.or_w2;
    m.or_w2 +=eps;
    g.or_w2 = (cost(m)-c)/eps;
    m.or_w2 = saved;

    saved = m.or_b;
    m.or_b +=eps;
    g.or_b = (cost(m)-c)/eps;
    m.or_b = saved;

    saved = m.nand_w1;
    m.nand_w1 +=eps;
    g.nand_w1 = (cost(m)-c)/eps;
    m.nand_w1 = saved;

    saved = m.nand_w2;
    m.nand_w2 +=eps;
    g.nand_w2 = (cost(m)-c)/eps;
    m.nand_w2 = saved;

    saved = m.nand_b;
    m.nand_b +=eps;
    g.nand_b = (cost(m)-c)/eps;
    m.nand_b = saved;

    saved = m.and_w1;
    m.and_w1 +=eps;
    g.and_w1 = (cost(m)-c)/eps;
    m.and_w1 = saved;

    saved = m.and_w2;
    m.and_w2 +=eps;
    g.and_w2 = (cost(m)-c)/eps;
    m.and_w2 = saved;

    saved = m.and_b;
    m.and_b +=eps;
    g.and_b = (cost(m)-c)/eps;
    m.and_b = saved;
    return g;
}

Xor learn(Xor m, Xor g, float rate)
{
    m.or_w1 -= rate*g.or_w1;
    m.or_w2 -= rate*g.or_w2;
    m.or_b -= rate*g.or_b;
    m.nand_w1 -= rate*g.nand_w1;
    m.nand_w2 -= rate*g.nand_w2;
    m.nand_b -= rate*g.nand_b;
    m.and_w1 -= rate*g.and_w1;
    m.and_w2 -= rate*g.and_w2;
    m.and_b -= rate*g.and_b;
    return m;
}

int main()
{
    srand(time(0));
    float eps = 1e-1;
    float rate = 1e-1;
    Xor m = rand_xor();
    for(int i=0; i<1000*1000; i++){
        Xor g = gradiente(m, eps);
        m = learn(m, g, rate);
    }
    
    printf("-------------------------------- xor gate\n");

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%zu ^ %zu = %f\n", i, j, foward(i, j, m));
        }
    }

    printf("-------------------------------- or gate\n");

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%zu | %zu = %f\n", i, j, sigmoidf(m.or_w1*i + m.or_w2*j + m.or_b));
        }
    }

    printf("-------------------------------- nand gate\n");

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%zu ~& %zu = %f\n", i, j, sigmoidf(m.nand_w1*i + m.nand_w2*j + m.nand_b));
        }
    }

    printf("-------------------------------- and gate\n");

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%zu & %zu = %f\n", i, j, sigmoidf(m.and_w1*i + m.and_w2*j + m.and_b));
        }
    }

    return 0;
}

