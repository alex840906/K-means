#include "vector"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <sstream>
#define data_size 150
#define k 3
#define dim 4

using namespace std;
vector<vector<string>> feature;
vector<vector<float>> centroid(3);
void init()
{
    int i = 0, r;

    while (i < k)
    {
        r = rand() % data_size;
        //for(int j=0;j<k;j++)

    }
}

int main()
{
    string line, tmp;
    int i = 0;

    srand(time(NULL));
    fstream file;
    file.open("K-means/iris.txt", ios::in);

    feature.resize(data_size);

    while (getline(file, line))
    {
        stringstream t_line(line);
        while (getline(t_line, tmp, ' '))
            feature[i].push_back(tmp);
        i++;
    }
    
    vector<int>init_point(3);
    //init()

    system("pause");
    return 0;
}