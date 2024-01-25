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
		Lexer(const std::string &input): input_(input), currentPos_(0){}
		Token getNextToken() {
			
			skipWhiteSpace();

			if(currentPos_ >= input_.size()){
				return {INVALID, ""};
			}

			char current = input_[currentPos_];

			if(isalpha(current)){
				return parseKeyword();
			}else if(isdigit(current)){
				parseInteger();
			}else if(isSeparator(current)){
				return parseSeparator();
			}else{
				return parseChar();
			}
			currentPos_++;
		}
	private:
		std::string input_;
		size_t currentPos_;
		
		void skipWhiteSpace(){
			while(currentPos_ < input_.size() && isspace(input_[currentPos_])){
				currentPos_++;
			}
		}

		bool isSeparator(char ch){
			return ch == ',' || ch == ';' || ch == '(' || ch == ')';
		}

		Token parseKeyword(){
			std::string tokenValue;
			while(currentPos_ < input_.size() && isalnum(input_[currentPos_])){
				tokenValue += input_[currentPos_];
				currentPos_++;
			}
			return {KEYWORD, tokenValue};
		}

		Token parseInteger(){
			std::string tokenValue;
			while(currentPos_ < input_.size() && isdigit(input_[currentPos_])){
				tokenValue += input_[currentPos_]-'0';
				currentPos_++;
			}
			return {INTEGER, tokenValue};
		}

		Token parseSeparator(){
			std::string tokenValue;
			tokenValue = input_[currentPos_];
			currentPos_++;

			return {SEPARATOR, tokenValue};
		}

		Token parseChar(){
			std::string tokenValue;
			tokenValue = input_[currentPos_];
			currentPos_++;

			return {CHAR, tokenValue};
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
