#include <iostream>
#include <vector>

using namespace std;

//DFS knapsack:

struct knode
{
    int levelnumber;
    int profit;
    int weight;
    knode() {

    }

    knode(int i, int j, int k)
        :levelnumber(i), profit(j), weight(k) {}
};

struct knapsack_details
{
    int n;
    vector<int> w;
    vector<int> p;
    int W;
    float maxprofit = 0;
    vector<int> bestset;
    vector<int> include;
    int numbest;
    knapsack_details() {}

};

bool promising(knode i, knapsack_details l)
{
    int j, k;
    float bound;
    int totweight;
    if (i.weight >= l.W)
        return false;
    else
    {
        j = i.levelnumber + 1;
        bound = i.profit;
        totweight = i.weight;
        while (j <= l.n && totweight + l.w[j] <= l.W)
        {
            totweight = totweight + l.w[j];
            bound = bound + l.p[j];
            j++;
        }
        k = j;
        if (k <= l.n)
            bound = bound + (l.W - totweight) * l.p[k] / l.w[k];
        return bound > l.maxprofit;
    }
}

void knapsack_data_input(knapsack_details& j)
{
    cout << "enter the number of items: ";
    cin >> j.n;
    j.w.resize(j.n + 1);
    j.p.resize(j.n + 1);
    j.bestset.resize(j.n + 1);
    j.include.resize(j.n + 1);
    for (int i = 1; i <= j.n; i++)
    {
        cout << "enter number " << i << " item weight: ";
        cin >> j.w[i];
        cout << "enter number " << i << " item price: ";
        cin >> j.p[i];
    }
    cout << "enter the weight limit: ";
    cin >> j.W;
}

void knapsack(knapsack_details& i, knode& j)
{
    if (j.weight <= i.W && j.profit > i.maxprofit)
    {
        i.maxprofit = j.profit;
        i.numbest = j.levelnumber;
        i.bestset = i.include;
    }
    if (promising(j, i))
    {
        int num = j.levelnumber + 1;
        int pr = i.p[num], we = i.w[num];

        j.levelnumber = num;
        i.include[num] = 1;
        j.profit += pr;
        j.weight += we;
        knapsack(i, j);
        i.include[num] = 0;
        j.profit -= pr;
        j.weight -= we;
        knapsack(i, j);
        j.levelnumber--;
    }
}

/*/
int main()
{
    knapsack_details d;
    cout << "for notes example enter 1 else 0 :" << endl;
    int x;
    cin >> x;
    if(x){
        d.n = 4;
        d.W = 16;
        d.include.resize(5);
        d.bestset.resize(5);
        d.w.resize(5);
        d.p.resize(5);
        d.w[1] = 2, d.w[2] = 5, d.w[3] = 10, d.w[4] = 5;
        d.p[1] = 40, d.p[2] = 30, d.p[3] = 50, d.p[4] = 10;
    }
    else {
        knapsack_data_input(d);
    }
    knode j{ 0, 0, 0 };
    knapsack(d, j);
    for (int l = 1; l <= d.n; l++)
        cout << "item number " << l << " existence in best set: " << (d.bestset[l] ? "yes" : "no") << endl;
    cout << "max profit= " << d.maxprofit << endl;
    return 0;
}*/