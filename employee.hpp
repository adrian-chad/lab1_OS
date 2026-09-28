#pragma once

struct employee
{
    int num;       // идентификационный номер сотрудника
    char name[10]; // имя сотрудника
    double hours;  // количество отработанных часов

    bool operator<(const employee other)const
    {
        return num < other.num;
    }
};