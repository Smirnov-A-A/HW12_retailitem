#include <iostream>
#include <string>
#include <vector>

///////////////////////////////////////Class RetailItem//////////////////////////////////////
class RetailItem {

public:
    //Constructor
    RetailItem(std::string description, int quantity, double price):
        m_description{description}, m_quantity_in_stock{quantity}, m_price{price} {

    }

    //Setters
    void setDescription() {
        std::cout << "Enter item description: ";
        std::cin >> m_description;
    }

    void setQuantity() {
        std::cout << "Enter item quantity: ";
        std::cin >> m_quantity_in_stock;
    }

    void setPrice() {
        std::cout << "Enter item price: ";
        std::cin >> m_price;
    }

    //Friends
    friend class CashRegister;

private:
    std::string m_description;
    int m_quantity_in_stock;
    double m_price;

};

////////////////////////////////////////Class CashRegister/////////////////////////////////////
class CashRegister {

public:
    //Constructor
    CashRegister(double total = 0): m_total(total) {

    }

    //Metods
    //Add item to the list
    void buyItem(RetailItem &item) {
        //Проверяем наличие товара на складе
        if (item.m_quantity_in_stock == 0) {
            std::cout << "This item is out of stock" << '\n';
            return;
        }
        else {
            //Добавляем товар в список покупок
            m_itemList.push_back(item);
            //Уменьшаем количество на складе на 1
            --item.m_quantity_in_stock;

        }
    }

    //Get total price of all items in list
    double getTotal() {
        for (int i = 0; i < m_itemList.size(); ++i) {
            m_total += m_itemList[i].m_price;
        }
        return m_total;
    }

    //Show list
    void showItems() {
        if (m_itemList.empty()) {
            std::cout << "Shopping list is empty!" << '\n';
            return;
        }
        else {
            std::cout << "Shopping list:" << '\n';
            for (int i = 0; i < m_itemList.size(); ++i) {
                std::cout << m_itemList[i].m_description << '\t'
                          << "$" << m_itemList[i].m_price << '\n';
            }
        }
    }

    //Clear list
    void clear() {
        m_itemList.clear();
        m_itemList.shrink_to_fit();
        m_total = 0;
    }


private:
    double m_total;
    std::vector<RetailItem> m_itemList;
};

////////////////////////////////////////Other functions////////////////////////////////////

void menu() {
    std::cout << "Choose operation from the list:" << '\n';
    std::cout << "0 - Quit" << '\n';
    std::cout << "1 - Buy jacket" << '\n';
    std::cout << "2 - Buy jeans" << '\n';
    std::cout << "3 - Buy shirt" << '\n';
    std::cout << "4 - Pay for shoppings" << '\n';
    std::cout << "5 - Clear shoppings list" << '\n';
}


//////////////////////////////////////////////Main/////////////////////////////////////////
int main() {

    int op = 0;
    enum choose {quit, buy_jacket, buy_jeans, buy_shirt, pay, clear}; 

    RetailItem jacket("Jacket", 12, 59.95);
    RetailItem jeans("Jeans", 40, 34.95);
    RetailItem shirt("Shirt", 20, 24.95);

    CashRegister shoppings_list;

    menu();

    do {
        do {
            std::cout << '\n' << "Choose operation: ";
            std::cin >> op;
            if (op < 0 || op > 5) {
                std::cout << "There is no such operation. Try again: ";
            }
        }
        while (op < 0 || op > 5);

        switch (op) {
            case buy_jacket:
                shoppings_list.buyItem(jacket);
                std::cout << "Jacket added to the list" << '\n';
                break;

            case buy_jeans:
                shoppings_list.buyItem(jeans);
                std::cout << "Jeans added to the list" << '\n';
                break;

            case buy_shirt:
                shoppings_list.buyItem(shirt);
                std::cout << "Shirt added to the list" << '\n';
                break;

            case pay:
                shoppings_list.showItems();
                std::cout << "Total: " << "$" << shoppings_list.getTotal() << '\n';
                break;

            case clear:
                shoppings_list.clear();
                std::cout << "Shoppings list is empty!" << '\n';
                break;

            case quit:
                std::cout << "Done!" << '\n';
                break;

            default:
                break;
        }
    }
    while (op != 0);

    return 0;
}
