#include <iostream>
#include <vector>
#include <cstdlib>   
#include <ctime>     
#include <chrono>    

using namespace std;
pair<int, int> twoMaxTwoPass(const vector<int>& arr) {
    int n = arr.size();
    int max1 = arr[0];
    int idx1 = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] > max1) {
            max1 = arr[i];
            idx1 = i;
        }
    }
    int max2 = INT_MIN;
    int idx2 = -1;
    for (int i = 0; i < n; ++i) {
        if (i != idx1 && arr[i] > max2) {
            max2 = arr[i];
            idx2 = i;
        }
    }

    return { max1, max2 };
}
pair<int, int> twoMaxOnePass(const vector<int>& arr) {
    int max1 = INT_MIN, max2 = INT_MIN;
    for (int x : arr) {
        if (x > max1) {
            max2 = max1;
            max1 = x;
        }
        else if (x > max2) {
            max2 = x;
        }
    }
    return { max1, max2 };
}
vector<int> generate_random_list(int n, int min_val = 0, int max_val = 20000) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<int> sizes = { 1000, 10000, 100000 };

    for (int n : sizes) {
        vector<int> arr = generate_random_list(n);
        auto start = chrono::high_resolution_clock::now();
        pair<int, int> maxTwoPass = twoMaxTwoPass(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedTwoPass = end - start;
        start = chrono::high_resolution_clock::now();
        pair<int, int> maxOnePass = twoMaxOnePass(arr);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedOnePass = end - start;
        cout << "Размер списка: " << n << "\n";
        cout << "Два прохода: максимумы = " << maxTwoPass.first << ", " << maxTwoPass.second
            << ", время = " << elapsedTwoPass.count() << " секунд\n";
        cout << "Один проход: максимумы = " << maxOnePass.first << ", " << maxOnePass.second
            << ", время = " << elapsedOnePass.count() << " секунд\n";
        cout << "--------------------------\n";
    }
    return 0;
}