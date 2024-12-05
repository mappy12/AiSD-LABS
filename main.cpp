#include <iostream>
#include <vector>

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

vector<int> quickSort(vector<int> arr) {
    
    size_t size = arr.size();


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
    

}