#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

#include "Tasks.h"
#include "Examples.h"

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Calculation of expressions using bitwise operations  \n";
    cout << "    2.  Data encryption using structures with bit fields \n";
    cout << "    3.  Data decryption using structures with bit fields \n";
    cout << "    4.  Calculation of expressions using bitwise operations (extra) \n";
    cout << "    5.  Examples of problems using bitwise operations \n";
    cout << "    6.  Exit \n";
}

struct EncryptedChar {
    uint16_t lower : 4;   // Молодші 4 біти ASCII
    uint16_t position : 7; // Позиція символу (7 бітів)
    uint16_t upper : 4;   // Старші 4 біти ASCII
    uint16_t parity : 1;  // Біт парності
};

union EncodedData {
    EncryptedChar fields;
    uint16_t value;
};

bool calculateParity(uint16_t data) {
    bool parity = 0;
    while (data) {
        parity ^= (data & 1); 
        data >>= 1;
    }
    return parity;
}

// uint16_t encryptChar(char ch, int position) {
//     uint16_t upper = (ch >> 4) & 0xF;  // Старші 4 біти ASCII
//     uint16_t lower = ch & 0xF;         // Молодші 4 біти ASCII
//     uint16_t pos = position & 0x7F;    // Позиція в рядку (7 бітів)

//     uint16_t encrypted = upper | pos | lower;
//     uint16_t parity = calculateParity(encrypted) ? 0x8000 : 0;

//     return encrypted;
// }

// char decryptChar(uint16_t encrypted) {
//     uint16_t upper = encrypted & 0xF;
//     uint16_t lower = encrypted & 0xF;
//     return (upper << 4) | lower;
// }

uint16_t encryptCharUnion(char ch, int position) {
    EncodedData data;
    data.fields.upper = (ch >> 4) & 0xF;
    data.fields.lower = ch & 0xF;
    data.fields.position = position & 0x7F;
    data.fields.parity = calculateParity(data.value);
    return data.value;
}

// Функція дешифрування символу
char decryptCharUnion(uint16_t encrypted) {
    EncodedData data;
    data.value = encrypted;
    return (data.fields.upper << 4) | data.fields.lower;
}

void task1() {
    cout << " Calculation of expressions using bitwise operations  \n";

    int a, b, c, d;

    //"Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.\n";
    cout << "Expression: x = 37 * b + (d * 31 + 12 * a) / 2048 - (65 * c + d * 14). \n";
    cout << "Input a b c d" << endl;

	cin >> a >> b >> c >> d;

    auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); cin.get(); cin.get(); return; }

    int x = (37*b) + (((d*31)+(12*a))/2048) - (65*c) + (d*14);
    int y = (b << 5) + (b << 2) + b + ((((d << 5) - d) + ((a << 3) + (a << 2))) >> 11) - ((c << 6) + c) + ((d << 4) - d - d);
    
	cout << "x= " << x  << "  y=" << y << " a=" << a << " b=" << b << " c=" << c << " d=" << d;
	cin.get();
}


// Функція шифрування символу

// Функція шифрування тексту
void task3_encrypt() {
    cout << " Data encryption using bitwise operations  \n";
    
    ifstream inputFile("encryption/input.txt");
    ofstream outputFile("encryption/encrypted.bin", ios::binary);

    if (!inputFile || !outputFile) {
        cerr << "Error while opening files!";
        return;
    }

    string text;
    getline(inputFile, text);
    inputFile.close();

    text.resize(128, ' '); //змінює розмір на 128 і заповнює пустоту пробілами

    vector<uint16_t> encryptedData;
    for (size_t i = 0; i < text.size(); ++i) {
        encryptedData.push_back(encryptCharUnion(text[i], i));
    }

    outputFile.write(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size() * sizeof(uint16_t));
    outputFile.close();

    cout << "File encrypted successfully!";
    cin.get();
}

// Функція дешифрування тексту
void task3_decrypt() {
    cout << " Data decryption using bitwise operations  \n";
    
    ifstream inputFile("encryption/encrypted.bin", ios::binary);
    ofstream outputFile("encryption/output.txt");

    if (!inputFile || !outputFile) {
        cerr << "Error while opening files!";
        return;
    }

    vector<uint16_t> encryptedData(128);
    inputFile.read(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size() * sizeof(uint16_t));
    inputFile.close();

    string decryptedText;
    for (size_t i = 0; i < encryptedData.size(); ++i) {
        decryptedText += decryptCharUnion(encryptedData[i]);
    }

    cout << "Decrypted text:\n" << decryptedText << endl;
    outputFile << decryptedText;
    outputFile.close();

    cout << "File decrypted successfully!";
    cin.get();
}


void task4()
{
    cout << " Calculation of expressions using bitwise operations  \n";

    int a, b;

    //"Приклад обчислення виразу використовуючи тiльки побiтовi операцiї.\n";
    cout << "Expression: x = (20 * b - a * 120) / 32 + (a + 32 * b) / 128 + (a + b)%16. \n";
    cout << "Input a b" << endl;

	cin >> a >> b;

    auto st = cin.rdstate();
	if (st != cin.goodbit) { cin.clear(); cout << " error \n"; cin.get(); cin.get(); cin.get(); cin.get(); return; }

    int x = (20 * b - a * 120) / 32 + (a + 32 * b) / 128 + (a + b) % 16;
    int y = (((b << 4) + (b << 2) - (a << 7) - (a << 3)) >> 5) + ((a + (b << 5)) >> 7) + (a+b) - (a+b) >> 4;
    
	cout << "x= " << x  << "  y=" << y << " a=" << a << " b=" << b;
	cin.get();
}


// void task2_encrypt()
// {
//     cout << " Data encryption using bitwise operations  \n";
    
//     ifstream inputFile("encryption/input.txt");
//     ofstream outputFile("encryption/encrypted.bin", ios::binary);

//     if (!inputFile || !outputFile) {
//         cerr << "Error while opening file!";//"Помилка відкриття файлів!\n";
//         return;
//     }

//     string text;
//     getline(inputFile, text);
//     inputFile.close();

//     text.resize(128, ' '); //змінює розмір на 128 і заповнює пустоту пробілами

//     vector<uint16_t> encryptedData;
//     for (size_t i = 0; i < text.size(); ++i) {
//         encryptedData.push_back(encryptChar(text[i], i));
//     }

//     outputFile.write(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size() * sizeof(uint16_t));
//     outputFile.close();

//     cout << "File encrypted successfully!";//"Файл зашифровано успішно!\n";
// 	cin.get();
// }

// void task2_decrypt()
// {
//     cout << " Data decryption using bitwise operations  \n";
    
//     ifstream inputFile("encryption/encrypted.bin", ios::binary);
//     ofstream outputFile("encryption/output.txt");

//     if (!inputFile || !outputFile) {
//         cerr << "Error while opening files!";//"Помилка відкриття файлів!\n";
//         return;
//     }

//     vector<uint16_t> encryptedData(128);
//     inputFile.read(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size() * sizeof(uint16_t));
//     inputFile.close();

//     string decryptedText;
//     for (size_t i = 0; i < encryptedData.size(); ++i) {
//         decryptedText += decryptChar(encryptedData[i]);
//     }

//     cout << "Decrypted text:\n" << decryptedText << endl;
//     outputFile << decryptedText;
//     outputFile.close();

//     cout << "File decrypted successfully!";//"Файл розшифровано успішно!\n";
// 	cin.get();
// }
