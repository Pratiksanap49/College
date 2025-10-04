#include <iostream>
#include <stdlib.h>
using namespace std;

struct Item {
    int weight;
    int profit;
    float ratio;
};

void calculateratio(Item items[], int numberOfItems) {
    for (int i = 0; i < numberOfItems; i++) {
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }
}

void sortratio(Item items[], int numberOfItems) {
    for (int i = 0; i < numberOfItems - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < numberOfItems; ++j) {
            if (items[j].ratio < items[min_idx].ratio) {
                min_idx = j;
            }
        }
        swap(items[i], items[min_idx]);
    }

    for (int i = 0; i < numberOfItems; i++) {
        cout << items[i].ratio << " ";
    }
    cout << endl;
}

float calculatemaxprofit(Item items[], int numberOfItems, int capacity) {
    float maxprofit = 0;
    for (int i = 0; i < numberOfItems; i++) {
        if (capacity > 0) {
            if (capacity >= items[i].weight) {
                capacity -= items[i].weight;
                maxprofit += items[i].profit;
            } else {
                maxprofit += ((float)capacity / items[i].weight) * items[i].profit;
                capacity = 0;
            }
        } else {
            break;
        }
    }
    return maxprofit;
}

int main() {
    cout << "hii" << endl;
    int capacity;
    int numberOfItems;
    cout << "Number of items : ";
    cin >> numberOfItems;

    cout << "Enter capacity : ";
    cin >> capacity;

    Item items[numberOfItems];

    for (int i = 0; i < numberOfItems; i++) {
        cout << "Weight of item " << i + 1 << " : ";
        cin >> items[i].weight;
        cout << "Profit of item " << i + 1 << " : ";
        cin >> items[i].profit;
    }

    calculateratio(items, numberOfItems);
    sortratio(items, numberOfItems);
    float maxprofit = calculatemaxprofit(items, numberOfItems, capacity);

    cout << "Maximum Profit = " << maxprofit << endl;
}
