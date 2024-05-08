#include <iostream>
#include <string>
#include <algorithm>
class BinaryNumber {
private:
    std::string binaryString; // Строка для хранения двоичного числа

public:
    // Конструктор, принимающий десятичное число и преобразующий его в двоичное
    BinaryNumber(int decimal) {
        binaryString = decimalToBinary(decimal);
    }

    // Конструктор, принимающий двоичную строку
    BinaryNumber(std::string binary) : binaryString(std::move(binary)) {}

    // Преобразование десятичного числа в двоичное в строкововом представление
    static std::string decimalToBinary(int decimal) {
        if (decimal == 0) return "0"; // Если число равно 0, возвращаем строку "0"
        std::string binary = ""; // Инициализируем пустую строку для результата
        while (decimal > 0) { // Пока десятичное число больше нуля
            binary = std::to_string(decimal % 2) + binary; // Добавляем остаток от деления на 2 к результату
            decimal /= 2; // Делим десятичное число на 2
        }
        return binary; // Возвращаем полученное двоичное число в виде строки
    }
    // Метод для конвертации двоичного числа в десятичное
    int toDecimal() const {
        int decimal = 0; // Инициализируем переменную для хранения десятичного числа
        for (size_t i = 0; i < binaryString.length(); ++i) { // Проходим по каждому символу двоичной строки
            if (binaryString[i] == '1') {
                decimal += 1 << (binaryString.length() - i - 1); // Прибавляем к десятичному числу соответствующую степень двойки
            }
        }
        return decimal; // Возвращаем полученное десятичное число
    }

    // Сложение двух двоичных чисел
    BinaryNumber operator+(const BinaryNumber& other) const {
        std::string result = ""; // Строка для результата сложения
        std::string a = this->binaryString; // Первое слагаемое
        std::string b = other.binaryString; // Второе слагаемое

        // Дополнение меньшей строки нулями до равной длины
        while (a.size() < b.size()) a = "0" + a;
        while (b.size() < a.size()) b = "0" + b;

        int carry = 0; // Переменная для хранения переноса из предыдущего разряда
        for (int i = a.size() - 1; i >= 0; --i) { // Проходим по строкам с конца к началу
            int bitA = a[i] - '0'; // Преобразуем символ в число (0 или 1)
            int bitB = b[i] - '0';
            int sum = bitA + bitB + carry; // Считаем сумму соответствующих битов и переноса
            result = std::to_string(sum % 2) + result; // Добавляем остаток от деления суммы на 2 к результату
            carry = sum / 2; // Определяем новый перенос
        }
        if (carry) result = "1" + result; // Если остался перенос, добавляем его к результату

        return BinaryNumber(result); // Возвращаем результат сложения в виде объекта класса BinaryNumber
    }

