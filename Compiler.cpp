#include "Compiler.h"

bool Compiler::judge_num(char i)
{
	if (i == '+' || i == '-' || i == '*' || i == '/' || i == '(' || i == ')') {
		return false;
	}
	else {
		return true;
	}
}

bool Compiler::prior(char i, char c)
{
	if ((i == '*' || i == '/') && (c == '+' || c == '-') || c == '(' || c == NULL) {
		return true;
	}// into stack
	else {
		return false;
	}// out stack
}

int Compiler::calc(int x, int y, char op)
{
	if (op == '+') {
		return y + x ;
	}
	else if (op == '-') {
		return y - x;
	}
	else if (op == '*') {
		return y * x;
	}
	else if (op == '/') {
		return y / x;
	}
	else {
		cout << "Error!!!!" << endl;
		return NULL;
	}
}

void Compiler::in_to_post()
{
	for (auto it = s.begin(); it != s.end(); ++it) {
		char in = *it;
		if (judge_num(in)) {
			postfix.push(in);
		}
		else if (in == '(') {
			oprt.push(in);
		}
		else if (in == ')') {
			while (1) {
				char ops{ NULL };
				if (oprt.length() == 0) {
					break;
				}
				else {
					ops = oprt.pop();
				}
				if (ops != '(') {
					postfix.push(ops);
				}
				else {
					break;
				}
			}
		}
		else {
			char cur{ NULL };
			if (oprt.length() != 0) {
				cur = oprt.top();
			}
			bool cmp = prior(in, cur);
			if (cmp) {
				oprt.push(in);
			}
			else {
				char temp = oprt.pop();
				postfix.push(temp);
				oprt.push(in);
			}
		}
	}
	while (oprt.length() != 0) {
		char temp = oprt.pop();
		postfix.push(temp);
	}
}

void Compiler::calc_post()
{
	auto k = postfix.head;
	while (k != NULL) {
		if (judge_num(k->val)) {
			opnd.push(k->val);
		}
		else {
			int op1 = opnd.pop();
			int op2 = opnd.pop();
			int ans = calc(op1, op2, k->val);
			opnd.push(ans);
		}
	}
}

void Compiler::exit_calc()
{
	char ops = oprt.pop();
	int op1 = opnd.pop();
	int op2 = opnd.pop();
	int ans = calc(op1, op2, ops);
	opnd.push(ans);
}

int Compiler::v_to_int(vector<int> x)
{
	int ans{ 0 };
	int n = x.size();
	for (auto it = x.begin(); it != x.end(); ++it) {
		int in = *it;
		ans += in * pow(10, n - 1);
		--n;
	}
	return ans;
}

int Compiler::make_num(string::iterator &i)
{
	char in = *i;
	vector<int> buff;
	//auto temp = i;
	while (1) {
		buff.push_back(*i - '0');
		if (i == s.end() - 1) {
			break;
		}
		if (!judge_num(*i)) {
			break;
		}
		else {
			if (judge_num(*(i + 1))) {
				++i;
			}
			else {
				break;
			}
		}
	}
	//i = temp;
	return v_to_int(buff);
}

bool Compiler::check_parenthesis()
{
	Stack<char> buff;
	for (auto it = s.begin(); it != s.end(); ++it) {
		char in = *it;
		if (in == '(') {
			buff.push(in);
		}
		else if (in == ')') {
			buff.pop();
		}
	}
	if (buff.length() == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Compiler::check_oprt()
{
	int num_opnd{ 0 }, num_oprt{ 0 };
	for (auto it = s.begin(); it != s.end(); ++it) {
		char in = *it;
		if (judge_num(in)) {
			//make_num(it);
			while (1) {
				if (it == s.end() - 1) {
					break;
				}
				if (!judge_num(*it)) {
					break;
				}
				else {
					if (judge_num(*(it + 1))) {
						++it;
					}
					else {
						break;
					}
				}
			}
			++num_opnd;
		}
		else if (in == '+' || in == '-' || in == '*' || in == '/') {
			++num_oprt;
		}
	}
	if (num_opnd == num_oprt + 1) {
		return true;
	}
	else {
		return false;
	}
}

void Compiler::scan()
{
	/*in_to_post();
	postfix.show();
	calc_post();
	
	cout << opnd.top();*/

	if (!check_parenthesis() || !check_oprt()) {
		cout << "Error!!!!!" << endl;
		return;
	}
	for (auto it = s.begin(); it != s.end(); ++it) {
		char in = *it;
		if (judge_num(in)) {
			opnd.push(make_num(it));
		}
		else if (in == '(') {
			oprt.push(in);
		}
		else if (in == ')') {
			while (1) {
				char ops{ NULL };
				if (oprt.length() == 0) {
					break;
				}
				else {
					ops = oprt.top();
				}
				if (ops != '(') {
					exit_calc();
				}
				else {
					//oprt.pop();
					break;
				}
			}
		}
		else {
			if (oprt.length() == 0) {
				oprt.push(in);
				continue;
			}
			while (oprt.length() != 0) {
				char cur = oprt.top();
				if (cur == '(') {
					//oprt.pop();
					oprt.push(in);
					break;
				}
				bool cmp = prior(in, cur);
				if (cmp) {
					oprt.push(in);
					break;
				}
				else {
					exit_calc();
				}
			}
		}
	}
	while (oprt.length() != 0) {
		if (oprt.top() != '(') {
			exit_calc();
		}
		else {
			oprt.pop();
		}
	}
	cout << opnd.top();
}