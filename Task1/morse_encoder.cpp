/* Программа-телеграф, которая принимает от пользователя сообщение
   и выводит его на экран в виде последовательности точек и тире */

#include "morse_encoder.h"
#include <cctype>

MorseEncoder::MorseEncoder() {
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

std::optional<std::string> MorseEncoder::encodeToMorse(const std::string& text, std::string& error) const {
    if (text.empty()) {
        error = "Введена пустая строка";
        return std::nullopt;
    }

    std::string result = "";
    for (char c : text) {
        if (c == ' ') {
            result += "  ";
            continue;
        }

        char upperC = toupper(c);
        if (!isValidRussianChar(upperC)) {
            error = "Неподдерживаемый символ: " + std::string(1, c);
            return std::nullopt;
        }

        std::string morseChar = encodeChar(upperC);
        if (morseChar.empty()) {
            error = "Не удалось закодировать символ: " + std::string(1, c);
            return std::nullopt;
        }

        result += morseChar + " ";
    }

    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

std::string MorseEncoder::encodeChar(char c) const {
    auto it = morseAlphabet.find(c);
    return it != morseAlphabet.end() ? it->second : "";
}

bool MorseEncoder::isValidRussianChar(char c) const {
    return (c >= 'А' && c <= 'Я') || c == 'Ё' || c == ' ';
}