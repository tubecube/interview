#include <stdio.h>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include <unordered_map>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

using namespace std;

struct Data {
    int position;
    bool up;
    int height;
};

int resolve(const char* input)
{
    // parse input
    istringstream iss(input);
    string line;
    getline(iss, line);
    int num = stoi(line);
    Data data[2*num];
    for (int i=0; i<num; ++i) {
        getline(iss, line);
        istringstream mou(line);
        string start, end, height;
        getline(mou, start, ',');
        getline(mou, end, ',');
        getline(mou, height);
        data[2*i] = {stoi(start), true, stoi(height)};
        data[2*i+1] = {stoi(end), false, stoi(height)};
    }

    // sort data by position
    std::sort(data, data+2*num, 
            [](const Data& d1, const Data& d2)->bool{return d1.position == d2.position ? d1.up : d1.position < d2.position;});
    
    // for (int i=0; i<2*num; ++i) {
    //     cout << data[i].position << " " << data[i].up << " " << data[i].height << endl;
    // }

    int distance = 0;
    int currentHeight = 0;
    std::unordered_map<int,int> mountains;
    for (int i=0; i<2*num; ++i) {
        if (data[i].up) {
            mountains[data[i].height]++;
            if (data[i].height > currentHeight) {
                distance += data[i].height-currentHeight;
                currentHeight = data[i].height;
            }
        } else {
            if (mountains[data[i].height] == 1)
                mountains.erase(data[i].height);
            else
                mountains[data[i].height]--;
            if (data[i].height == currentHeight) {
                int newHeight = mountains.size() == 0 ? 0 : (max_element(mountains.begin(), mountains.end(), 
                            [](const pair<int,int>& p1, const pair<int,int>& p2)->bool{return p1.first < p2.first;}))->first;
                distance += currentHeight-newHeight;
                currentHeight = newHeight;
            }
        }
    }
    // add horizontal distance
    distance += data[2*num-1].position;
    return distance;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        "3\n1,2,2\n2,4,1\n0,3,1",
        "2\n0,2,2\n1,2,2",
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 8, 6};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
