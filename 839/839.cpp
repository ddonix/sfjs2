#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool isbanlace(int & w)
{
	int wl, dl, wr, dr;
	bool bl = true, br = true;
	cin>>wl>>dl>>wr>>dr;
	if (!wl)
		bl = isbanlace(wl);
	if (!wr)
		br = isbanlace(wr);
	w = wl + wr;
	return (bl && br && (wl*dl == wr*dr));
}

int main()
{
	int T;
	cin>>T;

	while(T--)
	{
		int w;
		if (isbanlace(w))
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
		if (T)
			cout<<endl;
	}
}
