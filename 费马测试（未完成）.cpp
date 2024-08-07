#include<iostream>
#include<sstream>
#include<vector>
using namespace std;
string long_to_string(long long n){
	ostringstream write;
	write << n;
	return write.str();
}
int func(string s,long long n) {
	int num = (s[0]-'0') % n;
	for (int i = 1; i < s.size(); i++)
	{
		num = (10 * num + s[i]-'0') % n;
	}
	return num;
}
int main() {
	int p;
	vector <int> a;
	while (cin) {
		cin >> p;
		if (p == 0)
			break;
		else
			a.push_back(p);
	}
	cout << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << func(long_to_string(pow(2, a[i] - 1)), a[i] * a[i]) << endl;
	}
	return 0;
	system("pause");
}