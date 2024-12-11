#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct stats {
    size_t comparisonCount = 0;
    size_t copyCount = 0;
};

ostream& operator<<(ostream& os, vector<int> arr) {

    size_t size = arr.size();
    
    for (size_t i = 0; i < size; ++i) {
        os << arr[i] << " ";
    }

    os << "\n";

    return os;
}

stats bubbleSort(vector<int>& arr) {

    stats s;

    size_t size = arr.size();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {

            ++s.comparisonCount;

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                
                s.copyCount += 3;
            }
        }
    }

    return s;
}

stats shakeSort(vector<int>& arr) {

    stats s;
    size_t size = arr.size();

    int start = 0;
    int end = size - 1;
    
    while (start <= end) {
        for (size_t i = start; i <= end - 1; ++i) {
            ++s.comparisonCount;

            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);

                s.copyCount += 3;
            }
        }

        ++start;

        for (size_t i = end; i >= start; --i) {
            ++s.comparisonCount;

            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);

                s.copyCount +=3;
            }
        }

        --end;
    }

    return s;

}

stats quickSort(vector<int>& arr, size_t left, size_t right) {
    
    size_t size = arr.size();
    stats s;

    size_t i = left;
    size_t j = right;

    int middle = (left + right) / 2;

    if (size == 2) {
        if (arr[0] > arr[1]) {
            ++s.comparisonCount;
            swap(arr[0], arr[1]);
            s.copyCount += 3;
        }
    }

    if (size >= 3) {
        while (i <= j) {
            while(arr[i] < arr[middle]) {
                ++s.comparisonCount;
                ++i;
            }

            while (arr[j] > arr[middle]) {
                ++s.comparisonCount;
                --j;
            }

            if (i <= j) {
                swap(arr[i], arr[j]);
                s.copyCount += 3;

                ++i;
                --j;
            }
        }

        if (left < j) quickSort(arr, left , j);
        if (right > i) quickSort(arr, i, right);
    }

    return s;
}


vector<int> createRandomArr(size_t size) {
    vector<int> arr(size);

    srand(time(0));

    for (size_t i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
    }

    return arr;
}

void calcStatsRandom() {
    stats s, total;

    vector<size_t> sizes = { 1000, 2000, 3000 };

    for (size_t size : sizes) {
        cout << "\nSize of array: " << size << endl;
        
        total.comparisonCount = 0;
        total.copyCount = 0;

        for (size_t i = 0; i < 100; ++i) {
            vector<int> arr = createRandomArr(size);

            s = bubbleSort(arr);

            total.comparisonCount += s.comparisonCount;
            total.copyCount += s.copyCount;
        }

        for (size_t i = 0; i < 100; ++i) {
            vector<int> arr = createRandomArr(size);

            s = shakeSort(arr);

            total.comparisonCount += s.comparisonCount;
            total.copyCount += s.copyCount;
        }

        for (size_t i = 0; i < 100; ++i) {
            vector<int> arr = createRandomArr(size);

            s = quickSort(arr, 0, arr.size() - 1);

            total.comparisonCount += s.comparisonCount;
            total.copyCount += s.copyCount;
        }

        cout << "Avg comparison count: " << total.comparisonCount / 100 << endl;
        cout << "Avg copy count: " << total.copyCount / 100 << endl;

    }

}

int main() {

    vector<int> arr1;

    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(135);
    arr1.push_back(30);
    arr1.push_back(53);
    arr1.push_back(91);
    arr1.push_back(53);
    arr1.push_back(19);
    arr1.push_back(77);

    cout << "----------------------------------\n";
    cout << "Array_1: ";
    cout << arr1;
    cout << "----------------------------------\n\n";

    cout << "-----------------Bubble Sort-----------------\n\n";
    stats bsStats = bubbleSort(arr1);
    cout << arr1 << endl;
    cout << "Comparison count: " << bsStats.comparisonCount << endl;
    cout << "Copy count: " << bsStats.copyCount << endl << endl;

    vector<int> arr2;
    arr2.push_back(43);
    arr2.push_back(63);
    arr2.push_back(1);
    arr2.push_back(4);
    arr2.push_back(7);
    arr2.push_back(10);
    arr2.push_back(28);
    arr2.push_back(100);
    arr2.push_back(99);

    cout << "----------------------------------\n";
    cout << "Array_2: ";
    cout << arr2;
    cout << "----------------------------------\n\n";

    cout << "-----------------Shake Sort-----------------\n\n";
    stats ssStats = shakeSort(arr2);
    cout << arr2 << endl;
    cout << "Comparsion count: " << ssStats.comparisonCount << endl;
    cout << "Copy count: " << ssStats.copyCount << endl << endl;

    vector<int> arr3;
    arr3.push_back(20);
    arr3.push_back(91);
    arr3.push_back(111);
    arr3.push_back(2);
    arr3.push_back(9);
    arr3.push_back(231);
    arr3.push_back(9);
    arr3.push_back(73);
    arr3.push_back(97);

    cout << "----------------------------------\n";
    cout << "Array_3: ";
    cout << arr3;
    cout << "----------------------------------\n\n";

    cout << "-----------------Quick Sort-----------------\n\n";
    stats qsStats = quickSort(arr3, 0, arr3.size() - 1);
    cout << arr3 << endl;
    cout << "Comparsion count: " << qsStats.comparisonCount << endl;
    cout << "Copy count: " << qsStats.copyCount << endl << endl;

    cout << "---------------------------------------------------------------------------\n";
    cout << "Second Task:" << endl << endl;

    calcStatsRandom();

}