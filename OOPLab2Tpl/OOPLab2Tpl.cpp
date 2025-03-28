﻿// OOPLab2Tpl.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include "Tasks.cpp"
#include "Examples.cpp"


/// @brief 
/// @return 
int main()
{
    cout << "OOP. Template for laboratory work #2.\n";

    char ch = '5';
    do {
        system("cls");
        MenuTask();
        ch = cin.get();
        
        cin.get();

        switch (ch) {
        case '1': task1();   break;
        case '2': task3_encrypt();   break;
        case '3': task3_decrypt();   break;
        case '4': task4(); break;  
		case '5': Examples(); break;
		case '6': return 0;
	    }
        cout << " Press any key and enter\n";
        ch = cin.get();
    } while (ch != '6');

    return 0;
}

