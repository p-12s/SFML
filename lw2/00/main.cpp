#include <iostream>

int main()
{

    // цикл выводит числа от 1 до 100
    // int num = 1;
    // // условие: пока num меньше или равно 100
    // while (num <= 100)
    // {
    //     std::cout << num << std::endl;
    //     // добавляем к числу 1
    //     // оператор += это сокращение от `num = num + 1`
    //     num += 1;
    // }

    // начальное действие: объявить переменную num, равную 1
    // условие: пока num меньше или равно 100
    // после каждого шага (итерации) цикла добавляем к num единицу
    // for (int num = 1; num <= 100; num += 1)
    // {
    //     // если остаток от деления на 3 равен 0
    //     if ((num % 3 == 0) && (num % 5 == 0))
    //     {
    //         // выводим FizzBuzz
    //         std::cout << "FizzBuzz" << std::endl;
    //     }
    //     else if (num % 3 == 0)
    //     {
    //         // выводим Fizz
    //         std::cout << "Fizz" << std::endl;
    //     }
    //     else if (num % 5 == 0)
    //     {
    //         // выводим Buzz
    //         std::cout << "Buzz" << std::endl;
    //     }
    //     else
    //     {
    //         // выводим число num
    //         std::cout << num << std::endl;
    //     }
    // }

    for (int num = 1; num <= 100; num += 1)
    {
        switch (num % 15)
        {
        case 0:
            std::cout << "FizzBuzz" << std::endl;
            break;
        case 5:
        case 10:
            std::cout << "Buzz" << std::endl;
            break;
        case 3:
        case 6:
        case 9:
        case 12:
            std::cout << "Fizz" << std::endl;
            break;
        default:
            // выводим само число
            std::cout << num << std::endl;
        }
    }
}