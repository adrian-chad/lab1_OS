#include <iostream>
#include <fstream>
#include <string>
#include "employee.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    std::string file_name = argv[1];
    int quantity = std::stoi(argv[2]);
    if (quantity <= 0)
        return 1;
    std::ofstream file(file_name, std::ios::binary);
    if (!file)
        return 1;

    employee emp;
    for (int i = 0; i < quantity; ++i)
    {
        std::cout << "Запись " << i + 1 << ":\n";

        std::cout << "Номер сотрудника: ";
        std::cin >> emp.num;

        std::cout << "Имя сотрудника: ";
        std::cin.ignore();
        std::cin.getline(emp.name, 10);

        std::cout << "Отработано часов: ";
        std::cin >> emp.hours;

        file.write(reinterpret_cast<const char *>(&emp), sizeof(emp));
    }
    file.close();
    return 0;
}