    // Вычитание двоих чисел аналогично обрабатывается, с учетом заимствования вместо переноса
// Вычитание двух двоичных чисел
   BinaryNumber operator-(const BinaryNumber& other) const {
    std::string result = ""; // Строка для результата вычитания
    std::string a = this->binaryString; // Первое (уменьшаемое) число
    std::string b = other.binaryString; // Второе (вычитаемое) число

    // Дополнение меньшей строки нулями до равной длины
    while (a.size() < b.size()) a = "0" + a; // Если строка a короче b, добавляем ведущие нули к a
    while (b.size() < a.size()) b = "0" + b; // Если строка b короче a, добавляем ведущие нули к b

    int borrow = 0; // Переменная для хранения заема из предыдущего разряда
    for (int i = a.size() - 1; i >= 0; --i) { // Проходим по строкам с конца к началу
        int bitA = a[i] - '0'; // Преобразуем символ в число (0 или 1)
        int bitB = b[i] - '0' + borrow; // Учитываем предыдущий заем при вычитании текущего бита

        if (bitA < bitB) { // Если бит из a меньше бита из b с учетом заема
            bitA += 2; // Добавляем 2 к биту из a, т.к. это эквивалентно займу из следующего старшего разряда
            borrow = 1; // Запоминаем, что произошел заем
        } else {
            borrow = 0; // Если заем не нужен, сбрасываем его значение
        }
        result = std::to_string(bitA - bitB) + result; // Вычитаем и добавляем результат к строке результата
    }

    // Удаление ведущих нулей из результата
    result.erase(0, std::min(result.find_first_not_of('0'), result.size()-1));
    // Используем std::min, чтобы избежать удаления последнего символа, если весь результат равен 0

    return BinaryNumber(result); // Возвращаем результат вычитания в виде объекта класса BinaryNumber
}
    // Умножение двоих чисел выполняется через сдвиг и сложение, имитируя стандартный алгоритм умножения
BinaryNumber operator*(const BinaryNumber& other) const {
    BinaryNumber product(0); // Создаем объект для хранения результата умножения, инициализируем его нулем
    std::string a = this->binaryString; // Сохраняем двоичное представление первого числа в строку a
    std::string b = other.binaryString; // Сохраняем двоичное представление второго числа в строку b

    std::reverse(b.begin(), b.end()); // Переворачиваем строку b, чтобы умножать начиная с младших разрядов
    for (size_t i = 0; i < b.size(); ++i) { // Проходим по всем разрядам строки b
        if (b[i] == '1') { // Если текущий бит в строке b равен 1
            std::string temp = a + std::string(i, '0'); // Добавляем к строке a i нулей справа, симулируя сдвиг на i позиций
            product = product + BinaryNumber(temp); // Складываем текущий продукт с полученным результатом сдвига, используя перегруженный оператор +
        }
    }

    return product; // Возвращаем результат умножения
}

// Отображение двоичного числа
void display() const {
    std::cout << binaryString << std::endl; // Выводим строковое представление двоичного числа на экран
}
};
int main() {
    int num1, num2;
    char operation;
    
    std::cout << "Enter operation: ";
    std::cin >> num1 >> operation >> num2; // Запрашиваем у пользователя операцию и два числа

    BinaryNumber binary1(num1), binary2(num2); // Создаем объекты класса BinaryNumber из введенных чисел

    std::cout << "First number in binary: ";
    binary1.display(); // Выводим первое число в двоичной форме

    std::cout << "Second number in binary: ";
    binary2.display(); // Выводим второе число в двоичной форме

    // Далее код выполняет выбранную операцию (+, -, *) над двумя двоичными числами и выводит результат.
    try {  // Открываем блок try для перехвата исключений
        switch (operation) { // Используем оператор switch для выбора действия в зависимости от введенной операции

            case '+': { // Если операция сложения
                auto result = binary1 + binary2; // Сложение двух двоичных чисел
                std::cout << "Result in binary: "; // Вывод сообщения о результате в двоичной форме
                result.display(); // Вывод результата сложения в двоичной форме
                std::cout << "Result in decimal: " << result.toDecimal() << std::endl; // Вывод результата сложения в десятичной форме
                break; // Выход из case
            }
            case '-': { // Если операция вычитания
                auto result = binary1 - binary2; // Вычитание второго двоичного числа из первого
                std::cout << "Result in binary: "; // Вывод сообщения о результате в двоичной форме
                result.display();  // Вывод результата вычитания в двоичной форме
                std::cout << "Result in decimal: " << result.toDecimal() << std::endl; // Вывод результата вычитания в десятичной форме
                break; // Выход из case
            }
            case '*': {
            // Если операция умножения

            auto result = binary1 * binary2; // Умножение двух двоичных чисел
            std::cout << "Result in binary: "; // Вывод сообщения о результате в двоичной форме
            result.display(); // Вывод результата умножения в двоичной форме
            std::cout << "Result in decimal: " << result.toDecimal() << std::endl; // Вывод результата умножения в десятичной форме
            break; // Выход из case
        }
            default:
            // Если ни один из вышеуказанных случаев не подходит (неподдерживаемая операция)

            std::cerr << "Unsupported operation" << std::endl; // Вывод сообщения об ошибке
    }
} catch (const std::exception& e) {
    // Блок catch для перехвата и обработки исключений

    std::cerr << "Error: " << e.what() << std::endl; // Вывод сообщения об ошибке с подробностями исключения
}

return 0;}// Возвращаем 0, чтобы указать, что программа завершилась успешно
