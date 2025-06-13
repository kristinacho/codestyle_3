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
     * @brief Êîäèðóåò ñòðîêó â àçáóêó Ìîðçå
     * @param text Òåêñò äëÿ êîäèðîâàíèÿ
     * @param error [out] Ññûëêà äëÿ âîçâðàòà ñîîáùåíèÿ îá îøèáêå
     * @return std::optional<std::string> Çàêîäèðîâàííàÿ ñòðîêà èëè std::nullopt ïðè îøèáêå
     */
    std::optional<std::string> encodeToMorse(const std::string& text, std::string& error) const;

private:
    std::unordered_map<char, std::string> morseAlphabet;
    std::string encodeChar(char c) const;
    bool isValidRussianChar(char c) const;
};

#endif // MORSE_ENCODER_H
