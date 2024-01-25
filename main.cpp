#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
			//test
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
				tokenValue += input_[currentPos_];
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
	return 0;
}
