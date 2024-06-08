#include <iostream>
#include <vector> // ��� �������
#include <fstream> // ��� ������ � ������ �����
#include <string> // ��� ������ �� ��������
#include "Array_Search2.h" // ������
using namespace std;

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
    key answer; // ���� ��� ������
    int steps = 0; // ���������� ����� ���������
    read_file(Array_SLS, "Input.txt",n); // ������ �����
    bool flag =  Sentinel_Linear_Search(Array_SLS, answer, number, steps,n); // ����� �������
    if (flag) {
        write_file(answer, steps, "Output_Sentinel_Linear_Search.txt"); // ������ � ����
    }
    else {
        cout << "Key is not found" << "\n";
    }
}

void Call_Homogeneous_Binary_Search(int number,long n) {
    vector<key> Array_HBS;
    key answer; // ���� ��� ������
    int steps = 0; // ���������� �����
    read_file(Array_HBS, "Input.txt",n); // ������ �����
    shellSort(Array_HBS, n); // ���������� ������� "������"
    //bubbleSort(Array_HBS, n);
    bool flag = Homogeneous_Binary_Search(Array_HBS,answer,number,steps,n); // ����� �������
    if (flag) {
        write_file(answer, steps, "Output_Homogeneous_Binary_Search.txt"); // ������ � ����
    }
    else {
        cout << "Key is not found" << "\n";
    }
    
}

int main(){
    int number = 817; //����� ��� ������
    int n = 10000; // ������� ����� ������
    Call_Sentinel_Linear_Search(number,n);
    Call_Homogeneous_Binary_Search(number,n);
    return 0;
}