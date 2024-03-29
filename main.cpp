#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

enum TokenType{
	CHAR,
	INTEGER,
	KEYWORD,
	SEPARATOR,
	INVALID
};

struct Token{
	TokenType type;
	std::string value;
};

class Lexer{
	public:
		Lexer(const std::string &inputString){
			input = inputString;
			currentPos = 0;
		}
		Token getNextToken() {
			
			skipWhiteSpace();

			if(currentPos >= input.size()){
				return {INVALID, ""};
			}

			char current = input[currentPos];

			if(isalpha(current)){
				return parseKeyword();
			}else if(isdigit(current)){
				return parseInteger();
			}else if(isSeparator(current)){
				return parseSeparator();
			}

		}
	private:
		std::string input;
		std::size_t currentPos;
		
		void skipWhiteSpace(){
			while(currentPos < input.size() && isspace(input[currentPos])){
				currentPos++;
			}
		}

		bool isSeparator(char ch){
			return ch == ',' || ch == ';' || ch == '(' || ch == ')';
		}

		Token parseKeyword(){
			std::string tokenValue;
			while(currentPos < input.size() && isalnum(input[currentPos])){
				tokenValue += input[currentPos];
				currentPos++;
			}
			if(tokenValue.size() == 1 && !isdigit(tokenValue[0])){
				return {CHAR, tokenValue};
			}else if(!isdigit(tokenValue[0])){
				return {KEYWORD, tokenValue};
			}
		}

		Token parseInteger(){
			std::string tokenValue;
			while(currentPos < input.size() && isdigit(input[currentPos])){
				tokenValue += input[currentPos];
				currentPos++;
			}
			return {INTEGER, tokenValue};
		}

		Token parseSeparator(){
			std::string tokenValue;
			tokenValue = input[currentPos];
			currentPos++;

			return {SEPARATOR, tokenValue};
		}
};

int main(){
	std::ifstream file("test.mlg");

	if(!file.is_open()){
		std::cerr << "Error opening file...\n";
		return 1;
	}

	std::ostringstream content;
	content << file.rdbuf();
	file.close();

	Lexer lexer(content.str());

	Token token;
	do{
		token = lexer.getNextToken();
		if(token.type != INVALID){
			std::cout << "Type: " << token.type << ", Value: "<< token.value << '\n';
		}

	}while(token.type != INVALID);
	return 0;
}
