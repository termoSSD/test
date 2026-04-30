#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

struct Order
{
	std::string name;
	int count;
};

// Функція читання JSON файлу
std::vector<Order> readJSON(const std::string& filename)
{
    std::vector<Order> students;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return students;
    }

    // Блок try-catch для перехоплення винятків (Exceptions)
    try
    {
        json j_array;
        file >> j_array;

        for (const auto& item : j_array)
        {
            Order order;

            // Витягуємо дані за ключами
            order.name = item["name"];
            order.count = item["count"];

            students.push_back(order);
        }
    }
    catch (const json::parse_error& e)
    {
        /*
        Якщо JSON зламаний(немає дужки, коми тощо)
        програма виведе цю помилку.
        */
        std::cerr << "JSON parsing error (Parse Error): " << e.what() << std::endl;
    }
    catch (const json::type_error& e)
    {
        // Якщо ми очікували число (вік), а в JSON там написаний текст
        std::cerr << "JSON data type error (Type Error): " << e.what() << std::endl;
    }

    file.close();
    return students;
}

void writeCSV()
{

}