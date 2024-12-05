#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, vector<int> arr) {
    size_t size = arr.size();
    
    for (size_t i = 0; i < size; ++i) {
        os << arr[i] << " ";
    }

    os << "\n";

    return os;
}

vector<int> bubbleSort(vector<int> arr) {

    size_t size = arr.size();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    return arr;
}

int main() {
    vector<int> arr;

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(135);
    arr.push_back(30);
    arr.push_back(53);
    arr.push_back(91);
    arr.push_back(53);
    arr.push_back(19);
    arr.push_back(77);

    cout << arr;   

    vector<int> bsArr = bubbleSort(arr);

    cout << bsArr;

}