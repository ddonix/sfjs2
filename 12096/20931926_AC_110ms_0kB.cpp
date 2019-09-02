#include <cstdio>
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x.begin())
using namespace std;
//例题5-5

typedef set<int> Set;
map<Set, int> IDCache;
vector<Set> SetCache;

int getID(Set s) {
    if (IDCache.count(s)) return IDCache[s];
    SetCache.push_back(s);
    return IDCache[s] = SetCache.size() - 1;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        stack<int> s;
        int n;
        scanf("%d", &n);
        char order[10];
        while (n--) {
            scanf("%s", &order);
            char ord = order[0];
            if (ord == 'P') s.push(getID(Set()));
            else if (ord == 'D') s.push(s.top());
            else {
                Set x1 = SetCache[s.top()]; s.pop();
                Set x2 = SetCache[s.top()]; s.pop();
                Set x;
                if (ord == 'U') set_union(ALL(x1), ALL(x2), INS(x));
                else if (ord == 'I') set_intersection(ALL(x1), ALL(x2), INS(x));
                else if (ord == 'A') {x = x2; x.insert(getID(x1));}
                s.push(getID(x));
            }
            printf("%d\n", SetCache[s.top()].size());
        }
        printf("***\n");
    }
    return 0;
}