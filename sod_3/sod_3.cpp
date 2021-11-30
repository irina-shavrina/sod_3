#include <iostream>
#include <fstream>
#include <windows.h>
#include <locale.h>
#include <regex>
#include <map>
#include <cstring>
#include <cctype>
#include <string>
using namespace std;
int calculateSize(std::ifstream&);
void controller();
void firstEx();
void secondEx();
void additionSecondEx();
void additionThirdEx();
void additionThirdEx2();
void additionThirdEx3();
void fourEx();
void additionFourEx();
void ExFive();
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    controller();
    return 0;
}



void controller() {
    int choice;
    std::cout << "Enter the exercice\n";
    std::cin >> choice;
    std::cin.ignore();
    switch (choice) {
    case 1: {
        //Друк питальних речень (задача 1.1);
        firstEx();
        break;
    }
    case 2: {
        //задача 1.2
        secondEx();
        break;
    }
    case 3: {
        //1.2(додатково дамп файлу)
        additionSecondEx();
        break;
    }
    case 4: {
        //1.3. (динамічний одновимірний масив)
        additionThirdEx();
        break;
    }
    case 5: {
        //1.3. (двовимірний масив)
        additionThirdEx2();
        break;
    }
    case 6: {
        //завдання  1.4.
        additionThirdEx3();
        break;
    }
    case 7: {
        //задачу 1.5. (порівняння файлів);
        fourEx();
        break;
    }
    case 8: {
        //завдання 1.6;
        additionFourEx();
        break;
    } 
    case 9: {
        //завдання за варіантами
        ExFive();
        break;
    }
    default:
        break;
    }
}
int calculateSize(std::ifstream& someFile) {
    someFile.seekg(0, std::ios::end);
    int size = someFile.tellg();
    someFile.seekg(0, std::ios::beg);
    return size;
}

void firstEx() {
    ifstream fin("Shakespeare_WintersTale.txt", ios::binary); //Визначаю об'єкт fin класу вхідних потоків ifstream, та вказую повний шляд до файлу Shakespeare_WintersTale.txt
    ofstream fout("text.txt", ios::binary | ios::app);//Визначаю об'єкт fout класу вхідних потоків ofstream, та вказую повний шляд до файлу Питальні речення.txt
    if (!fin.is_open()) { //Перевіряю успішність створення об'єкта fin
        cout << "Помилка відкриття файлу!" << endl; 
        return; 
    }
    if (!fout.is_open()) { //Перевіряю успішність створення об'єкта fout
        cout << "Помилка відкриття файлу!" << endl; 
        return; 
    }
    fin.seekg(0, ios::end);//Перехожу в кінець файлу для визначення довжини
    long len = fin.tellg();// Отримую значення, запам'ятавши його в змінній len
    cout << "Розмір файлу: " << len << endl; 
    char* buf = new char[len + 1];// Виділяю len+1 байтів під символьний рядок buf, в якій буде зберігатися текст з файлу
    fin.seekg(0, ios::beg);//Переміщаю поточну позицію на початок файлу
    fin.read(buf, len);//Виконую власне читання, за допомогою методу read(buf, len), який зчитує з файлу len символів в символьний масив buf
    buf[len] = '\0';
    long n = 0, i = 0;//n-буде зберігати позиції початку поточної змінної, i-використовується для перегляду масиву
    while (buf[i]) { //Цикл перегляду buf завершується коли зустрівся нуль-символ
        if (buf[i] == '?') {//Якщо зустрівся знак '?'
            for (int j = n; j <= i; j++) {//Починаючи з позиції n і закінчуючи поточною
                if (j == i) fout << buf[j] << endl;//Виконується друк символів в файл
                else fout << buf[j];//Виконується друк символів в файл
            }
            n = i + 1; // В змінну n заноситься позиція початку нового речення
        }
        if (buf[i] == '.' || buf[i] == '!' || buf[i] == '\n') n = i + 1;//Якщо в речені немає '?' переходимо до наступного
        i++;

    }
    fin.close();
}
void secondEx() {
    {
        std::ofstream os("z3.dat", std::ios::binary);
        if (!os.is_open()) {
            std::cout << "Opens error\n";
            return;
        }

        const int intsArrSize = 10;
        const int charsArrSize = 5;
        double doubleNum1 = 36.14;
        double doubleNum2 = 0.3543;

        int intsArr[intsArrSize];
        char charsArr[charsArrSize];

        for (int index = 0; index < intsArrSize; ++index)
            intsArr[index] = index;
        for (int index = 0; index < charsArrSize; ++index)
            charsArr[index] = 70 + index;

        //записа в дамп 16 байт (double - 8 byte)
        os.write((char*)&doubleNum1, sizeof(doubleNum1));
        os.write((char*)&doubleNum2, sizeof(doubleNum2));

        //також можна так os.write((char*)intsArr, intArrSize * sizeof(int));
        //массив - 10 чисел, тому записується 4 * 10 байт
        for (int index = 0; index < intsArrSize; ++index)
            os.write((char*)&intsArr[index], sizeof(intsArr[index]));
        //2 * 5 байт
        for (int index = 0; index < charsArrSize; ++index)
            os.write((char*)&charsArr[index], sizeof(charsArr[index]));

        os.close();

        {
            //открытые файла в бинарном режиме
            std::ifstream ist("z3.dat", std::ios::binary);
            if (!ist.is_open()) {
                std::cout << "Opens error\n";
            }
            //переход в конец и считывание количества символов
            ist.seekg(0, std::ios::end);
            int lenght = ist.tellg();
            ist.close();
            //открытые файла в бинарном режиме и режиме добавления
            std::ofstream os("z3.dat", std::ios::binary | std::ios::app);
            if (!os.is_open()) {
                std::cout << "Opens error\n";
            }
            //запись 
            os.write((char*)&lenght, sizeof(lenght));
            os.close();
        }
    }
}
void additionSecondEx() {
    std::ofstream os("z3.dat", std::ios::binary);
    std::ifstream ist("Shakespeare_WintersTale.txt");
    if (!(os.is_open()) && !(ist.is_open())) {
        std::cout << "Opens error\n";
        return;
    }
    int bufSize;
    char* buf;

    //вычисления размера запись текстового файла в бинарный файл
    ist.seekg(0, std::ios::end);
    bufSize = ist.tellg();
    ist.seekg(0, std::ios::beg);
    buf = new char[bufSize];
    ist.read(buf, bufSize);

    os.write((char*)buf, sizeof(char) * bufSize);

    os.close();
}

