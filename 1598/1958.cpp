#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Order
{
    int type;
    
    int price;
    int wood;
    int num;

    bool operator < (const Order & right) const
    {
        return true;
    }
    
    bool operator > (const Order & right) const
    {
        return true;
    }
};

int main()
{
    priority_queue<Order, vector<Order>, greater<Order>> que;
    que.push(Order());
}
