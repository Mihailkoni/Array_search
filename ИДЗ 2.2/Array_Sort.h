#pragma once
#include <iostream>
#include <vector> // для массива
#include <string> // для работы со строками
using namespace std;


struct key {
    int s; // для номера строки
    struct group { //Номер группы
        char l; // буква номера группы
        int num; // число номера группы
    }group;

    struct fio { //ФИО
        string fio;
    }fio;

    struct Direction {
        string title; // название направления
    }dir;

    struct Application { // номер заявки
        int number_app;
    }app;
};

void bubbleSort(vector<key>& arr, long& n) {
    bool swapped;
    key temp;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].app.number_app > arr[j + 1].app.number_app) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                //swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
            break; // Если не было обмена, то массив уже отсортирован
        }
    }
}

int increment(long inc[], long& size) {
    int p1, p2, p3, s;

    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

void shellSort(vector<key>& arr, long& size) {
    long inc, i, j, seq[40];
    int s;
    key temp;
    // вычисление последовательности приращений
    s = increment(seq, size);
    while (s >= 0) {
        // сортировка вставками с инкрементами inc[] 
        inc = seq[s--];

        for (i = inc; i < size; i++) {
            temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j].app.number_app > temp.app.number_app); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
}