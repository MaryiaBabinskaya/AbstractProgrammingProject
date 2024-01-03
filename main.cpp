#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <ctime>

class Product {
public:
    std::string MeasureUnit;
    std::string Name;
    float PricePerUnit;
    float NeedQuantity;
    float DiscountPercentage;

    virtual bool CheckDiscount() = 0;

    Product(std::string name, std::string measureUnit, float pricePerUnit, float needQuantity, float discountPercentage = 0)
            : Name(std::move(name)), MeasureUnit(std::move(measureUnit)), PricePerUnit(pricePerUnit), NeedQuantity(needQuantity), DiscountPercentage(discountPercentage) {}

    virtual ~Product() = default;
};

class MilkProducts : public Product {
private:
    float FatPercentage;
public:
    MilkProducts(std::string name, std::string measureUnit, float pricePerUnit, float needQuantity, float fatPercentage, float discountPercentage = 0)
            : Product(std::move(name), std::move(measureUnit), pricePerUnit, needQuantity, discountPercentage), FatPercentage(fatPercentage) {}

    bool CheckDiscount() override {
        if (ConvertToStringNowDayOfWeek() == "Wednesday" && DiscountPercentage != 0) { //mozna zmienic dzien
            std::cout << "Today, a discount on " << Name << " - " << DiscountPercentage << "%" << std::endl;
            return true;
        }
        else {
            return false;
        }
    }

private:
    static std::string ConvertToStringNowDayOfWeek() {
        std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::tm* currentTm = std::localtime(&currentTime);
        switch (currentTm->tm_wday) {
            case 0: return "Sunday";
            case 1: return "Monday";
            case 2: return "Tuesday";
            case 3: return "Wednesday";
            case 4: return "Thursday";
            case 5: return "Friday";
            case 6: return "Saturday";
            default: return "";
        }
    }
};

class MeatProducts : public Product {
private:
    bool Butchered;
public:
    MeatProducts(std::string name, std::string measureUnit, float pricePerUnit, float needQuantity, bool butchered, float discountPercentage = 0)
            : Product(std::move(name), std::move(measureUnit), pricePerUnit, needQuantity, discountPercentage), Butchered(butchered) {}

    bool CheckDiscount() override {
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        tm* currentTm = std::localtime(&currentTime);
        auto from = std::chrono::system_clock::from_time_t(std::mktime(currentTm));
        auto to = from + std::chrono::hours(2);
        if (now > from && now < to && PricePerUnit > 25 && DiscountPercentage != 0) {
            std::cout << "From " << currentTm->tm_hour << ":00 to " << currentTm->tm_hour + 2 << ":00 discount on " << Name << " - " << DiscountPercentage << "%" << std::endl;
            return true;
        }
        else {
            return false;
        }
    }
};

class VegetablesAndFruits : public Product {
public:
    bool IsWeighted;
    int WeightCode;

    VegetablesAndFruits(std::string name, std::string measureUnit, float pricePerUnit, float needQuantity, int weightCode, float discountPercentage = 0)
            : Product(std::move(name), std::move(measureUnit), pricePerUnit, needQuantity, discountPercentage), WeightCode(weightCode), IsWeighted(false) {}

    bool CheckDiscount() override {
        auto now = std::chrono::system_clock::now();
        auto currentTime = std::chrono::system_clock::to_time_t(now);
        tm* currentTm = std::localtime(&currentTime);

        if (currentTm->tm_mon + 1 == 1 && DiscountPercentage != 0) { //mozna zmienic na inny miesiac(teraz styczen)
            std::cout << "This month, a discount on " << Name << " - " << DiscountPercentage << "%" << std::endl;
            return true;
        }
        else {
            return false;
        }
    }
};

class Customer {
public:
    std::string Name;
    float MoneyBalance;
    float BonusBalance;

    Customer(std::string name, float moneyBalance, float bonusBalance)
            : Name(std::move(name)), MoneyBalance(moneyBalance), BonusBalance(bonusBalance) {}

    template <typename T>
    static void AddToList(std::vector<std::string>& list, T* product) {
        std::string str = product->Name + " " + std::to_string(product->NeedQuantity) + " " + product->MeasureUnit + ".";
        list.push_back(str);
    }

    static void WeighProduct(VegetablesAndFruits* product) {
        product->IsWeighted = true;
        std::cout << "\nThe product has been weighed " << product->Name << " with the code " << product->WeightCode
                  << ". Weight: " << product->NeedQuantity << " kg" << std::endl;
    }

    static void AddToCart(std::vector<Product*>& cart, Product* product) {
        cart.push_back(product);
        std::cout << "Product " << product->Name << " added to the cart." << std::endl;
    }

    template <typename U>
    static void PutOutOfCart(std::vector<U*>& cart) {
        std::cout << "\nThere are not enough funds to pay for groceries. You can post some items." << std::endl;
        int productNum;
        while (true) {
            std::cout << "Enter the number of the product you want to remove." << std::endl;
            for (int i = 0; i < cart.size(); i++) {
                std::cout << i << " - " << cart[i]->Name << std::endl;
            }
            std::string input;
            std::cin >> input;
            bool check = true;
            try {
                productNum = std::stoi(input);
            } catch (std::invalid_argument&) {
                check = false;
            }

            if (productNum < 0 || productNum > cart.size() - 1 || !check) {
                std::cout << "\nThis product is not on the list!" << std::endl;
            } else {
                break;
            }
        }
        std::cout << "Product " << cart[productNum]->Name << " is removed from the cart." << std::endl;
        cart.erase(cart.begin() + productNum);
    }

