#include <fstream>
#include <string>
#include "employee.hpp"
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    std::string bin_file_name = argv[1];

    std::string report_file_name = argv[2];

    double payment = std::stod(argv[3]);
    if (payment <= 0)
        return 1;

    std::ifstream file1(bin_file_name, std::ios::binary);
    if (!file1)
        return 1;
    std::vector<employee> employees;
    employee emp;
    while (file1.read(reinterpret_cast<char *>(&emp), sizeof(emp)))
    {
        employees.push_back(emp);
    }
    file1.close();
    std::sort(employees.begin(), employees.end());

    std::ofstream file2(report_file_name);
    if (!file2)
        return 1;
    file2 << "Отчет по файлу «" << bin_file_name << "»\n";
    file2 << "Номер сотрудника, имя сотрудника, часы, зарплата\n";

    double salary;

    for (const auto &e : employees)
    {
        salary = e.hours * payment;
        file2 << e.num << ", " << e.name << ", " << e.hours << ", " << salary << "\n";
    }
    file2.close();
    return 0;
}