#include <iostream>
#include <string>
#include <string.h>
#include "parser.h"
using std::string;

int main(int argc, char **argv)
{
	try{
		bool IsDown = true;
		char str[300];
		string input = "", composeCentance = "";
		while (true)
		{
			if (IsDown){
				std::cout << "?- ";
			}
			else{
				std::cout << "|  ";
			}

			std::getline(std::cin, input);
			if (input.compare("halt.") == 0){
				break;
			}

			if (input == "."){
				throw string("never get assignment");
			}
			else if (input != ""){
				composeCentance += input;
				IsDown = false;
			}

			strcpy(str, input.c_str());

			while (true)
			{
				//一個句子結束
				if (str[input.size() - 1] == '.'){
					Scanner s(composeCentance);
					Parser p(s);
					p.buildExpression();
					string result;
					if (p.getExpressionTree()->evaluate()){
						result = p.getExpressionTree()->getEvaluateResult() + '.';
					}
					else{
						result = "false.";
					}
					std::cout << result << std::endl;
					composeCentance = "";
					IsDown = true;
					break;
				}
				//代表句子還沒組裝完成
				else if (str[input.size() - 1] == ',' || str[input.size() - 1] == ';'){
					IsDown = false;
					break;
				}
				else if (input == ""){
					break;
				}
			}
		}
	}
	catch (std::string & mes){
		cout << mes << std::endl;
	}
	return 0;
}