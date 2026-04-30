#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <exception>
#include "json.hpp"

using json = nlohmann::json;

class OutOfStockException : public std::exception 
{
public:
    const char* what() const noexcept override 
    {
        return "Error";
    }
};

struct Order
{
	std::string name;
    int quantity;
};

std::queue<Order> readOrdersFromJSON(const std::string& filename) 
{
    std::queue<Order> orders;
    std::ifstream file(filename);

    if (file.is_open()) 
    {
        json j;
        file >> j;
        for (const auto& item : j) 
        {
            orders.push({ item["name"], item["quantity"] });
        }
    }
    return orders;
}

void processOrders(std::map<std::string, int>& stock, std::queue<Order>& orders) 
{
    while (!orders.empty()) 
    {
        Order current = orders.front();

        // Перевірка: чи є товар на складі
        if (stock[current.name] < current.quantity) 
            throw OutOfStockException();

        // Оновлюємо склад та видаляємо замовлення з черги
        stock[current.name] -= current.quantity;
        orders.pop();

        std::cout << "Operated: " << current.name << std::endl;
    }
}

void saveToCSV(const std::string& filename, const std::map<std::string, int>& stock) 
{
    std::ofstream file(filename);

    if (!file.is_open()) 
    {
        std::cerr << "Cant open file!" << std::endl;
        return;
    }

    // Заголовок
    file << "Product,Quantity\n";

    // Прохід по всьому масиву
    for (const auto& item : stock)
        file << item.first << "," << item.second << "\n";


    file.close();
    std::cout << "Succesfull " << std::endl;
}

