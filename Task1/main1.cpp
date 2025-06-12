/* ���������-��������, ������� ��������� �� ������������ ���������
   � ������� ��� �� ����� � ���� ������������������ ����� � ���� */

#include "morse_encoder.h"
#include <iostream>
#include <string>
#include <unordered_map>


int main() {
    MorseEncoder encoder = nullptr;
    std::string input = "";

    std::cout << "������� ��������� ��� ����������� � ������ �����: ";
    std::getline(std::cin, input);

    try {
        std::string morseCode = encoder.encodeToMorse(input);
        std::cout << "�������������� ���������: " << morseCode << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "������: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}