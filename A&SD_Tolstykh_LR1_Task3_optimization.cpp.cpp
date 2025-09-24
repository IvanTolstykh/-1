#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
vector<int> generate_random_list(int n, int min_val = 0, int max_val = 10000) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return arr;
}
int naiveDuplicates(const vector<int>& arr) {
    int count = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}
int findDuplicates(const vector<int>& arr) {
    vector<int> seen;
    int count = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (find(seen.begin(), seen.end(), arr[i]) != seen.end()) {
            count++;
        }
        else {
            seen.push_back(arr[i]);
        }
    }
    return count;
}
void visualize(double time1, double time2) {
    int len1 = static_cast<int>(time1 * 1000);
    int len2 = static_cast<int>(time2 * 1000);
    cout << "Наивный метод (" << time1 << " сек): ";
    for (int i = 0; i < len1; i++) cout << "#";
    cout << "\n";
    cout << "Метод с std::find (" << time2 << " сек): ";
    for (int i = 0; i < len2; i++) cout << "#";
    cout << "\n";
}
int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<int> sizes = { 1000, 5000, 10000 };

    for (int n : sizes) {
        cout << "=== Тест для списка размера " << n << " ===\n";
        vector<int> arr = generate_random_list(n);
        auto start = chrono::high_resolution_clock::now();
        int dupNaive = naiveDuplicates(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedNaive = end - start;
        start = chrono::high_resolution_clock::now();
        int dupFind = findDuplicates(arr);
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsedFind = end - start;

        cout << "Наивный метод: найдено " << dupNaive << " дубликатов, время = " << elapsedNaive.count() << " секунд\n";
        cout << "Метод с std::find: найдено " << dupFind << " дубликатов, время = " << elapsedFind.count() << " секунд\n\n";

        cout << "Визуализация времени (пропорциональные полоски):\n";
        visualize(elapsedNaive.count(), elapsedFind.count());
        cout << "--------------------------\n";
    }
    return 0; 
}
