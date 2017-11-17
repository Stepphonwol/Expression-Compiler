#include "Compiler.h"

int main(void)
{
	string i;
	cout << "Input the expression : " << endl;
	getline(cin, i);
	//cin.get();
	Compiler c(i);
	c.scan();

	return 0;
}