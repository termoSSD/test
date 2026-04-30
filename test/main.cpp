#include "func.hpp"

int main() {
    // Імітація початкового складу
    std::map<std::string, int> stock = {
        {"Laptop", 5},
        {"Phone", 10}
    };

    try 
    {
        // Читаємо замовлення з файлу
        std::queue<Order> orders = readOrdersFromJSON("data.json");

        // Опрацьовуємо їх
        processOrders(stock, orders);

        // Зберігаємо результат у CSV
        saveToCSV("remaining_stock.csv", stock);

        std::cout << "Succesfull opdated in CSV.\n";
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
