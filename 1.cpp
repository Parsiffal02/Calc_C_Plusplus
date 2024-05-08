#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

class BinaryNumber {
private:
    std::string binaryString; // Храним двоичное число как строку
    static const size_t NUM_BITS = 8; // Размерность для представления числа

public:
    // Конструктор принимает десятичное число
    BinaryNumber(int decimal) {
        binaryString = decimalToBinary(decimal);
    }

    // Преобразование десятичного числа в двоичное с учетом отрицательных значений
    static std::string decimalToBinary(int decimal) {
        std::bitset<NUM_BITS> binary(decimal);
        return binary.to_string();
    }

    // Преобразование двоичного числа в десятичное с учетом отрицательных значений
    static int binaryToDecimal(const std::string& binary) {
        if (binary.length() > NUM_BITS) throw std::invalid_argument("Binary string is too long");
        std::bitset<NUM_BITS> set(binary);
        return static_cast<int>(set.to_ulong());
    }

    // Сложение двух двоичных чисел
    BinaryNumber operator+(const BinaryNumber& other) const {
        int sum = binaryToDecimal(this->binaryString) + binaryToDecimal(other.binaryString);
        return BinaryNumber(sum);
    }

    // Вычитание двух двоичных чисел
    BinaryNumber operator-(const BinaryNumber& other) const {
        int difference = binaryToDecimal(this->binaryString) - binaryToDecimal(other.binaryString);
        return BinaryNumber(difference);
    }

    // Умножение двух двоичных чисел
    BinaryNumber operator*(const BinaryNumber& other) const {
        int product = binaryToDecimal(this->binaryString) * binaryToDecimal(other.binaryString);
        return BinaryNumber(product);
    }

    // Отображение двоичного числа
    void display() const {
        std::cout << binaryString.substr(binaryString.size() - NUM_BITS) << " (" << binaryToDecimal(binaryString) << ")" << std::endl;
    }
};

int main() {
    int num1, num2;
    char operation;

    std::cout << "Enter operation: ";
    std::cin >> num1 >> operation >> num2;

    BinaryNumber binary1(num1), binary2(num2);

    std::cout << "First number in binary: ";
    binary1.display();

    std::cout << "Second number in binary: ";
    binary2.display();

    try {
        switch (operation) {
            case '+': {
                auto result = binary1 + binary2;
                std::cout << "Result: ";
                result.display();
                break;
            }
            case '-': {
                auto result = binary1 - binary2;
                std::cout << "Result: ";
                result.display();
                break;
            }
            case '*': {
                auto result = binary1 * binary2;
                std::cout << "Result: ";
                result.display();
                break;
            }
            default:
                std::cerr << "Unsupported operation" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}