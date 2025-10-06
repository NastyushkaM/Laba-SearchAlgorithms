#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <climits>

using namespace std;

/*******************************************************************
 *           Г Л О Б А Л Ь Н Ы Е   К О Н С Т А Н Т Ы               *
 *******************************************************************/

const char* int_array_filename[2] = { "array1", "array2" }; // массив имен файлов, в которые будут записаны массивы

/*********************************************************************
 *              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                   *
 *********************************************************************/

 //запись элементов последовательностей в файлы
void Output(int* array, int size, int index);
// последовательный поиск (Better_Linear_Search)
int Better_Linear_Search(int* array1, int size, int x);
// быстрый последовательный поиск (Sentinel_ Linear_Search)
int Sentinel_Linear_Search(int* array1, int size, int x);
// последовательный поиск в упорядоченном массиве (Ordered_Array_Search)
int Ordered_Array_Search(int* array2, int size, int x);
// бинарный поиск ( Binary Search)
int Binary_Search(int* array2, int size, int x);

int main(void)
{
    setlocale(LC_ALL, "Russian");  //подключение русского языка

    string FuncName[6] = { "Better_Linear_Search", "Sentinel_Linear_Search",
        "Ordered_Array_Search", "Binary_Search" }; //массив названий функций

    int size; // размерность массивов
    cout << "Введите размерность для массивов: ";
    cin >> size;

    //первый массив - случайная последовательность (для "Better_Linear_Search", "Sentinel_Linear_Search")
    int* array1 = new int[size];
    for (int i = 0; i < size; i++)
    {
        if (i == size / 2)
        {
            array1[i] = -1;
        }
        else if (i == size - 1)
        {
            array1[i] = -2;
        }
        else
        {
            array1[i] = 2 + rand() % 200000;
        }
    }//for

    Output(array1, size, 0); // запись массива 1 в файл

    // второй массив - возрастающая последовательность (для "Ordered_Array_Search", "Binary_Search")
    int* array2 = new int[size];

    for (int i = 0; i < size; i++)
    {
        array2[i] = 2 + ((200002 - 2) / size) * i; // создание последовательности (минимальное значение - 2, максимальное - 200000)
    }

    Output(array2, size, 1); // запись массива 2 в файл

    int (*int_func[])(int*, int, int) = { Better_Linear_Search,
        Sentinel_Linear_Search, Ordered_Array_Search,
        Binary_Search }; // массив указателей на функции

    string IndexName[6] = { "начале", "середине", "конце" }; //массив местонахождения индексов
    int indexes_of_x[3] = { 0, size / 2, size - 1 }; // массив с индексами для ключа поиска - x

    cout << endl;
    cout << "                    Поиск элемента" << endl;
    cout << endl;

    cout << "**********************BLS и SLS**********************" << endl;
    for (int i = 0; i < 2; i++) // для "Better_Linear_Search", "Sentinel_Linear_Search",
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "В " << IndexName[j] << " массива" << endl;
            //cout << "X = " << array1[indexes_of_x[j]] << endl;
            auto begin = chrono::steady_clock::now(); // фиксирование начального времени работы алгоритма
            int result = int_func[i](array1, size, array1[indexes_of_x[j]]); // обращение к i-й функции из массива указателей
            auto end = chrono::steady_clock::now();  // фиксирование конечного времени 
            auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin); // получение времени работы в микросекундах
            cout << "Время работы алгоритма " << FuncName[i] << ": " << elapsed_ms.count() << " (мкС)" << endl; //вывод времени работы 
            cout << endl;
        }//for 
    }//for 
    delete[] array1; // очистка памяти 

    cout << "**********************OAS и BS**********************" << endl;
    for (int i = 2; i < 4; i++) // для "Ordered_Array_Search", "Binary_Search"
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "В " << IndexName[j] << " массива" << endl;
            //cout << "X = " << array2[indexes_of_x[j]] << endl;
            auto begin = chrono::steady_clock::now(); // фиксирование начального времени работы алгоритма
            int result = int_func[i](array2, size, array2[indexes_of_x[j]]); // обращение к i-й функции из массива указателей
            auto end = chrono::steady_clock::now();  // фиксирование конечного времени 
            auto elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin); // получение времени работы в микросекундах
            cout << "Время работы алгоритма " << FuncName[i] << ": " << elapsed_ms.count() << " (мкС)" << endl; //вывод времени работы 
            cout << endl;
        }//for 
    }//for 
    delete[] array2; // очистка памяти

    return 0;
}//main


