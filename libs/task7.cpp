#include <iostream>
using namespace std;

bool F(int arr[],int st,int end,int K)
{
    int mid=(st+end)/2;
    int sum=arr[mid]+arr[mid+1];
    if(sum==K){
        return true;
    }
    if((mid==st&&sum<K)||(mid==end&&sum>K)){
        return false;
    }
    if(sum>K){
        return F(arr,st,mid,K);
    }
    else{
        return F(arr,mid,end,K);
    }
    
}

int main() {
    int arr1[]={6,8,9,10,15};
    int K1=17;
    int arr2[]={5,12,20,25,30};
    int K2=38;

    F(arr1,0,4,K1)?cout<<"True\n":cout<<"False\n";
    F(arr2,0,4,K2)?cout<<"True\n":cout<<"False\n";
    return 0;
}