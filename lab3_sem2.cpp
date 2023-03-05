// lab3_sem2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

float Det(float **array, int s);
void PrintArr(float** array, int s);

int main(int argc, char *argv[])
{
    const string RAND = "random", NR = "nature row";
    const int N = 10;
    //float arr[N][N]{};
    int size, column, waay;
    string way;

    cout << "Enter the size of the array(from 2 to 10): ";
    cin >> size;
    while (size >= 10){
        cout << "The value uncorrectable!!!\n" << "Enter other value: ";
        cin >> size;
    }
    // объявление массива
    float** arr = new float* [size];
    // связывание элементов 1 массива с элементами 2
    for (int i = 0; i < size; i++) {
        arr[i] = new float[size];
    }
    cout << endl;

    cout << "Enter the decomposition column: " << endl;
    cin >> column;
    while (column > size) {
        cout << "Uncorrect column!!!\nThe column goes beyond the bounds of the matrix\nEnter column( from 1 to "<< (size) <<" )" << endl;
        cin >> column;
    }
    cin.clear();
    
    cout << "Choose the way to fill the array( 1 - random, 2 - nature row ):" << endl;
    cin >> waay;
    if (waay == 1)
        way = RAND;
    else if (waay == 2)
        way = NR;
    else if ((waay != 1) || (waay != 2)) {

        while ((waay != 1) || (waay != 2)) {
            cout << "Uncorrect way!!!" << endl;
            cout << "Choose 1 - 'random' or 2 - 'nature row':" << endl;
            cin >> waay;

            if (waay == 1)
                way = RAND;
            else if (waay == 2)
                way = NR;
        }
    }

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (way == RAND)
                arr[i][j] = rand() % -99;
            else if (way == NR) {
                int r = 0;
                arr[i][j] = ++r;
            }
        }
    }
    //полученный массив
    cout << "Initial array: \n";
    PrintArr(arr, size);
    float tmp;


    // Удаление массива
    for (int i = 0; i < size; i++) {
        delete[] arr[i]; 
    }
    delete[] arr;
    return 0;
}

float Det(float **a, int s) {
    float d = 0, tmp;
    
    if (s == 1)
        return a[0][0];
    else if (s == 2)
        return a[0][0] * a[1][1] - a[1][0] * a[0][1];
    else {
            
    }
    
    return d;
}

void PrintArr(float** array, int s) {

    cout << "  ";
    for (int t = 0; t < s; t++) {
        cout << setw(3) << t + 1 << ' ';
    }
    cout << endl;

    for (int i = 0; i < s; i++) {
        cout << i + 1 << ' ';
        for (int j = 0; j < s; j++) {
            cout << setw(3) << array[i][j] << ' ';
            if (j == s - 1)
                cout << endl;
        }
    }
    cout << endl;
}
