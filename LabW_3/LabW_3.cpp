#include <iostream>
bool checkInput(double **a, int height) // проверка на соблюдение условия a[i][j] = a[j][i]
{
    bool isSuitable = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (a[i][j] - a[j][i] < -0.0001 || a[i][j] - a[j][i] > 0.0001)
            {
                isSuitable = 0;
            }
        }
    }
    return isSuitable;
}
bool input(double **a, int height) //ввод значений в матрицу height x height. Возвращает 0 <=> введённые с консоли значения не подпадаю под условие a[i][j] = a[j][i]
{
    bool isAuto, isCorrect;
    isCorrect = 1;
    std::cout << std::endl
              << "0 to manually fill array, 1 to fill it with random numbers: ";
    std::cin >> isAuto;
    if (isAuto) // Генерация случайных чисел (в описанных пределах. До 3 знаков после запятой включительно)
    {
        srand(static_cast<unsigned int>(time(0)));
        double min, max;
        std::cout << std::endl
                  << "Minimum and maximum possible numbers: ";
        std::cin >> min >> max;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < height; j++)
            {
                a[i][j] = (rand() % (int)(max * 1000 - min * 1000) + (int)min * 1000) / 1000.0;
                if (i > j)
                {
                    a[i][j] = a[j][i];
                }
                std::cout << a[i][j] << "\t";
            }

            std::cout << std::endl;
        }
    }
    else
    {
        for (int i = height - 1; i > 0; i++)
        { // ручной ввод с консоли
            for (int j = 0; j <= i; j++)
            {
                std::cin >> a[i][j];
                a[j][i] = a[i][j];
                std::cout << "/t";
            }
            std::cout << std::endl;
        }
    }
    if (!checkInput(a, height))
    {
        std::cout << "ERROR";
        isCorrect = 0;
    }
    return isCorrect;
}
void replace(double **a, int x1, int y1, int x2, int y2) //перемена местами двух значений в матрице с соблюдением условия a[i][j] = a[j][i]
{
    double buffer = a[x1][y1];
    a[x1][y1] = a[x2][y2];
    a[x2][y2] = buffer;
}
void sort(double **a, int height) //сортировка матрицы таким образом: наибольший значения матрицы находятся на главной диагонали, с верхнего левого угла к правому нижнему они расположены по убыванию
{
    std::cout << std::endl;
    for (int i = 0; i < height; i++) // номер на главной диагонали
    {
        for (int j = 0; j < height; j++) // столбец
        {
            for (int k = 0; k < height; k++) // строка
            {
                if (a[i][i] < a[j][k] && ((j != k) || (j > i)))
                {
                    replace(a, i, i, j, k);
                }
            }
        }
    }
}
void cout(double **a, int height) // вывод матрицы на консоль
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            std::cout << a[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
int search(double **a, int height) // поиск первой строки с только отрицательными числами в ней
{
    bool isNegative = 0;
    bool isConstantlyNegative = 1;
    int res = -1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (a[i][j] < 0)
            {
                isNegative = 1;
            }
            else if (isNegative == 1)
            {
                isNegative = 0;
                isConstantlyNegative = 0;
                break;
            }
        }
        if (isNegative && isConstantlyNegative)
        {
            res = i + 1;
            break;
        }
        isConstantlyNegative = 1;
    }
    return res;
}
int main()
{
    int height;
    std::cout << "Height of array: ";
    std::cin >> height;
    std::cout << std::endl;
    double **numbers = new double *[height];
    for (int i = 0; i < height; i++)
    {
        numbers[i] = new double[height];
    }
    if (input(numbers, height))
    {
        if (search(numbers, height) != -1)
        {
            std::cout << search(numbers, height) << " is the first line with only negative numbers. " << std::endl;
        }
        else
        {
            std::cout << "There is no line with only negative numbers";
        }
        sort(numbers, height);
        cout(numbers, height);
    }
}
