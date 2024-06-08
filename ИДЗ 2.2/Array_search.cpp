#include <iostream>
#include <vector> // для массива
#include <chrono> // для времени
#include <fstream> // для чтения и записи файла
#include <string> // для работы со строками
#include "Array_Sort.h" // для сортировки массива
using namespace std;
using namespace chrono;

///<summary>
/// Линейный поиск с барьером
///</summary>

bool Sentinel_Linear_Search(vector<key>arr,key &answer,int search_key, int& steps,int n) {
    if (arr.empty()) {
        return false;
    }
    int temp = arr[n-1].app.number_app;
    arr[n-1].app.number_app = search_key;

    int i = 0;
    if (arr[i].app.number_app == search_key) {
        steps++;
        answer = arr[i];
        return true;
    }
    while (arr[i].app.number_app != search_key) {
        i++;
        steps++;
    }

    arr[n-1].app.number_app = temp;
    if ((i < n-1) || (arr[i].app.number_app == search_key)) {
        steps++;
        answer = arr[i];
        return true;
    }
    else {
        return false;
    }
}

///<summary>
/// Однородный бинарный поиск
///</summary>

int for_pow(int num, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) {
        res *= num;
    }
    return res;
}

void steps_table(vector<int>& arr, int n) {
    int j = 1;
    while (((n + for_pow(2, j - 1)) / for_pow(2, j)) > 0) {
        arr.push_back((n + for_pow(2, j - 1)) / (for_pow(2, j)));
        j++;
    }
}

bool Homogeneous_Binary_Search(vector<key>& arr, key& answer, int search_key, int& steps,int n) {
    int m = n / 2;
    vector<int> b_step;
    steps_table(b_step, m);
    int j = 0;
    while (!b_step.empty()) {
        steps++;

        if ((m >= 0) && (m < n) && (arr[m].app.number_app == search_key)) {
            answer = arr[m];
            return true;
        }
        else if ((m >= 0) && (m < n) && (arr[m].app.number_app < search_key)) {
            m += b_step[j];
        }
        else {
            m -= b_step[j];
        }
        if (j < b_step.size() - 1) {
            j++;
        }
        else {
            b_step.pop_back();
            j = 0;
        }
    }
    return false;
}
///

void read_file(vector<key>& arr, const string& filename,int n) {
    string line;
    int count = 0;
    int n_count = n;
    int p1, p2, p3, p4, p5 = 0;

    ifstream in(filename);
    if (in.is_open()) {

        while ((getline(in, line)) &&(n_count>0)) {
            count += 1;
            key k;
            k.group.l = line[0];
            k.group.num = stoi(line.substr(1, 4));
            p1 = line.find(' ');
            p2 = line.find(' ', p1 + 1);
            p3 = line.find(' ', p2 + 1);
            p4 = line.find(' ', p3 + 1);
            p5 = line.find_last_of(' ');
            k.fio.fio = line.substr(p1 + 1, p4 - p1 - 1);
            k.dir.title = line.substr(p4 + 1, p5 - p4 - 1);
            k.app.number_app = stoi(line.substr(p5 + 1));
            k.s = count;
            arr.push_back(k);
            n_count--;
        }
    }
    else {
        cerr << "error";
        return;
    }

    in.close();
}

void write_file(key& arr,int steps, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << arr.group.l << arr.group.num << " " << arr.fio.fio << " " << arr.dir.title<< " " << arr.app.number_app << " " << arr.s << " " << steps << "\n";
    }
    else {
        cerr << "error";
        return;
    }
    file.close();
};

void Call_Sentinel_Linear_Search(int number,int n) {
    vector<key> Array_SLS;
    key answer; // ключ для ответа
    int steps = 0; // количество шагов алгоритма
    read_file(Array_SLS, "Input.txt",n); // чтение файла
    bool flag =  Sentinel_Linear_Search(Array_SLS, answer, number, steps,n); // вызов функции
    if (flag) {
        write_file(answer, steps, "Output_Sentinel_Linear_Search.txt"); // запись в файл
    }
    else {
        cout << "Key is not found" << "\n";
    }
}

void Call_Homogeneous_Binary_Search(int number,long n) {
    vector<key> Array_HBS;
    key answer; // ключ для ответа
    int steps = 0; // количество шагов
    read_file(Array_HBS, "Input.txt",n); // чтение файла
    shellSort(Array_HBS, n); // сортировка массива "Шеллом"
    //bubbleSort(Array_HBS, n);
    bool flag = Homogeneous_Binary_Search(Array_HBS,answer,number,steps,n); // вызов функции
    if (flag) {
        write_file(answer, steps, "Output_Homogeneous_Binary_Search.txt"); // запись в файл
    }
    else {
        cout << "Key is not found" << "\n";
    }
    
}

int main(){
    int number = 817; //число для поиска
    int n = 10000; // сколько строк читать
    Call_Sentinel_Linear_Search(number,n);
    Call_Homogeneous_Binary_Search(number,n);
    return 0;
}