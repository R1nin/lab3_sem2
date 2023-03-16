#include <iostream>
#include <string>
#include <random>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

void PrintArr(double** array, int s);
double Det(double** array, int s, int col = 0);
void Minor(double** x, double** t, int s, int col, int row);
double Gauss(double** x, int s);

int main( int argc, char *argv[] )
{
    const string RAND = "random", NR = "nature row" , Enter = "enter";
    const int N = 10;
    int size, column, waay, time;
    string way;
    bool method = 0;

    double pA2[2][2] = { 
        { 1, 3 }, 
        { 7, 9 } };
    double** p2 = new double* [2];
    for (int i = 0; i < 2; i++)
    {
        p2[i] = new double[2];
        for (int j = 0; j < 2; j++)
        {
            p2[i][j] = pA2[i][j];
        }
    }
    double pB3[3][3] = { 
        { 1, -2, 3 },
        { 0, 7, 4 },
        { 5, 3, -3 } }; // -178
    int q = 3;
    double** p3 = new double* [q];
    for (int i = 0; i < q; i++)
    {
        p3[i] = new double[q];
        for (int j = 0; j < q; j++)
        {
            (p3[i][j]) = pB3[i][j];
        }
    }
     
    cout << "Show example (1 or 0): ";
    cin >> waay;
    cout << endl;
    
    if (waay == 1) {
        int length = 2;
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                cout << setw(2) << p2[i][j] << ' ';
            }
            cout << endl;
        }
           cout << "Determinant (2*2) = " << Det(p2, 2) << endl;
        for (int i = 0; i < q; i++)
        {
            for (int j = 0; j < q; j++)
            {
                cout << setw(2) << p3[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "Determinant (3*3) = " << Det(p3, q) << endl;
        cout << "Determinant(Gauss) = " << Gauss(p3, q) << endl;
    }

    cout << "\nEnter the size of the array(from 1 to 10): ";
    cin >> size;
    while (size == 0 || size > 10){
        cout << "\aThe value is incorrect!!!\n" << "Enter other value: ";
        cin >> size;
    }
    /// объявление массива
    double** arr = new double* [size];
    /// связывание элементов 1 массива с элементами 2
    for (int i = 0; i < size; i++) {
        arr[i] = new double[size];
    }
    cout << endl;

    double** new_arr = new double* [size-1];
    /// связывание элементов 1 массива с элементами 2
    for (int i = 0; i < size-1; i++) {
        new_arr[i] = new double[size-1];
    }
    
    /// Путь заполнения массива
    cout << "Choose the way to fill the array( 1 - random, 2 - nature row, 3 - enter ):" << endl;
    cin >> waay;
    if (waay == 1)
        way = RAND;
    else if (waay == 2)
        way = NR;
    else if (waay == 3)
        way = Enter;
    else {
        while ((way != RAND) || (way != NR)) {
            cout << "\aUncorrect way!!!" << endl;
            cout << "Choose 1 - 'random' or 2 - 'nature row' or 3 - 'manual input':" << endl;
            cin >> waay;
            if (waay == 1)
                way = RAND;
            else if (waay == 2)
                way = NR;
            else if (waay == 3)
                way = Enter;
        }
    }

    /// Заполнение массива
    int r = 0;
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            if (way == RAND) {
                double p = rand() % 10;
                arr[i][j] = p;
            }
            else if (way == NR) {
                arr[i][j] = ++r;
            }
            else if (way == Enter) {
                cout << "Element [" << i << "]" << "[" << j << "] = ";
                cin >> arr[i][j];
            }
        }
    }

    /// Столбец 
    cout << "Enter the decomposition column: " << endl;
    cin >> column;
    while (column > size) {
        cout << "\aInvalid column!!!\nThe column goes beyond the bounds of the matrix\nEnter column( from 1 to " << (size) << " )" << endl;
        cin >> column;
    }
    
    /// Вывод полученного массива
    cout << "Initial array: \n";
    PrintArr(arr, size);
    
    time = clock();
    cout << time << endl;
    cout << "Determinant (recurs) = " << Det(arr, size, column) << endl;
    time = clock();
    cout << time << endl;
    
    cout << "Determinant (Gauss) = " << Gauss(arr, size) << endl;
    time = clock();
    cout << time << endl;
    PrintArr(arr, size);

    /// Удаление массива
    for (int i = 0; i < size; i++) {
        delete[] arr[i]; 
    }
    delete[] arr;
    return 0;
}

double Det(double** x, int s, int col) {
    
    switch (s) {
    case 1:
        return x[0][0];
        break;
    case 2:
        return x[0][0] * x[1][1] - x[1][0] * x[0][1];
        break;
    default:
        int k = 1;
        double** t;
        t = new double* [s - 1];
        for (int i = 0; i < s-1; i++) {
            t[i] = new double[s - 1];
        }
        double det = 0;
        int a, b;
        for (int i = 0; i < s; i++) {
            Minor(x, t, s, col, i);
            det += pow(-1, i+col) * x[i][col] * Det(t, s - 1);
        }
        for (int i = 0; i < s-1; i++) {
            delete[] t[i];
        }
        delete[] t;
        return det;
    }

}

void Minor(double** x, double** t, int s, int col, int row) {

    int sm_col = 0, sm_row = 0;
    for (int i = 0; i < s-1; i++)
    {
        if (row == i)
            sm_row = 1;
        for (int j = 0; j < s-1; j++)
        {
            if (col == j)
                sm_col = 1;
            t[i][j] = x[sm_row + i][sm_col + j];
            
        }
        sm_col = 0;
    }
}

double Gauss(double** x, int s) {
    double factor = 0, det = 1;
    for (int i = 0; i < s-1; i++) {
        for (int j = 1; j < s-i; j++) {
            factor = x[i+j][i] / x[i][i];
            for (int k = 0; k < s; k++) {
                x[i + j][k] -= x[i][k] * factor;
            }
        }
    }
    for (int i = 0; i < s; i++) {
        det *= x[i][i];
    }
    return det;
}

void PrintArr(double** array, int s) {
    cout << "   ";
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
