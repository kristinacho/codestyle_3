/* ���������-��������, ������� ��������� �� ������������ ���������
   � ������� ��� �� ����� � ���� ������������������ ����� � ���� */

#ifndef MORSE_ENCODER_H
#define MORSE_ENCODER_H

#include <string>
#include <unordered_map>
#include <optional>

class MorseEncoder {
public:
    MorseEncoder();

    /**
     * @brief �������� ������ � ������ �����
     * @param text ����� ��� �����������
     * @param error [out] ������ ��� �������� ��������� �� ������
     * @return std::optional<std::string> �������������� ������ ��� std::nullopt ��� ������
     */
    std::optional<std::string> encodeToMorse(const std::string& text, std::string& error) const;

private:
    std::unordered_map<char, std::string> morseAlphabet;
    std::string encodeChar(char c) const;
    bool isValidRussianChar(char c) const;
};

#endif // MORSE_ENCODER_H