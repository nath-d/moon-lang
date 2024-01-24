#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum{
	SEMI,
	OPEN_PAREN,
	CLOSE_PAREN,
} TypeSeparator;

typedef enum{
	INT,
} TypeLiteral;

typedef enum{
	EXIT,
} TypeKeyword;

typedef struct{
	TypeKeyword type;
}TokenKeyword;

typedef struct{
	TypeSeparator type;
}TokenSeparator;

typedef struct{
	TypeLiteral type;
	int value;
}TokenLiteral;

void generate_number(char current, FILE *file){
	while(isdigit(current) && current != EOF){
		if(!isdigit(current)){
			return;
		}
		printf("%c\n", current);
		current = fgetc(file);
	}
}

void lexer(FILE *file){
	char current  = fgetc(file);

	while(current != EOF){
		if(current == ';'){
			printf("FOUND SEMICOLON\n");
		}else if(current == '('){
			printf("FOUND OPEN PARENTHESIS\n");
		}else if(current == ')'){
			printf("FOUND CLOSED PARENTHESIS\n");
		}else if(isdigit(current)){
			generate_number(current, file);			
		}else if(isalpha(current)){
			printf("FOUND CHARACTER %c\n",current);
		}
		current = fgetc(file);
	}
}

int main(){
	FILE *file;
	file = fopen("test.mlg", "r");
	lexer(file);
}
