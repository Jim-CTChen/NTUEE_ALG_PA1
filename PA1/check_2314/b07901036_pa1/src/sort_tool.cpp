// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int i, j, tmp = 0;
    for (i = 1; i < data.size(); ++i) {
        tmp = data[i];
        for (j = i-1; j >= 0 && tmp < data[j]; --j) {
            data[j+1] = data[j];
        }
        data[j+1] = tmp;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high) {
        int q = Partition(data, low, high);
        // for (auto it : data) {
        //     cout << it << " ";
        // }
        // cout << endl;
        // cout << "q: " << q << endl;
        QuickSortSubVector(data, low, q);
        QuickSortSubVector(data, q+1, high);
    }

}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    // cout << "low: " << low << " high: " << high << endl;
    // cout << "data: ";
    // for (int i = low; i <= high; i++) {
    //     cout << data[i] << " ";
    // }
    // cout << endl;
    int benchmark = (data[low] + data[high] + data[(low + high)/2]) / 3;
    // cout << data[low] << " " << data[high] << " " << data[(low + high)/2] << endl;
    // cout << "b " << benchmark << endl;
    int i = low;
    int j = high;
    while (true) {
        while (data[j] > benchmark && j > low) j--;
        while (data[i] < benchmark && i < high) i++;
        if (j <= i) return j;
        else {
            int tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            j--;
            i++;
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (high > low) {
        int q = (low + high) / 2;
        // cout << "q: " << q << endl;
        MergeSortSubVector(data, low, q);
        MergeSortSubVector(data, q+1, high);
        Merge(data, low, q, q+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    // cout << "input subArray1: ";
    // for (int i = low; i <= middle1; ++i) cout << data[i] << " ";
    // cout << endl;
    // cout << "input subArray2: ";
    // for (int i = middle2; i <= high; ++i) cout << data[i] << " ";
    // cout << endl;
    vector<int> tmp_data;
    int idx1 = low, idx2 = middle2; 
    tmp_data.reserve(high-low+1);
    for (int i = 0; i <= high-low; ++i) {
        if (data[idx1] <= data[idx2]) {
            tmp_data[i] = data[idx1++];
        }
        else if (data[idx2] < data[idx1]) {
            tmp_data[i] = data[idx2++];
        }
        if (idx1 > middle1) {
            for (int j = i+1; j <= high-low; ++j) {
                tmp_data[j] = data[idx2++];
            }
            break;
        }
        else if (idx2 > high) {
            for (int j = i+1; j <= high-low; ++j) {
                tmp_data[j] = data[idx1++];
            }
            break;
        }
    }
    // cout << "output subArray: ";
    for (int i = low; i <= high; ++i) {
        data[i] = tmp_data[i-low];
        // cout << tmp_data[i-low] << " ";
    }
    // cout << endl;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    // for (auto it : data) {
    //     cout << it << " ";
    // }
    // cout << endl;
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

int SortTool::parent(int i) {
    return (i-1)/2;
}

int SortTool::leftChild(int i) {
    return 2*i+1;
}

int SortTool::rightChild(int i) {
    return 2*i+2;
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    // cout << "----------------" << endl;
    int l = leftChild(root);
    int r = rightChild(root);
    int largest = root;
    // cout << "root: " << root << endl;
    // cout << "l: " << l << endl;
    // cout << "r: " << r << endl;
    if (l < heapSize && data[largest] < data[l]) largest = l;
    if (r < heapSize && data[largest] < data[r]) largest = r;
    if (largest != root) {
        int tmp = data[root];
        data[root] = data[largest];
        data[largest] = tmp;
        // cout << "largest " << largest << endl;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = heapSize/2; i >= 0; --i) {
        MaxHeapify(data, i);
    }
}

