//
// Created by rcflo on 5/11/2024.
//

#include "../Header Files/SortingAlgorithms.h"
#include "../Header Files/Globals.h"
#include <vector>
#include <thread>

// Sorting algorithms
void SortingAlgorithms::bubbleSort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
                if (!sorting)
                    return;
            }
        }
    }
    sorting = false;
}

void SortingAlgorithms::selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
        if (!sorting)
            return;
    }
    sorting = false;
}

void SortingAlgorithms::insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
        if (!sorting)
            return;
    }
    sorting = false;
}

void SortingAlgorithms::merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void SortingAlgorithms::mergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMS));
    if (sorting == false) return;
}
