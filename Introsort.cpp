
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<ctime>

using namespace std;

void swapValue(int* a, int* b){//обмен значений указателей
    int* temp = a;
    a = b;
    b = temp;
}
void InsertionSort(int arr[], int* begin, int* end){//сортировка вставками
    int left = begin - arr; //левый индекс подмассива
    int right = end - arr; //правый индекс подмассива
    for (int i = left + 1; i <= right; i++){
        int key = arr[i];
        int j = i - 1;
            while (j >= left && arr[j] > key) { //перемещение элементов массива от 0 до i-1, которые больше чем ключ, на одну позицию вперед.
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        arr[j + 1] = key;
    }
}
int* Quicksort(int arr[], int low, int high){ //быстра€ сотрировка
    int pivot = arr[high];    // пивот
    int i = (low - 1);  // »ндекс меньшего элемента
    for (int j = low; j <= high - 1; j++){// ≈сли текущий элемент меньше или равно pivot
        if (arr[j] <= pivot) {
            i++;// увеличиваем индекс меньшего элемента
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1); //точка разбиени€
}

int* MedianOfThree(int* a, int* b, int* c){//‘-€ нахождени€ "ћедианы трех", находит середину значений между указател€ми a,b,c и возвращает этот указатель
    if (*a < *b && *b < *c)
        return (b);
    if (*a < *c && *c <= *b)
        return (c);
    if (*b <= *a && *a < *c)
        return (a);
    if (*b < *c && *c <= *a)
        return (c);
    if (*c <= *a && *a < *b)
        return (a);
    if (*c <= *b && *b <= *a)
        return (b);
}

void IntrosortUtil(int arr[], int* begin,int* end, int depthLimit){// выполнение сортировки introsort
    int size = end - begin;// ѕодсчитать количество элементов
    if (size < 16){ // ≈сли размер раздела невелик, делаем сортировку вставками
        InsertionSort(arr, begin, end);
        return;
    }
    if (depthLimit == 0){// ≈сли глубина равна нулю, используем heapsort
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1); //используем heapsort из STL
    }
    int* pivot = MedianOfThree(begin, begin + size / 2, end); // »наче используем концепцию медианы трех и находим хорошую точку дл€ разворота
    swapValue(pivot, end);    // ћен€ем значени€, указанные двум€ указател€ми
    int* partitionPoint = Quicksort(arr, begin - arr, end - arr);// ¬ыполн€ем быструю сортировку
    IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1);
}

void Introsort(int arr[], int* begin, int* end){ //инициализаци€ сортировки
    int depthLimit = 2 * log(end - begin);
    IntrosortUtil(arr, begin, end, depthLimit); // ¬ыполнить рекурсивный интросорт
}

void printArray(int arr[], int n){// ¬спомогательна€ функци€ вывода массива на экран
    for (int i = 0; i < n; i++)
        cout << arr[i]<<" ";
}
int main() {
    int n;
    srand(time(NULL));
    cout << "N = ";
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    cout << "\n |INPUT|: ";
    printArray(arr, n);
    Introsort(arr, arr, arr + n - 1);
    cout << "\n |SORTED|: ";
    printArray(arr, n);
    return(0);
}
