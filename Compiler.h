#pragma once
#ifndef COMPILER_H
#define COMPILER_H
#include "Stack.h"

class Compiler {
	public:
		Compiler(string x) : s(x) {}
		~Compiler() {}
		void scan();
	private:
		void in_to_post();
		void calc_post();
		bool judge_num(char i);
		bool prior(char i, char c);
		void exit_calc();
		int v_to_int(vector<int> x);
		int make_num(string::iterator &i);
		int calc(int x, int y, char op);
		bool check_parenthesis();
		bool check_oprt();
		Stack<int> opnd;
		Stack<char> oprt;
		Stack<char> postfix;
		string s;
};

#endif
