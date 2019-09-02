#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;
struct book{
    string author;
    int status;
};
map<string, book> books;
vector<string> name;
bool compare(string a, string b){
    if(books[a].author == books[b].author) return a < b;
    else return books[a].author < books[b].author;
}
int main()
{
    string x,z,m;
    book y;
    while(getline(cin,m)){
        if(m == "END") break;
        x = m.substr(0, m.find_last_of("\"")+1);
        y.author = m.substr(m.find_last_of("\"")+1);
        name.push_back(x);
        books[x]= y;
    }
    sort(name.begin(), name.end(), compare);
    for(int i = 0; i < name.size(); i++)
        books[name[i]].status = 1;
    while(cin >> x){
        if(x == "END") break;
        if(x == "BORROW"){
            getchar();
            getline(cin, z);
            books[z].status = 0;
        }
        if(x == "RETURN"){
            getchar();
            getline(cin, z);
            books[z].status = -1;
        }
        if(x == "SHELVE"){
            for(int i = 0; i < name.size(); i++)
                if(books[name[i]].status == -1){
                    int j;
                    for(j = i; j >= 0; --j)
                        if(books[name[j]].status == 1) break;
                    if(j > -1) cout << "Put " << name[i] << " after " << name[j] << endl;
                    else cout << "Put " << name[i] << " first" << endl;
                    books[name[i]].status = 1;
                }
                cout << "END" << endl;
 
        }
    }
    return 0;
}

