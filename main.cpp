#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>  
#include <sys/wait.h>   
#include "employee.hpp"


int runProcess(const char* path, char* const args[]) {
    std::cout.flush();  

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Ошибка fork()\n";
        return -1;
    }

    if (pid == 0) {
        execvp(path, args);
        std::cerr << "Не удалось запустить " << path << "\n";
        _exit(1);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        std::cerr << "Ошибка waitpid()\n";
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;
}

int main() {
    std::string binFile;
    int count;

    std::cout << "Имя бинарного файла: ";
    std::cin >> binFile;

    std::cout << "Количество записей: ";
    std::cin >> count;

    if (count <= 0) {
        return 1;
    }

    std::string countStr = std::to_string(count);

    char* creatorArgs[] = {
        const_cast<char*>("Creator"),
        const_cast<char*>(binFile.c_str()),
        const_cast<char*>(countStr.c_str()),
        nullptr
    };

    int code = runProcess("./Creator", creatorArgs);
    if (code != 0) {
        return 1;
    }

    std::ifstream fin(binFile, std::ios::binary);
    if (!fin) {
        return 1;
    }

    std::cout << "\nСодержимое файла " << binFile << ":\n";
    std::cout << "Номер | Имя | Часы\n";

    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        std::cout << emp.num << " | " << emp.name << " | " << emp.hours << "\n";
    }
    fin.close();

    std::string reportFile;
    double payment;

    std::cout << "\nИмя файла отчёта: ";
    std::cin >> reportFile;

    std::cout << "Оплата за час: ";
    std::cin >> payment;

    if (payment <= 0) {

        return 1;
    }

    std::string rateStr = std::to_string(payment);

    char* reporterArgs[] = {
        const_cast<char*>("Reporter"),
        const_cast<char*>(binFile.c_str()),
        const_cast<char*>(reportFile.c_str()),
        const_cast<char*>(rateStr.c_str()),
        nullptr
    };

    code = runProcess("./Reporter", reporterArgs);
    if (code != 0) {
        return 1;
    }

    std::ifstream file2(reportFile);
    if (!file2) {
        return 1;
    }

    std::string line;
    std::cout << "\nОтчёт:\n";
    while (std::getline(file2, line)) {
        std::cout << line << "\n";
    }
    file2.close();

    return 0;
}