void Output(int* array, int size, int index) // запись элементов последовательностей в файлы
{
    ofstream File; // инициализация файловой переменной для записи
    File.open(int_array_filename[index]); // открытие файла по имени из массива имён

    // запись элементов последовательности в файлы
    for (int j = 0; j < size; j++)
    {
        File << array[j] << endl;
    }//for j

    File.close(); // закрытие файла
}//Output

int Better_Linear_Search(int* array1, int size, int x)
{
    int comparisons1 = 0; // счетчик сравнений ключа с элементом массива
    int comp_i = 0; // счетчик сравнений в цикле 
    for (int i = 0; i < size; i++)
    {
        comparisons1++;
        comp_i++; // сравнения в цикле
        if (array1[i] == x)
        {
            comparisons1++;
            cout << "Индекс искомого элемента = " << i << endl;
            cout << "Кол-во сравнений в цикле в Better_Linear_Search: " << comp_i << endl;
            cout << "Кол-во сравнений ключа с элементом массива в Better_Linear_Search: " << comparisons1 << endl;
            return i;  // элемент найден, возвращение его индекса
        }//if
    }//for
    cout << "Кол-во сравнений в цикле в Better_Linear_Search: " << comp_i << endl;
    cout << "Кол-во сравнений ключа с элементом массива в Better_Linear_Search: " << comparisons1 << endl;
    return -1; // элемент не найден
}//Better_Linear_Search

int Sentinel_Linear_Search(int* array1, int size, int x)
{
    int comparisons2 = 0; // счетчик сравнений ключа с элементом массива
    int last = array1[size]; // сохранение последнего э-та в last
    array1[size] = x; // помещение x 

    for (int i = 0; i < size; i++)
    {
        comparisons2++;
        if (array1[i] == x)
        {
            array1[size] = last;
            cout << "Индекс искомого элемента = " << i << endl;
            cout << "Кол-во сравнений ключа с элементом массива в Sentinel_Linear_Search: " << comparisons2 << endl;
            return i;  // элемент найден, возвращение его индекса
        }//if
    }//for
    cout << "Кол-во сравнений ключа с элементом массива в Sentinel_Linear_Search: " << comparisons2 << endl;
    return -1; // элемент не найден
}//Sentinel_Linear_Search

int Ordered_Array_Search(int* array2, int size, int x)
{
    int last = array2[size]; // сохранение последнего э-та в last
    array2[size] = LONG_MAX; // заведомо большое значение

    int i = 0;
    while (x > array2[i]) {
        i++;
    }
    array2[size] = last; // восстановление последнего элемента

    if (x == array2[i]) {
        cout << "Индекс искомого элемента = " << i << endl;
        return i;  // элемент найден, возвращение его индекса
    }

    if (x == array2[size]) {
        cout << "Индекс искомого элемента = " << size << endl;
        return size; // возвращение размерности массива
    }

    return -1; // элемент не найден
}//Ordered_Array_Search

int Binary_Search(int* array2, int size, int x)
{
    int p = 0;
    int r = size - 1;

    while (p <= r) {
        int q = (p + r) / 2; // середина интервала

        if (array2[q] == x) {
            cout << "Индекс искомого элемента = " << q << endl;
            return q;  // элемент найден, возвращение его индекса
        }
        else if (array2[q] > x) {
            r = q - 1; // сужение интервала справа
        }
        else {
            p = q + 1; // сужение интервала слева
        }
    }//while

    return -1; // элемент не найден
}//Binary_Search