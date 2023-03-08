#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

double Det(double** array, int s);
void PrintArr(double** array, int s);

int main(int argc, char *argv[])
{
    const string RAND = "random", NR = "nature row";
    const int N = 10;
    int size, column, waay;
    string way;

    cout << "Enter the size of the array(from 1 to 10): ";
    cin >> size;
    while (size > 10){
        cout << "\aThe value is incorrect!!!\n" << "Enter other value: ";
        cin >> size;
    }
    // объявление массива
    double** arr = new double* [size];
    // связывание элементов 1 массива с элементами 2
    for (int i = 0; i < size; i++) {
        arr[i] = new double[size];
    }
    cout << endl;
    
    // Путь заполнения массива
    cout << "Choose the way to fill the array( 1 - random, 2 - nature row ):" << endl;
    cin >> waay;
    if (waay == 1)
        way = RAND;
    else if (waay == 2)
        way = NR;
    else {
        while ((way != RAND) || (way != NR)) {
            cout << "\aUncorrect way!!!" << endl;
            cout << "Choose 1 - 'random' or 2 - 'nature row':" << endl;
            cin >> waay;
            if (waay == 1)
                way = RAND;
            else if (waay == 2)
                way = NR;
        }
    }
    // Столбец 
    cout << "Enter the decomposition column: " << endl;
    cin >> column;
    while (column > size) {
        cout << "\aInvalid column!!!\nThe column goes beyond the bounds of the matrix\nEnter column( from 1 to " << (size) << " )" << endl;
        cin >> column;
    }

    int r = 0;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (way == RAND){
                srand(rand() % 100);
                arr[i][j] = rand() % 10;
            }
            else if (way == NR) {
                arr[i][j] = ++r;
            }
        }
    }
    //полученный массив
    cout << "Initial array: \n";
    PrintArr(arr, size);

    cout << "Determinant = " << Det(arr, size);






    // Удаление массива
    for (int i = 0; i < size; i++) {
        delete[] arr[i]; 
    }
    delete[] arr;
    return 0;
}

double Det(double** x, int s) {
    switch (s)
    {
    case 1:
        return x[0][0];
        break;
    case2:
        return x[0][0] * x[1][1] - x[1][0] * x[0][1];
        break;
    default:
   
        double** t;
        t = new double* [s - 1];
        for (int i = 0; i < s-1; i++) {
            t[i] = new double[s - 1];
        }
        double det = 0;
        int a, b;
        
        for (int j = 0; j < s; j++)
        {
            a = 0;
            for (int k = 1; k < s; k++)
            {
                b = 0;
                for (int n = 0; n < s; n++)
                    if (n != j) 
                    {
                        t[a][b] = x[k][n];
                        b++;
                    }
                a++;
            }
            det += pow(-1, (double)j + 1 + 1) * x[0][j] * Det(t, s - 1);
        }
        for (int i = 0; i < s-1; i++) {
            delete[] t[i];
        }
        delete[] t;
        return det;
    }
    
}

void PrintArr(double** array, int s) {
    cout << "  ";
    for (int t = 0; t < s; t++) {
        cout << setw(3) << t + 1 << ' ';
    }
    cout << endl << endl;

    for (int i = 0; i < s; i++) {
        cout << i + 1 << "  ";
        for (int j = 0; j < s; j++) {
            cout << setw(3) << array[i][j] << ' ';
            if (j == s - 1)
                cout << endl;
        }
    }
    cout << endl;
}
