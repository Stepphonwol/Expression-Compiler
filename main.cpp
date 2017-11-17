#include "Compiler.h"

int main(void)
{
	string i;
	while (1) {
		cout << "Input the expression and press 1 to exit the program: " << endl;
		getline(cin, i);
		//cin.get();
		if (i == "1") {
			break;
		}
		Compiler c(i);
		c.scan();
	}

	return 0;
}