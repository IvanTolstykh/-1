#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>   
#include <ctime>     
#include <chrono>    

using namespace std;
void rotateRight(vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;

    reverse(arr.begin(), arr.end());
    reverse(arr.begin(), arr.begin() + k);
    reverse(arr.begin() + k, arr.end());
}

// Генерация случайного массива целых чисел размером n
vector<int> generate_random_list(int n, int min_val = 0, int max_val = 100) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}

int main() {
    setlocale(LC_ALL, "Russian"); 
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<int> sizes = { 10, 1000, 100000 }; 

    for (int n : sizes) {
        vector<int> arr = generate_random_list(n, 0, 1000);
        int k = n / 3; 

        
        if (n <= 20) {
            cout << "Размер списка: " << n << "\n";
            cout << "Массив до ротации: ";
            for (int x : arr) cout << x << " ";
            cout << "\n";
        }

        auto start = chrono::high_resolution_clock::now();
        rotateRight(arr, k);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = end - start;

        if (n <= 20) {
            cout << "Массив после ротации на " << k << " позиций: ";
            for (int x : arr) cout << x << " ";
            cout << "\n";
        }

        cout << "Сдвиг: " << k << "\n";
        cout << "Время ротации: " << elapsed.count() << " секунд\n";
        cout << "Сложность алгоритма: O(n)\n";
        cout << "--------------------------\n";
    }

    return 0;
}