    float CalcSumOfProducts(std::vector<Product*>& cart) const {
        float sum = 0;
        std::cout << std::endl;
        for (auto & i : cart) {
            if (typeid(*i) == typeid(VegetablesAndFruits)) {
                auto* product = dynamic_cast<VegetablesAndFruits*>(i);
                if (!product->IsWeighted) {
                    std::cout << "Product " << i->Name << " unweighted. Weigh the product." << std::endl;
                    WeighProduct(product);
                }
            }
            float cost;
            float discountedCost;
            cost = i->PricePerUnit * i->NeedQuantity;
            if (i->CheckDiscount()) {
                discountedCost = i->PricePerUnit * i->NeedQuantity * (1 - i->DiscountPercentage / 100);
                std::cout << "Product for payment: " << i->Name << "; amount: " << i->NeedQuantity
                          << " " << i->MeasureUnit << "; cost: " << discountedCost << " zl (no discount: " << cost << " zl)." << std::endl;
            } else {
                std::cout << "Product for payment: " << i->Name << "; amount: " << i->NeedQuantity
                          << " " << i->MeasureUnit << "; cost: " << cost << " zl" << std::endl;
            }
            sum += cost;
        }
        std::cout << "\nTotal amount of purchases: " << sum << " zl" << std::endl;
        std::cout << "Cash: " << MoneyBalance << " zl" << std::endl;
        std::cout << "Bonuses: " << BonusBalance << " zl" << std::endl;
        return sum;
    }

    void Pay(std::vector<Product*>& cart) {
        float sum = CalcSumOfProducts(cart);
        if (MoneyBalance + BonusBalance < sum) {
            while (true) {
                if (MoneyBalance + BonusBalance >= sum) {
                    break;
                }
                PutOutOfCart(cart);
                sum = CalcSumOfProducts(cart);
            }
            if (cart.empty()) {
                std::cout << "\nThere are no items left in the cart. \n" << Name << " left the store." << std::endl;
                exit(0);
            }
        }

        while (true) {
            std::cout << "Enter the payment method. 0 - cash, 1 - bonuses, 2 - bonuses and cash." << std::endl;
            int paymentMethod;
            std::cin >> paymentMethod;

            if (paymentMethod < 0 || paymentMethod > 2 || std::cin.fail()) {
                std::cout << "\nThe payment method is entered incorrectly!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else if (paymentMethod == 0 && MoneyBalance >= sum) {
                MoneyBalance -= sum;
                std::cout << "\nPurchases have been successfully paid for. Payment method: cash." << std::endl;
                return;
            } else if (paymentMethod == 1 && BonusBalance >= sum) {
                BonusBalance -= sum;
                std::cout << "\nPurchases have been successfully paid for. Payment method: bonuses." << std::endl;
                return;
            } else if (paymentMethod == 2 && MoneyBalance + BonusBalance >= sum) {
                while (true) {
                    std::cout << "Enter the number of bonuses to be debited." << std::endl;
                    float bonus;
                    std::cin >> bonus;
                    if (bonus < 0 || bonus > BonusBalance || std::cin.fail() || bonus < sum - MoneyBalance) {
                        std::cout << "\nAn incorrect number of bonuses has been entered." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        sum -= bonus;
                        BonusBalance -= bonus;
                        MoneyBalance -= sum;
                        std::cout << "\nPurchases have been successfully paid for. Payment method: bonuses and cash." << std::endl;
                        return;
                    }
                }
            } else {
                std::cout << "\nInsufficient funds. Choose another payment method." << std::endl;
            }
        }
    }
};

int main() {

    Customer customer("Maria", 100, 50);
    std::vector<std::string> productList;

    std::cout << "Name: " << customer.Name << std::endl;
    std::cout << "Cash: " << customer.MoneyBalance << " zl" << std::endl;
    std::cout << "Bonuses: " << customer.BonusBalance << " zl" << std::endl;
    std::cout << "\nShopping list:" << std::endl;

    MeatProducts meat("Meat", "kg", 30, 4, true, 10);
    MilkProducts milk("Milk", "l", 10, 1, 5, 50);
    MilkProducts curd("Cottage cheese", "pcs", 15, 4, 1);
    VegetablesAndFruits vegetable("Vegetables", "kg", 12, 0.5f, 149, 10);
    VegetablesAndFruits fruit("Fruit", "kg", 8, 1, 504);

    Customer::AddToList(productList, &meat);
    Customer::AddToList(productList, &milk);
    Customer::AddToList(productList, &curd);
    Customer::AddToList(productList, &vegetable);
    Customer::AddToList(productList, &fruit);

    for (const auto& product : productList) {
        std::cout << product << std::endl;
    }

    std::cout << "\n" << customer.Name << " went into the store." << std::endl;

    std::vector<Product*> cart;

    //Customer::WeighProduct(&vegetable); //nie byly na wadze
    Customer::WeighProduct(&fruit);

    Customer::AddToCart(cart, &meat);
    Customer::AddToCart(cart, &milk);
    Customer::AddToCart(cart, &curd);
    Customer::AddToCart(cart, &vegetable);
    Customer::AddToCart(cart, &fruit);

    customer.Pay(cart);

    std::cout << "Cash: " << customer.MoneyBalance << " zl" << std::endl;
    std::cout << "Bonuses: " << customer.BonusBalance << " zl" << std::endl;
    std::cout << "\n" << customer.Name << " left the store." << std::endl;

    return 0;
}