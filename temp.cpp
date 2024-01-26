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
		Lexer(const std::string &str){
			input = str;
			currentPos_ = 0;
		}
		Token getNextToken() {
			
			skipWhiteSpace();

			if(currentPos_ >= input.size()){
				return {INVALID, ""};
			}

			char current = input[currentPos_];

			if(isalpha(current)){
				return parseKeyword();
			}else if(isdigit(current)){
				std::cout<<"integer\n";
				return parseInteger();
			}else if(isSeparator(current)){
				return parseSeparator();
			}

		}
	private:
		std::string input;
		std::size_t currentPos_;
		
		void skipWhiteSpace(){
			while(currentPos_ < input.size() && isspace(input[currentPos_])){
				currentPos_++;
			}
		}

		bool isSeparator(char ch){
			return ch == ',' || ch == ';' || ch == '(' || ch == ')';
		}

		Token parseKeyword(){
			std::string tokenValue;
			while(currentPos_ < input.size() && isalnum(input[currentPos_])){
				tokenValue += input[currentPos_];
				currentPos_++;
			}
			if(tokenValue.size() == 1 && !isdigit(tokenValue[0])){
				return {CHAR, tokenValue};
			}else if(!isdigit(tokenValue[0])){
				return {KEYWORD, tokenValue};
			}
		}

		Token parseInteger(){
			std::string tokenValue;
			while(currentPos_ < input.size() && isdigit(input[currentPos_])){
				tokenValue += input[currentPos_];
				currentPos_++;
			}
			return {INTEGER, tokenValue};
		}

		Token parseSeparator(){
			std::string tokenValue;
			tokenValue = input[currentPos_];
			currentPos_++;

			return {SEPARATOR, tokenValue};
		}

		/*Token parseChar(){
			std::string tokenValue;
			if(isalpha(input[currentPos_])){
				tokenValue = input[currentPos_];
				currentPos_++;
			}

			return {CHAR, tokenValue};
		}*/


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
