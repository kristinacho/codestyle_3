﻿#include <iostream>
#include <string>
#include <unordered_map>
#include <locale>
#include <codecvt>

// Программа-телеграф: переводит русские буквы в азбуку Морзе

int main() {
    // Отобразим русские буквы в верхнем регистре на коды Морзе
    std::unordered_map<wchar_t, std::wstring> morse = {
        {L'А', L"·−"}, {L'Б', L"−···"}, {L'В', L"·−−"}, {L'Г', L"−−·"},
        {L'Д', L"−··"}, {L'Е', L"·"}, {L'Ж', L"···−"}, {L'З', L"−−··"},
        {L'И', L"··"}, {L'Й', L"·−−−"}, {L'К', L"−·−"}, {L'Л', L"·−··"},
        {L'М', L"−−"}, {L'Н', L"−·"}, {L'О', L"−−−"}, {L'П', L"·−−·"},
        {L'Р', L"·−·"}, {L'С', L"···"}, {L'Т', L"−"}, {L'У', L"··−"},
        {L'Ф', L"··−·"}, {L'Х', L"····"}, {L'Ц', L"−·−·"}, {L'Ч', L"−−−·"},
        {L'Ш', L"−−−−"}, {L'Щ', L"−−·−"}, {L'Ъ', L"·−−·−·"}, {L'Ы', L"−·−−"},
        {L'Ь', L"−··−"}, {L'Э', L"··−··"}, {L'Ю', L"··−−"}, {L'Я', L"·−·"}
    };

    // Для корректного ввода/вывода русских символов используем wstring и wcin/wcout
    std::wcout << L"Введите сообщение на русском языке: ";
    std::wstring input;
    std::getline(std::wcin, input);

    // Преобразуем в верхний регистр (для русских символов)
    for (auto& ch : input) {
        if (ch >= L'а' && ch <= L'я') {
            ch = ch - L'а' + L'А';
        }
        else if (ch == L'ё') {
            ch = L'Ё'; // Ё отдельно, если понадобится
        }
    }

    std::wcout << L"Сообщение в азбуке Морзе:\n";

    for (wchar_t ch : input) {
        if (ch == L' ') {
            // Разделяем слова пробелом (например, 3 пробела)
            std::wcout << L"   ";
        }
        else if (morse.count(ch)) {
            std::wcout << morse[ch] << L" ";
        }
        else {
            // Если символ не найден, выводим знак вопроса
            std::wcout << L"? ";
        }
    }

    std::wcout << std::endl;
    return 0;
}
