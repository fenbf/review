#include <iostream>
#include <string>

using namespace std;

string replaceStr(const string &in, const string &what, const string &newStr)
{
	size_t lenWhat = what.length();
	size_t lenNew  = newStr.length();
	if (lenWhat == 0) 
		return in;
	
	size_t pos = in.find(what);
	string temp(in);
	
	while (pos != string::npos)
	{
		if (lenWhat > lenNew)
			temp.erase(pos, lenWhat-lenNew);
		else if (lenWhat < lenNew)
			temp.insert(pos, lenNew-lenWhat, '*');		

		temp.replace(pos, newStr.length(), newStr);
		
		pos = temp.find(what);
	}
	
	return temp;
}

int main(/*int argc, const char **argv*/)
{
	string s("Hello World Again");
	cout << s << endl;
	s = replaceStr(s, "World", "Awsome C++");	
	cout << s << endl;
	s = replaceStr(s, " ", "");
	cout << s << endl;
	
	return 0;
}