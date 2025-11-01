#include <iostream>
#include <vector>

using namespace std;

//calculate max profit
int knapsack(int capacity, int numberofitems, vector<int> &weights, vector<int> &profits)
{
    vector<vector<int>> DP(numberofitems + 1, vector<int>(capacity + 1, 0));

    for (int i = 0; i <= numberofitems; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
            {
                DP[i][j] = 0;
            }
            else if (weights[i-1] <= j)
            {
                DP[i][j] = max(DP[i - 1][j], profits[i - 1] + DP[i - 1][j - weights[i - 1]]);
            }
            else
            {
                DP[i][j] = DP[i - 1][j];
            }
        }
    }

    cout << "DP Table:";
    for (int i = 0; i <= numberofitems; i++) {
        for (int j = 0; j <= capacity; j++) {
            cout << DP[i][j] << "\t";
        }
        cout << endl;
    }

    return DP[numberofitems][capacity];
}

int main()
{
    int numberofitems, capacity;
    cout << "Enter number of items : ";
    cin >> numberofitems;
    cout << "Enter capacity : ";
    cin >> capacity;

    vector<int> weights(numberofitems), profits(numberofitems);

    for (int i = 0; i < numberofitems; i++)
    {
        cout << "Enter weight of item " << i + 1 <<": "  ;
        cin >> weights[i];
        cout << "Enter profit of item " << i + 1 <<": "  ;
        cin >> profits[i];
    }

    int maxprofit = knapsack(capacity, numberofitems, weights, profits);
    cout<<endl;

    cout<<"Max Profit :"<<maxprofit;
}
