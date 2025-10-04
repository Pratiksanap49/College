#include <iostream>
using namespace std;

void calculateratio(int weight[] , int profit[], float ratio[] ,int numberOfItems){

    for(int i=0 ; i<numberOfItems ; i++){
        ratio[i] = (float) profit[i] / weight[i];
        cout<<ratio[i];
        cout<<endl;
    }
}

int main(){
    int numberOfItems  ;
    cout<<"Number of items : ";
    cin>>numberOfItems;
    int weight[numberOfItems] , profit[numberOfItems] ; float ratio[numberOfItems];

    for(int i=0 ; i<numberOfItems ; i++){
        cout<<"Weight of item "<<i+1<<" : ";
        cin>>weight[i];
        cout<<"Profit of item "<<i+1<<" : ";
        cin>>profit[i];
    }

    calculateratio(weight,profit,ratio,numberOfItems);

    return 0;
    
}