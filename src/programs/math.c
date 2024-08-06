// Math expression lexer and parser

#include "../libc/stdint.h"
#include "../kernel/system.h"
#include "../libc/stdio.h"
#include "../libc/ctype.h"

#define BUFFER_SIZE 256

typedef enum
{
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_END
} TokenType;

typedef struct
{
	TokenType type;
	double value;
} Token;

typedef struct
{
	const char *text;
	size_t pos;
	Token current_token;
} Lexer;

void lexer_init(Lexer *lexer, const char *text)
{
	lexer->text = text;
	lexer->pos = 0;
	lexer->current_token.type = TOKEN_END;
	lexer->current_token.value = 0;
}

void lexer_advance(Lexer *lexer)
{
	lexer->pos++;
}

char lexer_peek(const Lexer *lexer)
{
	return lexer->text[lexer->pos];
}

bool lexer_is_at_end(const Lexer *lexer)
{
	return lexer->text[lexer->pos] == '\0';
}

Token lexer_get_next_token(Lexer *lexer)
{
	while (!lexer_is_at_end(lexer))
	{
		char current_char = lexer_peek(lexer);

		if (isspace(current_char)) {
			lexer_advance(lexer);
			continue;
		}

		if (isdigit(current_char)) {
			double value = 0;
			while (isdigit(current_char))
			{
				value = value * 10 + (current_char - '0');
				lexer_advance(lexer);
				current_char = lexer_peek(lexer);
			}
				if (current_char == '.')
				{
					lexer_advance(lexer);
					double decimal_place = 0.1;
					while (isdigit(lexer_peek(lexer))) 
					{
						value += decimal_place * (lexer_peek(lexer)-'0');
						decimal_place *= 0.1;
						lexer_advance(lexer);
					}
				}
				lexer->current_token.type = TOKEN_NUMBER;
				lexer->current_token.value = value;
				//printf("NUMBER %f\n", value);
				return lexer->current_token;
		}

		if (current_char == '+')
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_PLUS;
			printf("PLUS\n");
			return lexer->current_token;
		}

		if (current_char == '-') 
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_MINUS;
			printf("MINUS\n");
			return lexer->current_token;
		}

		if (current_char == '*')
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_MULTIPLY;
			printf("MULTIPLY\n");
			return lexer->current_token;
		}

		if (current_char == '/')
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_DIVIDE;
			printf("DIVIDE\n");
			return lexer->current_token;
		}

		if (current_char == '(')
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_LPAREN;
			printf("LPAREN\n");
			return lexer->current_token;
		}

		if (current_char == ')')
		{
			lexer_advance(lexer);
			lexer->current_token.type = TOKEN_RPAREN;
			printf("RPAREN\n");
			return lexer->current_token;
		}

		printf("Unknown character %c\n", current_char);
		//shell_install();
	}
	
	lexer->current_token.type = TOKEN_END;
	printf("END\n");
	return lexer->current_token;
}

typedef struct
{
	Lexer lexer;
	Token current_token;
} Parser;

void parser_init(Parser *parser, const char *text)
{
	lexer_init(&parser->lexer, text);
	parser->current_token = lexer_get_next_token(&parser->lexer);
}

void parser_eat(Parser *parser, TokenType type)
{
	if (parser->current_token.type == type)
	{
		parser->current_token = lexer_get_next_token(&parser->lexer);
	} else {
		printf("Unexpected token %d\n", parser->current_token.type);
		//shell_install();
	}
}

double parser_factor(Parser *parser);
double parser_term(Parser *parser);
double parser_expression(Parser *parser);

double parser_factor(Parser *parser)
{
	Token token = parser->current_token;
	if (token.type == TOKEN_NUMBER)
	{
		parser_eat(parser, TOKEN_NUMBER);
		//printf("Factor: %f\n", token.value);
		return token.value;
	} else if (token.type == TOKEN_LPAREN) {
		parser_eat(parser, TOKEN_LPAREN);
		double result = parser_expression(parser);
		parser_eat(parser, TOKEN_RPAREN);
		//printf("Factor (expression): %f\n", result);
		return result;
	} else {
		printf("Unexpected token in factor %d\n", token.type);
		//shell_install();
	}
	return -1;
}

double parser_term(Parser *parser)
{
	double result = parser_factor(parser);
	//printf("Initial term: %f\n", result);

	while (parser->current_token.type == TOKEN_MULTIPLY || parser->current_token.type == TOKEN_DIVIDE)
	{
		Token token = parser->current_token;
		if (token.type == TOKEN_MULTIPLY) 
		{
			parser_eat(parser, TOKEN_MULTIPLY);
			result *= parser_factor(parser);
			//printf("Term after multiply: %f\n", result);
		} else if (token.type == TOKEN_DIVIDE) {
			parser_eat(parser, TOKEN_DIVIDE);
			result /= parser_factor(parser);
			//printf("Term after divide: %f\n", result);
		}
	}
	return result;
}

double parser_expression(Parser *parser)
{
	double result = parser_term(parser);
	//printf("Initial expression: %f\n", result);

	while (parser->current_token.type == TOKEN_PLUS || parser->current_token.type == TOKEN_MINUS) 
	{
		Token token = parser->current_token;
		if (token.type == TOKEN_PLUS)
		{
			parser_eat(parser, TOKEN_PLUS);
			result += parser_term(parser);
			//printf("Expression after plus: %f\n", result);
		} else if (token.type == TOKEN_MINUS) {
			parser_eat(parser, TOKEN_MINUS);
			result -= parser_term(parser);
			//printf("Expression after minus: %f\n", result);
		}
	}
	return result;
}

double parse(const char* text)
{
	Parser parser;
	parser_init(&parser, text);
	double result = parser_expression(&parser);
	//printf("Final result: %f\n", result);
	return result;
}

void program_math()
{
	char input_buffer[BUFFER_SIZE];
	puts("Expression? ");
	get_input(input_buffer, BUFFER_SIZE);
	printf("Input: %s\n", input_buffer);
	double result = parse(input_buffer);
	printf("\n%f\n", result);
}
