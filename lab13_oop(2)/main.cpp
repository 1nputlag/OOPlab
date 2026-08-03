#include <iostream>
#include <string.h>
using namespace std;

#ifdef _MSC_VER

#else
  #define strcpy_s(dst, src) strncpy(dst, src, sizeof(dst)-1)
#endif

class book_series               // клас "серія книг"
{
public:
    book_series(char*, char*, float);   // конструктор
    void show_book(void);               // вивести інформацію про книгу
    void set_pages(int);                // встановити кількість сторінок

private:
    // Статичне поле — ОДНЕ на весь клас, не на кожен об'єкт
    static int page_count;

    char title[64];             // назва книги (не статичне — у кожного об'єкта своє)
    char author[64];            // автор
    float price;                // ціна
};


int book_series::page_count;

book_series::book_series(char* title, char* author, float price)
{
    strcpy_s(book_series::title, title);
    strcpy_s(book_series::author, author);
    book_series::price = price;
    // page_count тут НЕ ініціалізуємо — він спільний!
}

void book_series::show_book(void)
{
    cout << " Title: " << title    << endl;
    cout << "Author: " << author   << endl;
    cout << " Price: " << price    << endl;
    cout << " Pages: " << page_count << endl;  // читає спільне статичне поле
    cout << endl;
}

void book_series::set_pages(int pages)
{
    page_count = pages;         // змінює спільне статичне поле для ВСІХ об'єктів
}

int main()
{
    // Два об'єкти одного класу
    book_series Programming("C/C++ Programmer's Bible", "Kris Jamsa", 799.95f);
    book_series Word("Microsoft Office 2019 Inside", "Joe Habraken", 649.95f);

    // Об'єкт Word встановлює page_count = 256
    Word.set_pages(256);

    cout << "=== Після Word.set_pages(256) ===" << endl;
    Programming.show_book();    // Pages: 256  (хоча Programming не встановлював!)
    Word.show_book();           // Pages: 256

    cout << "=== Після Programming.set_pages(512) ===" << endl;
    // Об'єкт Programming змінює page_count = 512
    Programming.set_pages(512);
    Programming.show_book();    // Pages: 512
    Word.show_book();           // Pages: 512  (бачить нове значення!)

    cout << "Натисніть Enter...";
    cin.get();
    return 0;
}