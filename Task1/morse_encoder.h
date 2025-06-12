/* Программа-телеграф, которая принимает от пользователя сообщение
   и выводит его на экран в виде последовательности точек и тире */

#ifndef MORSE_ENCODER_H
#define MORSE_ENCODER_H

#include <string>
#include <unordered_map>
#include <optional>

class MorseEncoder {
public:
    MorseEncoder();

    /**
     * @brief Кодирует строку в азбуку Морзе
     * @param text Текст для кодирования
     * @param error [out] Ссылка для возврата сообщения об ошибке
     * @return std::optional<std::string> Закодированная строка или std::nullopt при ошибке
     */
    std::optional<std::string> encodeToMorse(const std::string& text, std::string& error) const;

private:
    std::unordered_map<char, std::string> morseAlphabet;
    std::string encodeChar(char c) const;
    bool isValidRussianChar(char c) const;
};

#endif // MORSE_ENCODER_H