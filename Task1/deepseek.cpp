/* Программа-телеграф, которая принимает от пользователя сообщение
   и выводит его на экран в виде последовательности точек и тире */

#include <iostream>
#include <string>
#include <unordered_map>
#include <optional>
#include <cctype>

class MorseEncoder {
public:
    MorseEncoder() {
        morseAlphabet = {
            {'А', "·−"}, {'Б', "−···"}, {'В', "·−−"}, {'Г', "−−·"},
            {'Д', "−··"}, {'Е', "·"}, {'Ж', "···−"}, {'З', "−−··"},
            {'И', "··"}, {'Й', "·−−−"}, {'К', "−·−"}, {'Л', "·−··"},
            {'М', "−−"}, {'Н', "−·"}, {'О', "−−−"}, {'П', "·−−·"},
            {'Р', "·−·"}, {'С', "···"}, {'Т', "−"}, {'У', "··−"},
            {'Ф', "··−·"}, {'Х', "····"}, {'Ц', "−·−·"}, {'Ч', "−−−·"},
            {'Ш', "−−−−"}, {'Щ', "−−·−"}, {'Ъ', "·−−·−·"}, {'Ы', "−·−−"},
            {'Ь', "−··−"}, {'Э', "··−··"}, {'Ю', "··−−"}, {'Я', "·−·−"},
            {' ', " "}
        };
    }

    std::string encodeToMorse(const std::string& text) const {
        if (text.empty()) {
            throw std::invalid_argument("Введена пустая строка");
        }

        std::string result = "";
        for (char c : text) {
            if (c == ' ') {
                result += "  ";
                continue;
            }

            char upperC = toupper(c);
            if (!isValidRussianChar(upperC)) {
                throw std::invalid_argument("Неподдерживаемый символ: " + std::string(1, c));
            }

            std::string morseChar = encodeChar(upperC);
            if (morseChar.empty()) {
                throw std::invalid_argument("Не удалось закодировать символ: " + std::string(1, c));
            }

            result += morseChar + " ";
        }

        if (!result.empty()) {
            result.pop_back();
        }

        return result;
    }

private:
    std::unordered_map<char, std::string> morseAlphabet;

    std::string encodeChar(char c) const {
        auto it = morseAlphabet.find(c);
        return it != morseAlphabet.end() ? it->second : "";
    }

    bool isValidRussianChar(char c) const {
        return (c >= 'А' && c <= 'Я') || c == 'Ё' || c == ' ';
    }
};

int main() {
    MorseEncoder encoder;
    std::string input = "";

    std::cout << "Введите сообщение для кодирования в азбуку Морзе: ";
    std::getline(std::cin, input);

    try {
        std::string morseCode = encoder.encodeToMorse(input);
        std::cout << "Закодированное сообщение: " << morseCode << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}