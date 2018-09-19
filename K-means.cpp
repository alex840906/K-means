#include "vector"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#define data_set 150
#define k 3
#define dim 4
using namespace std;
vector<float> w(data_set), x(data_set), y(data_set), z(data_set), SSE_distance(3);
vector<int> flower(data_set), part(data_set), random_point(k), count(3);
vector<vector<float>> centroid(k), ans_centroid(3);

void evaluate(int point, vector<vector<float>> &distance)
{
    int i;
    for (i = 0; i < data_set; i++)
    {
        int j = 0;
        distance[i][point] = sqrt(pow(w[i] - centroid[point][j], 2) + pow(x[i] - centroid[point][j + 1], 2) + pow(y[i] - centroid[point][j + 2], 2) + pow(z[i] - centroid[point][j + 3], 2));
    }
}

void partition(vector<vector<float>> distance)
{
    int i, j;

    for (i = 0; i < data_set; i++)
    {
        float min_distance = distance[i][0];
        part[i] = 0;
        for (j = 1; j < k; j++)
        {
            if (distance[i][j] <= min_distance)
            {
                min_distance = distance[i][j];
                part[i] = j;
            }
        }
    }
}

void FindCentroid(vector<vector<float>> &centroid)
{
    int h, i, j;
    for (i = 0; i < k; i++)
        for (j = 0; j < dim; j++)
            centroid[i][j] = 0;
    for (i = 0; i < k; i++)
        count[i] = 0;

    for (h = 0; h < data_set; h++)
        for (i = 0; i < k; i++)
        {
            if (part[h] == i)
            {
                j = 0;
                centroid[i][j] += w[h];
                centroid[i][j + 1] += x[h];
                centroid[i][j + 2] += y[h];
                centroid[i][j + 3] += z[h];
                count[i]++;
            }
        }

    for (i = 0; i < k; i++)
        for (j = 0; j < dim; j++)
            centroid[i][j] /= count[i];
}
void FindSSE(vector<vector<float>> &centroid)
{

    int i, j = 0, h;
    for (i = 0; i < k; i++)
        SSE_distance[i] = 0;

    for (h = 0; h < data_set; h++)
        SSE_distance[part[h]] += pow(w[h] - centroid[part[h]][0], 2) + pow(x[h] - centroid[part[h]][1], 2) + pow(y[h] - centroid[part[h]][2], 2) + pow(z[h] - centroid[part[h]][3], 2);
}

int main()
{
    int i = 0, j, r, e;
    float a, b, c, d, SSE = 0;
    int itteration = 0;

    vector<vector<float>> distance(data_set);
    for (i = 0; i < k; i++)
        random_point[i] = -1;

    srand(time(NULL));
    FILE *fp;
    fp = fopen("K-means/iris.txt", "r");

    i = 0;
    while (fscanf(fp, "%f%f%f%f%d", &a, &b, &c, &d, &e) != EOF)
    {
        w[i] = a;
        x[i] = b;
        y[i] = c;
        z[i] = d;
        flower[i] = e;
        i++;
    }

    int flag = 0;
    i = 0;
    while (i < k)
    {
        r = rand() % data_set;
        for (j = 0; j < k; j++)
        {
            if (random_point[j] == r)
                flag = 1;
        }
        if (flag == 0)
        {
            random_point[i] = r;
            i++;
        }
    }
    for (i = 0; i < k; i++)
    {
        centroid[i].resize(dim);
        centroid[i].assign(dim, 0);
    }
    for (i = 0; i < k; i++)
    {
        j = 0;
        centroid[i][j] = w[random_point[i]];
        centroid[i][j + 1] = x[random_point[i]];
        centroid[i][j + 2] = y[random_point[i]];
        centroid[i][j + 3] = z[random_point[i]];
    }

    for (i = 0; i < data_set; i++)
        distance[i].resize(k);

    while (itteration <= 10)
    {
        for (i = 0; i < k; i++)
            evaluate(i, distance); //ok

        partition(distance);

        FindCentroid(centroid);

        SSE_distance.assign(3, 0);
        FindSSE(centroid);
        SSE = 0;
        for (i = 0; i < k; i++)
            SSE += SSE_distance[i];
        
        itteration++;
    }
    ans_centroid.assign(3, vector<float>(4, 0));

        for (int h = 0; h < data_set; h++)
            for (i = 0; i < k; i++)
            {
                if (flower[h] == (i + 1))
                {
                    j = 0;
                    ans_centroid[i][j] += w[h];
                    ans_centroid[i][j + 1] += x[h];
                    ans_centroid[i][j + 2] += y[h];
                    ans_centroid[i][j + 3] += z[h];
                }
            }

        for (i = 0; i < k; i++)
            for (j = 0; j < dim; j++)
                ans_centroid[i][j] /= 50;

        vector<vector<float>> ans_distance(3, vector<float>(3, 0));
        int h = 0;
        for (i = 0; i < k; i++)
            for (j = 0; j < k; j++)
            {
                ans_distance[i][j] = sqrt(pow(centroid[i][h] - ans_centroid[j][h], 2) + pow(centroid[i][h + 1] - ans_centroid[j][h + 1], 2) + pow(centroid[i][h + 2] - ans_centroid[j][h + 2], 2) + pow(centroid[i][h + 3] - ans_centroid[j][h + 3], 2));
            }

        float min_distance;
        vector <int> ans(3);
        for (i = 0; i < k; i++)
        {
            min_distance=100;
            for (j = 0; j < k; j++)
            {
                if (min_distance>ans_distance[i][j])
                {
                    min_distance=ans_distance[i][j];
                    ans[i]=j+1;
                }
            }
        }
        for(i=0;i<data_set;i++)
            {
                if(part[i]==0)
                    part[i]=ans[0];
                else if(part[i]==1)
                    part[i]=ans[1];
                else
                    part[i]=ans[2];
            }

        int right=0;
        for(i=0;i<data_set;i++)
            if(part[i]==flower[i])
                right++;
        float accuracy=0.1;
        accuracy=(float)right/data_set*100;
        cout<<"SSE: "<<SSE<<endl;
        cout<<"Accuracy: "<<setprecision(4)<<accuracy<<"%"<<endl;
        
    system("pause");
    return 0;
}