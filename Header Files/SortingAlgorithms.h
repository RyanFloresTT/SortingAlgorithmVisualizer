//
// Created by rcflo on 5/11/2024.
//

#ifndef TESTPROGRAM_SORTINGALGORITHMS_H
#define TESTPROGRAM_SORTINGALGORITHMS_H

#include <SFML/Graphics.hpp>
#include <thread>

class SortingAlgorithms {
public:
    static void bubbleSort(int arr[], int n);
    static void selectionSort(int arr[], int n);
    static void insertionSort(int arr[], int n);
    static void mergeSort(int arr[], int l, int r);
private:
    static void merge(int arr[], int l, int m, int r);
};

#endif //TESTPROGRAM_SORTINGALGORITHMS_H
