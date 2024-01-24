#include <stdio.h>
#include <stdlib.h>

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

int main(){
	FILE *file;
	file = fopen("test.mlg", "r");
	char current = fgetc(file);
	while(current != EOF){
		printf("%c", current);
		current = fgetc(file);
	}

}
