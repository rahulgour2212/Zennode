#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Product structure to store product details
struct Product {
    string name;
    double price;
    int quantity;
    bool isGiftWrapped;
};

// Discount structure to store discount details
struct Discount {
    string name;
    double amount;
};

int main() {
    // Product catalog
    Product catalog[] = { {"Product A", 20.0, 0, false},
                          {"Product B", 40.0, 0, false},
                          {"Product C", 50.0, 0, false} };

    // Discount rules
    const double flat_10_discount = 10.0;
    const double bulk_5_discount = 5.0;
    const double bulk_10_discount = 10.0;
    const double tiered_50_discount = 50.0;

    // Cart details
    double subtotal = 0.0;
    double totalDiscount = 0.0;
    double shippingFee = 0.0;
    double giftWrapFee = 0.0;

    // Get quantity and gift wrap information for each product
    for (int i = 0; i < 3; ++i) {
        cout << "Enter the quantity of " << catalog[i].name << ": ";
        cin >> catalog[i].quantity;

        cout << "Is " << catalog[i].name << " wrapped as a gift? (1 for Yes, 0 for No): ";
        cin >> catalog[i].isGiftWrapped;

        subtotal += catalog[i].quantity * catalog[i].price;
    }

    // Apply discounts
    Discount appliedDiscount;
    if (subtotal > 200.0) {
        appliedDiscount = {"flat_10_discount", flat_10_discount};
        totalDiscount = flat_10_discount;
    } else if (catalog[0].quantity > 10 || catalog[1].quantity > 10 || catalog[2].quantity > 10) {
        appliedDiscount = {"bulk_5_discount", bulk_5_discount};
        totalDiscount = bulk_5_discount;
    } else if (catalog[0].quantity + catalog[1].quantity + catalog[2].quantity > 20) {
        appliedDiscount = {"bulk_10_discount", bulk_10_discount};
        totalDiscount = bulk_10_discount;
    } else if (catalog[0].quantity + catalog[1].quantity + catalog[2].quantity > 30
               && catalog[0].quantity > 15) {
        appliedDiscount = {"tiered_50_discount", tiered_50_discount};
        totalDiscount = subtotal * tiered_50_discount / 100.0;
    }

    // Calculate gift wrap fee
    for (int i = 0; i < 3; ++i) {
        if (catalog[i].isGiftWrapped) {
            giftWrapFee += catalog[i].quantity;
        }
    }
    giftWrapFee *= 1.0; // Gift wrap fee per unit is $1

    // Calculate shipping fee
    shippingFee = ceil((catalog[0].quantity + catalog[1].quantity + catalog[2].quantity) / 10.0) * 5.0;

    // Calculate total
    double total = subtotal - totalDiscount + giftWrapFee + shippingFee;

    // Display details
    cout << "\nProduct Details:\n";
    for (int i = 0; i < 3; ++i) {
        cout << catalog[i].name << ": " << catalog[i].quantity << " units - $"
             << catalog[i].quantity * catalog[i].price << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nSubtotal: $" << subtotal << endl;
    cout << "Discount Applied: " << appliedDiscount.name << " - $" << totalDiscount << endl;
    cout << "Shipping Fee: $" << shippingFee << endl;
    cout << "Gift Wrap Fee: $" << giftWrapFee << endl;
    cout << "Total: $" << total << endl;

    return 0;
}
