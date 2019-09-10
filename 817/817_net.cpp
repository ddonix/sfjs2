#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;
char str[maxn];
char table[] = { '*','+','-' };
int n, res[maxn];
vector<string> ans;


void cal(int len) {
    stack<int> sta;
    int cnt = 0;
    char tmp[maxn];
    for (int i = 0; i < len; i++) {
        if (res[i] == 3) {
            tmp[i] = str[cnt++];
        }
        else tmp[i] = table[res[i]];
    }
    tmp[len] = '=';
    tmp[len+1] = '\0';
    //printf("%s\n", tmp);

    int a, b;
    char *head = tmp;
    char ch;
    while (true) {
        sscanf(head, "%d%c", &a, &ch);
        if (a != 0 && *head == '0') return;
        sta.push(a);
        if (ch == '=') break;
        head = strchr(head, ch) + 1;
        
        if (ch == '*') {
            while (ch == '*') {
                sscanf(head, "%d%c", &b, &ch);
                if (b!=0 && *head == '0') return;
                head = strchr(head, ch) + 1;
                a = sta.top(); sta.pop();
                a *= b;
                sta.push(a);
            }
        }
        if (ch == '-') sta.push(-1);
        if (ch == '+') sta.push(-2);
        if (ch == '=') break;
    }

    int rres = 0;
    stack<int> ssta;
    while (!sta.empty()) ssta.push(sta.top()), sta.pop();
    while (!ssta.empty() && true) {
        int a = ssta.top(); ssta.pop();
        if (ssta.empty()) {
            rres = a;
            break;
        }

        int flag = ssta.top(); ssta.pop();
        int b = ssta.top(); ssta.pop();
        if (flag == -1) a -= b;
        else a += b;
        ssta.push(a);
    }

    if (rres == 2000) {
        //printf("%s\n", tmp);
        string ss(tmp);
        ans.push_back(ss);
    }
}

void dfs(int len,int pos,int pre) {
    if (pos == n) {
        cal(len);
        return;
    }

    if (pre) {
        for (int i = 0; i < 4; i++) {
            res[len] = i;
            if (i == 3) dfs(len + 1, pos + 1, 1);
            else dfs(len + 1, pos, 0);
        }
    }
    else {
        res[len] = 3;
        dfs(len + 1, pos + 1, 1);
    }
}

void solve() {
    ans.clear();
    dfs(0,0,0);
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int iCase = 1;
    while (~scanf("%s", str) && str[0] != '=') {
        if (strcmp(str, "2000=") == 0) {
            printf("Problem %d\n", iCase++);
            printf("  IMPOSSIBLE\n");
            continue;
        }
        n = strlen(str);
        n--;
        str[n] = 0;
        printf("Problem %d\n",iCase++);
        solve();
        if (ans.size() == 0) {
            printf("  IMPOSSIBLE\n");
        }
        else {
            vector<string>::iterator iter;
            for (iter = ans.begin(); iter != ans.end(); iter++) {
                cout << "  " << *iter << endl;
            }
        }
    }
    return 0;
}
