#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct knode
{
    int levelnumber;
    int profit;
    int weight;
    float bound;

    bool operator >(const knode& p) {
        if (p.bound < this->bound)
            return true;
        return false;
    }
    bool operator <(const knode& p) {
        if (p.bound > this->bound)
            return true;
        return false;
    }

    knode operator =(const knode& p) {
        this->bound = p.bound;
        this->levelnumber = p.levelnumber;
        this->profit = p.profit;
        this->weight = p.weight;
        return *this;
    }
};

knode H[500];
int Hsize = -1;

int parent(int i)
{

    return (i - 1) / 2;
}

int leftChild(int i)
{

    return ((2 * i) + 1);
}

int rightChild(int i)
{

    return ((2 * i) + 2);
}

void shiftUp(int i)
{
    while (i > 0 && H[parent(i)] < H[i]) {
        swap(H[parent(i)], H[i]);
        i = parent(i);
    }
}

void shiftDown(int i)
{
    int maxIndex = i;
    int l = leftChild(i);

    if (l <= Hsize && H[l] > H[maxIndex]) {
        maxIndex = l;
    }
    int r = rightChild(i);

    if (r <= Hsize && H[r] > H[maxIndex]) {
        maxIndex = r;
    }

    if (i != maxIndex) {
        swap(H[i], H[maxIndex]);
        shiftDown(maxIndex);
    }
}

void insert(knode p)
{
    Hsize = Hsize + 1;
    H[Hsize] = p;
    shiftUp(Hsize);
}

knode extractMax()
{
    knode result = H[0];
    H[0] = H[Hsize];
    Hsize = Hsize - 1;
    shiftDown(0);
    return result;
}

void changePriority(int i, knode p)
{
    knode oldp = H[i];
    H[i] = p;

    if (p > oldp) {
        shiftUp(i);
    }
    else {
        shiftDown(i);
    }
}

knode getMax()
{

    return H[0];
}

void remove(int i)
{
    knode tm;
    tm = getMax();
    tm.bound += 1;
    H[i] = tm;
    shiftUp(i);
    extractMax();
}
//////////////////////////////////////////////




struct knapsack_details
{
    int n;
    vector<int> w;
    vector<int> p;
    int W;
    float maxprofit = 0;
    vector<int> bestset;
    vector<int> include;
};

float bound(knode& u, knapsack_details& l) {
    int i, k;
    int totweight;
    float result;
    if (u.weight >= l.W)
        return 0;
    else {
        result = u.profit;
        i = u.levelnumber + 1;
        totweight = u.weight;
        while (i <= l.n && totweight + l.w[i] <= l.W) {
            totweight = totweight + l.w[i];
            result = result + l.p[i];
            i++;
        }
        k = i;
        if (k <= l.n) 
            result = result + (l.W - totweight) * l.p[k] / l.w[k]; 
        return result;
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

int cnt = 0;
void printknode(knode& x, knapsack_details& i) {
    cout << "node number : " << x.levelnumber << "  and is the " << cnt++ << "th  and node profit : " << x.profit << "  and bound is : " << x.bound << "  and wieght is : " << x.weight << "  Max profit is : " << i.maxprofit << endl;
}

void knapsack(knapsack_details& i, knode& j)
{
    
    i.maxprofit = 0;
    j.bound = bound(j, i);
    insert(j);
    while (Hsize >= 0) {
        knode x = extractMax();
        printknode(x, i);
        if (x.bound > i.maxprofit) {
            
            j.levelnumber = x.levelnumber + 1;
            j.weight = x.weight + i.w[j.levelnumber];
            j.profit = x.profit + i.p[j.levelnumber];
            i.include[j.levelnumber] = 1;
            if (j.weight <= i.W && j.profit > i.maxprofit) {
                i.maxprofit = j.profit;
                j.bound = bound(j, i);
                i.bestset = i.include;
            }
            if (j.bound > i.maxprofit)
                insert(j);
            j.weight = x.weight;
            j.profit = x.profit;
            i.include[j.levelnumber] = 0;
            j.bound = bound(j, i);
            if (j.bound > i.maxprofit)
                insert(j);
        }
    }

}

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
    //for (int l = 1; l <= d.n; l++)
    //    cout << "item number " << l << " existence in best set: " << (d.bestset[l] ? "yes" : "no") << endl;
    cout << "max profit= " << d.maxprofit << endl;
    return 0;
}

