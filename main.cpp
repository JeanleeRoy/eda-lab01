#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <math.h>
#include <queue>
#include <fstream>

using namespace std;

vector<pair<int, int>> data1;
vector<pair<int, int>> data2;
vector<pair<int, int>> data3;

vector<pair<int, int>> res1, res2, res3;

void exportDataset(int num = 1) {
    fstream file;
    string filename = (num == 1) ? "dataset1.csv" : (num==2) ? "dataset2.csv" : "dataset3.csv";
    file.open(filename, ios::out | ios::trunc);
    file.close();
    file.open(filename, ios::out | ios::app);
    if (file.is_open()) {
        if (num == 1) {
            for (auto i : data1) file << i.first << ',' << i.second << '\n';
        } else if (num == 2) {
            for (auto i : data2) file << i.first << ',' << i.second << '\n';
        } else
            for (auto i : data3) file << i.first << ',' << i.second << '\n';
    } file.close();
}

void exportKNN(int num = 1) {
    fstream file;
    string filename = (num == 1) ? "knn1.csv" : (num==2) ? "knn2.csv" : "knn3.csv";
    file.open(filename, ios::out | ios::trunc);
    file.close();
    file.open(filename, ios::out | ios::app);
    if (file.is_open()) {
        if (num == 1) {
            for (auto i : res1) file << i.first << ',' << i.second << '\n';
        } else if (num == 2) {
            for (auto i : res2) file << i.first << ',' << i.second << '\n';
        } else
            for (auto i : res3) file << i.first << ',' << i.second << '\n';
    } file.close();
}

void dataset1(int n) {
    srand (time(NULL));

    data1.clear();
    for(int i=0; i<n; i++) {
        auto x = rand() % 901;
        auto y = rand() % 901;
        data1.push_back(make_pair(x, y));
    }
}

void dataset2(int n) {
    srand (time(NULL));

    data2.clear();
    for(int i=0; i<n; i++) {
        auto x = rand() % 601 + 900;
        auto y = rand() % 601 + 900;
        data2.push_back(make_pair(x, y));
    }
}

void dataset3(int n) {

    srand (time(NULL));

    data3.clear();
    for(int i=0; i<n; i++) {
        auto x = rand() % 1501;
        auto y = rand() % 1501;
        data3.push_back(make_pair(x, y));
    }
}

float ed(pair<int, int> p1, pair<int, int> p2) {
    auto a = pow( p2.first - p1.first, 2);  // x
    auto b = pow(p2.second - p1.second, 2); // y
    return sqrt( a + b );
}

vector<pair<int, int>> knn(pair<int, int> point, int k_v, vector<pair<int, int>> data) {
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> minPQ;
    vector<pair<int, int>> result;
    int k = (k_v > data.size()) ? data.size() : k_v;

    for(int i=0; i<data.size(); i++) {
        auto d = ed(point, data.at(i));

        minPQ.push(make_pair(d, i));
    }

    result.clear();
    for (int j=0 ; j<k; j++) {
        int index = minPQ.top().second;
        minPQ.pop();
        result.push_back(data.at(index));
    }

    return result;
}

int main() {
    dataset1(2500);
    dataset2(1000);
    dataset3(2500);

    auto point = make_pair( 123, 600);
    cout << "Data set 1"  << endl;
    res1 = knn(point, 100, data1);

    //for (auto elem: res1) cout << "["<< elem.first << ","<< elem.second << "], ";

    auto point2 = make_pair( 1359, 1445);
    cout << "\n\nData set 2"  << endl;
    res2 = knn(point2, 70, data2);

    //for (auto elem: res2) cout << "["<< elem.first << ","<< elem.second << "], ";

    auto point3 = make_pair( 1200, 400);
    cout << "\n\nData set 2"  << endl;
    res3 = knn(point3, 100, data3);

    //for (auto elem: res3) cout << "["<< elem.first << ","<< elem.second << "], ";
    
    exportDataset(1);
    exportDataset(2);
    exportDataset(3);

    exportKNN(1);
    exportKNN(2);
    exportKNN(3);

    return 0;
}