void additionThirdEx() {
    int arrSize;
    std::cout << "Enter the size of array\n";
    std::cin >> arrSize;
    int* arr = new int[arrSize];
    for (int index = 0; index < arrSize; ++index) {
        arr[index] = index;
    }
    std::ofstream ofs("z3_3.txt", std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }
    //запис
    ofs.write((char*)arr, sizeof(arr) * arrSize);

    ofs.close();

    int newNum;
    int numIndex;
    std::fstream fst("z3_3.txt", std::ios::binary | std::ios::in | std::ios::out);
    std::cout << "Enter the number and its index\n";
    std::cin >> newNum >> numIndex;


    if (!fst.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }
    fst.seekg(0, std::ios::end);
    int lenght = fst.tellg();
    std::cout << "The file size ist: " << lenght << "bytes\n";
    //куди треба буде записати число
    int possition = numIndex * sizeof(int);

    std::cout << "Position of the edited element: " << possition << '\n';
    //перехід в позицію
    fst.seekp(possition, std::ios::beg);
    //запис в позицію
    fst.write((char*)&newNum, sizeof(int));
    fst.seekp(0);


    fst.read((char*)arr, sizeof(arr) * arrSize);
    for (int index = 0; index < arrSize; ++index)
    {
        std::cout << arr[index] << " ";
    }

}
void additionThirdEx2() {
    int arrSize;
    std::cout << "Enter the size of array\n";
    std::cin >> arrSize;
    int** arr = new int* [arrSize];
    for (int index = 0; index < arrSize; ++index) {
        arr[index] = new int[arrSize];
    }
    for (int index = 0; index < arrSize; ++index) {
        for (int index2 = 0; index2 < arrSize; ++index2) {
            arr[index][index2] = index2 + index * arrSize;
            std::cout << arr[index][index2] << " ";
        }
        std::cout << "\n";
    }
    std::ofstream ofs("z3_3.txt", std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }

    for (int index = 0; index < arrSize; ++index)
        for (int index2 = 0; index2 < arrSize; ++index2)
            ofs.write((char*)&arr[index][index2], sizeof(int));

    ofs.close();

    int newNum;
    int numIndex;
    int numIndex2;
    std::cout << "Enter the number and its index1 && index2\n";
    std::cin >> newNum >> numIndex >> numIndex2;

    std::fstream fst("z3_3.txt", std::ios::binary | std::ios::in | std::ios::out);
    if (!fst.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }
    fst.seekg(0, std::ios::end);
    int lenght = fst.tellg();
    std::cout << "The file size ist: " << lenght << "bytes\n";

    //розрахунок позиції редагуємого елемента
    int possition = (numIndex * arrSize * sizeof(int)) + numIndex2 * sizeof(int);

    std::cout << "Position of the edited element: " << possition << '\n';
    //запис нового елемента
    fst.seekp(possition, std::ios::beg);
    fst.write((char*)&newNum, sizeof(int));
    fst.seekg(0);

    for (int index = 0; index < arrSize; ++index)
        for (int index2 = 0; index2 < arrSize; ++index2)
            fst.read((char*)&arr[index][index2], sizeof(int));

    for (int index = 0; index < arrSize; ++index) {
        for (int index2 = 0; index2 < arrSize; ++index2) {
            std::cout << arr[index][index2] << " ";
        }
        std::cout << "\n";
    }

}
void additionThirdEx3() {
    const int arrSize = 10;
    int arr[arrSize];
    for (int index = 0; index < arrSize; ++index) {
        arr[index] = index;
    }
    for (int index = 0; index < arrSize; ++index) {
        std::cout << arr[index] << " ";

    }
    std::ofstream ofs("z3_3.txt", std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }
    for (int index = 0; index < arrSize; ++index)
        ofs.write((char*)&arr[index], sizeof(int));

    ofs.close();

    int newNum;
    int numIndex;
    int numIndex2;
    std::cout << "\nEnter the index you want to delete\n";
    std::cin >> numIndex;

    std::fstream fst("z3_3.txt", std::ios::binary | std::ios::in | std::ios::out);
    if (!fst.is_open()) {
        std::cout << "An error has occurred\n";
        return;
    }
    fst.seekg(0, std::ios::end);
    int lenght = fst.tellg();
    int possition = (numIndex * sizeof(int)) - sizeof(int);
    //новий массив повинен бути на один елемент менше
    int tmp[arrSize - 1];

    fst.seekp(possition, std::ios::beg);
    //запис елементу з видаляємої позиції
    for (int index = numIndex + 1; index < arrSize; ++index) {
        fst.write((char*)&arr[index], sizeof(int));
    }
    fst.seekg(0);
    fst.read((char*)arr, sizeof(arr));
    fst.seekg(0);
    fst.seekg(0, std::ios::end);
    lenght = fst.tellg();
    std::cout << "The file size ist: " << lenght << "bytes\n";
    for (int index = 0; index < arrSize - 1; ++index) {
        std::cout << arr[index] << " ";
    }
    fst.close();
}
void fourEx() {
    std::ifstream firstFile;
    std::ifstream secondFile;

    firstFile.open("first.dat");
    secondFile.open("second.txt");

    if (!(firstFile.is_open() && secondFile.is_open())) {
        std::cout << "The error was occure\n";
        return;
    }
    char* firstBuf;
    char* secondBuf;
    int firstBufSize = 0;
    int secondBufSize = 0;

    firstBufSize = calculateSize(firstFile);
    secondBufSize = calculateSize(secondFile);

    //якщо розмір різний, то і вміст теж
    if (firstBufSize != secondBufSize) {
        std::cout << "Files have different sizes and content\n";
        return;
    }
    firstBuf = new char[firstBufSize];
    secondBuf = new char[secondBufSize];

    firstFile.read((char*)firstBuf, sizeof(int) * firstBufSize);
    secondFile.read((char*)secondBuf, sizeof(int) * secondBufSize);
    //розмір однаковий, тому без двух умов (index < secondBufSize)
    for (int index = 0; index < firstBufSize; ++index)
    {
        if (firstBuf[index] != secondBuf[index]) {
            std::cout << "Files have different content\n";
            return;
        }
    }
    std::cout << "Files are absolutely identical\n";
}
void additionFourEx() {
    int const N = 1024;

    bool isSameSize = true, isSameContext = true;
    bool isSecondParrOfFirst, isFirstPartOfSecond;

    // вибір файлів для порівняння
    ifstream* fin = new ifstream[2];
    fin[0].open("first.txt", ios::binary | ios::in);
    fin[1].open("second.txt", ios::binary | ios::in);

    unsigned char buf1[N], buf2[N];

    cout << "Порiвняння файлiв..." << endl;
    int f1, f2; // кількість прочитаних символів
    do
    {
        // читання файлів
        fin[0].read((char*)buf1, sizeof(buf1));
        fin[1].read((char*)buf2, sizeof(buf2));

        // кількість прочитаних символів
        f1 = fin[0].gcount();
        f2 = fin[1].gcount();
        buf1[f1] = '\0';
        buf2[f2] = '\0';

        // порівняння за розміром
        if (f1 != f2)
        {
            cout << "Файли мають рiзнi розмiри." << endl;
            isSameSize = false;
        }

        // порівняння вмісту
        for (int j = 0; j < f1; j++)
        {
            if (buf1[j] != buf2[j])
            {
                cout << "Файли мають рiзний вмiст." << endl;
                isSameContext = false;
                break;
            }
        }
    } while (!fin[0].eof() || !fin[1].eof()); // доки не дійдемо до кінця першого або другого файла

    if (isSameSize && isSameContext)
        cout << "Файли однаковi." << endl;

    // посимвольна перевірка вмісту першого файла в другому
    for (int index = 0, index2, index3; index < f1; ++index)
    {
        isSecondParrOfFirst = true;
        for (index2 = 0, index3 = index; index2 < f2; ++index2, ++index3)
        {
            if (isSecondParrOfFirst && buf1[index3] != buf2[index2])
            {
                isSecondParrOfFirst = false;
                break;
            }
        }
        if (isSecondParrOfFirst)
        {
            cout << "Second file is part of first file\n";
            break;
        }
    }

    // посимвольна перевірка вмісту першого файла в другому
    for (int index = 0, index2, index3; index < f2; ++index)
    {
        isFirstPartOfSecond = true;
        for (index2 = 0, index3 = index; index2 < f1; ++index2, ++index3)
        {
            if (isFirstPartOfSecond && buf2[index3] != buf1[index2])
            {
                isFirstPartOfSecond = false;
                break;
            }
        }
        if (isFirstPartOfSecond)
        {
            cout << "First file is part of second file\n";
            break;
        }
    }

    // закриття файлів
    fin[0].close();
    fin[1].close();
   
}
void ExFive() {
    int const N = 1024;
    ifstream* fin = new ifstream[2]; // Вибір файлів для порівняння
    fin[0].open("Shakespeare_WintersTale.txt", ios::binary | ios::in);
    fin[1].open("text.txt", ios::binary | ios::in);

  
    ofstream fout("5_task.txt", ios::binary | ios::in);
    if (!fout.is_open()) {//Перевіряю успішність створення об'єкта fout
        cout << "Помилка відкриття файлу!" << endl;// Якщо об'єкт не створився буде виведенно "Помилка відкриття файлу!"
        return; 
    }
    unsigned char buf1[N], buf2[N];
    cout << " Порівняння файлів..." << endl;
    do {
        fin[0].read((char*)buf1, sizeof buf1);
        fin[1].read((char*)buf2, sizeof buf2);
        int f1 = fin[0].gcount();//Кількість прочитаних символів
        int f2 = fin[1].gcount();//Кількість прочитаних символів
        if (f1 != f2) {
            cout << "Файли мають різні розміри." << endl;
            fin[0].close();// Закриття файлу
            fin[1].close();// Закриття файлу
            return;
        }
        long b = 0, n = 0;
        if (f1 != f2) {//Якщо файли не дорівнюють один одному
            for (int j = n; j <= b; j++) {
                if (buf1[j] != buf2[j])//Якщо буфери не дорівнюють один одному
                    cout << "Файли мають різний вміст." << endl;
                fout << buf1[j] << endl;
                fout << buf2[j];
            }
            n = b + 1;
        }
        fin[0].close();// Закриття файлу
        fin[1].close();// Закриття файлу
        return;
    } while (!fin[0].eof() || !fin[1].eof());//Якщо файли однакові
    cout << "Файли однакові." << endl;
    fin[0].close(); //Закриття файлу
    fin[1].close();//Закриття файлу

}

