#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

// Функция для инициализации словаря с кодом Морзе
void initializeMorseCode(unordered_map<char, string>& morseCode) {
    morseCode['А'] = "·−";
    morseCode['Б'] = "−···";
    morseCode['В'] = "·−−";
    morseCode['Г'] = "−−·";
    morseCode['Д'] = "−··";
    morseCode['Е'] = "·";
    morseCode['Ж'] = "···−";
    morseCode['З'] = "−−··";
    morseCode['И'] = "··";
    morseCode['Й'] = "·−−−";
    morseCode['К'] = "−·−";
    morseCode['Л'] = "·−··";
    morseCode['М'] = "−−";
    morseCode['Н'] = "−·";
    morseCode['О'] = "−−−";
    morseCode['П'] = "·−−·";
    morseCode['Р'] = "·−·";
    morseCode['С'] = "···";
    morseCode['Т'] = "−";
    morseCode['У'] = "··−";
    morseCode['Ф'] = "··−·";
    morseCode['Х'] = "····";
    morseCode['Ц'] = "−·−·";
    morseCode['Ч'] = "−−−·";
    morseCode['Ш'] = "−−−−";
    morseCode['Щ'] = "−−·−";
    morseCode['Ъ'] = "·−−·−·";
    morseCode['Ы'] = "−·−−";
    morseCode['Ь'] = "−··−";
    morseCode['Э'] = "··−··";
    morseCode['Ю'] = "··−−";
    morseCode['Я'] = "·−·";
}

int main() {
    unordered_map<char, string> morseCode;
    initializeMorseCode(morseCode);

    string message;
    cout << "Введите сообщение (на русском): ";
    getline(cin, message);

    cout << "Сообщение в коде Морзе: ";

    for (char ch : message) {
        ch = toupper(ch); // Приводим к верхнему регистру
        if (morseCode.find(ch) != morseCode.end()) {
            cout << morseCode[ch] << " "; // Выводим код Морзе с пробелом
        }
        else if (ch == ' ') {
            cout << "/ "; // Разделитель между словами
        }
    }

    cout << endl;

    return 0;
}
