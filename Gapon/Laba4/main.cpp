#include <iostream>
#include <string.h>
#include <stdio.h>
#include "parser.h"


int main() {
    setlocale(LC_ALL, "Russian");
    polinom res1, res2, res3;
    calculate calculator;
    while (true) {
        system("cls");
        cout << "Введите номер полинома (1 или 2)\n";
        cout << "Затем введите полином в такеом формате: (ПРИМЕР 2x^2y^2z^2+...)\n";
        cout << " 1) ";
        res1.h == NULL ? cout << "Пусто" : cout << res1;
        cout << "\n 2) ";
        res2.h == NULL ? cout << "Пусто" : cout << res2;
        cout << "\n 3) Выход.\n";
        cout << "Чтобы получить сумму полиномов, нажмите '+'\n";
        cout << "Чтобы получить произведение плиномов , нажмите '*'\n";
        char x;
        cin >> x;
        if (x == '1') {
            string s;
            cin >> s;
            res1 = calculator.parser(s);
        }
        else

            if (x == '2') {
                string s;
                cin >> s;
                res2 = calculator.parser(s);
            }
            else

                if (x == '+') {
                    if (res1.h == NULL || res2.h == NULL) throw - 1;
                    res3 = res1 + res2;
                    if (res3.h == NULL) cout << "0";
                    if (res3.h != NULL) cout << res3;
                    cout << "\n\n Назад в меню (3).\n Если вы хотите, чтобы решение стало 1 или 2 полиномом введите (1) или (2), если нет (3)\n";
                    int g;
                    cin >> g;
                    if (g == 1)
                        res1 = res3;
                    if (g == 2)
                        res2 = res3;
                    if ((g <= 0) || (g > 3)) throw - 3;
                }
                else

                    if (x == '*') {
                        if (res1.h == NULL || res2.h == NULL) throw - 1;
                        res3 = res1 * res2;
                        cout << res3;
                        cout << "\n\n Назад в меню (3).\n Если вы хотите, чтобы решение стало 1 или 2 полиномом введите (1) или (2), если нет (3)\n";
                        int g;
                        cin >> g;
                        if (g == 1)
                            res1 = res3;
                        if (g == 2)
                            res2 = res3;
                        if ((g <= 0) || (g > 3)) throw - 3;
                    }
                    else {
                        return 0;
                    }
    }
    return 0;
}