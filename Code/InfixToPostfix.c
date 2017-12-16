#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "RegNode.h"
#include "ListBaseStack.h"

void case_bloack(Stack* stack, char* convExp, int *idx)
{
	char temp;

	while (1)
	{
		temp = (char)SPop(stack); // ���ÿ��� �ϳ��� ����

		if (temp != '(') // ���� ��ȣ�� �ƴ϶��
		{
			convExp[(*idx)++] = temp; // ���� �迭�� ����
			convExp[(*idx)++] = ' ';
		}
		else{
			break;
		}
	}
}
void case_operator1(Stack* stack, char* convExp, int* idx, char tok, char* word, int num, int limit)
{
	char temp;
	
	if (num > 0 && word[num - 1] == '(')
	{
		if (word[num+1] == '(' && word[num + 2] == '-'){
			convExp[(*idx)++] = tok;
			return;
		}
		for (int s = num + 1; s < limit; s++){
			if ((!isdigit(word[s]) && word[s] != ')' && word[s] != '.')){
				if (word[s] == '[' && (isalpha(word[s + 1]) && islower(word[s + 1])) && word[s + 2] == ']'){
					convExp[(*idx)++] = tok;
					return;
				}
				printf("\nERROR ! ");
				return;
			}
			if (word[s] == ')'){
				convExp[(*idx)++] = tok;
				return;
			}
		}	
		convExp[(*idx)++] = tok;
	}
	else
	{
		while (1)
		{
			if (stack->head == NULL)
			{
				break;
			}
			temp = (char)SPop(stack); // ���ÿ��� �ϳ��� ����

			if (temp == '+' || temp == '-' || temp == '*' || temp == '/') // ���� ��ȣ���
			{
				convExp[(*idx)++] = temp;	// ���� �迭�� ����
				convExp[(*idx)++] = ' ';
			}
			else
			{
				SPush(stack, temp); // ���� ��ȣ�� �ƴϸ� �ٽ� ���ÿ� ����
				break;
			}
		}
		SPush(stack, tok); // ���� ���� ��ȣ ����
	}
}
void case_operator2(Stack* stack, char* convExp, int *idx, char tok)
{
	char temp;

	while (1)
	{
		if (stack->head == NULL)
		{
			break;
		}
		temp = (char)SPop(stack); // ���ÿ��� �ϳ��� ����

		if (temp == '*' || temp == '/') // �켱������ ���� ���� ��ȣ���
		{
			convExp[(*idx)++] = temp;	// ���� �迭�� ����
			convExp[(*idx)++] = ' ';
		}
		else
		{
			SPush(stack, temp); // ���� ��ȣ�� �ƴϸ� �ٽ� ���ÿ� ����
			break;
		}
	}
	SPush(stack, tok); // ���� ���� ��ȣ ����
}
void case_digit(Stack* stack, char* word, char* convExp, int *idx, char tok, int num, int limit)
{
	convExp[(*idx)++] = tok; // ���ڸ� ���� �迭�� ����

	// ���� ������ ����
	if (num < limit && !isdigit(word[num + 1]))
	{
		if (word[num + 1] != '.'){
			convExp[((*idx)++)] = ' '; // ���� ����
		}
	}
}
void case_dot(Stack* stack, char* word, char* convExp, int *idx, char tok, int num, int limit)
{
	convExp[(*idx)++] = tok;
}

char* ConvToRPNExp(char* word, RegNode* reg_exp[])
{
	Stack stack;
	int wordLen = strlen(word);
	char* convExp = (char*)malloc(wordLen * 2 + 1);

	int i, idx = 0;
	char tok = 0, popOp = 0;
	int count = 1;

	memset(convExp, 0, sizeof(char)*wordLen + 1);
	StackInit(&stack);

	for (i = 0; i < wordLen; i++)
	{	
		tok = word[i];
		if (tok == '.')
		{
			case_dot(&stack, word, convExp, &idx, tok, i, wordLen);
			continue;
		}
		else if (isalpha(tok) && islower(tok)){
			if (word[i - 1] == '[' && word[i + 1] == ']')
			{
				if (i-3 >= 0 && (word[i - 2] == '+' || word[i-2] == '-') && word[i-3] == '('){
					convExp[idx - 1] = ' ';
					if (word[i - 2] == '-'){
						reg_exp[tok - 'a']->num = reg_exp[tok - 'a']->num * (-1);
					}
				}
				convExp[idx++] = tok;
				convExp[idx++] = ' ';
				continue;
			}
			else {
				printf("\nERROR ! ");
				break;
			}
		}
		else if (isdigit(tok)){
			case_digit(&stack, word, convExp, &idx, tok, i, wordLen);
			continue;
		}
		else
		{
			switch (tok)
			{
			case'(':
				SPush(&stack, tok);
				break;
			case')':
				case_bloack(&stack, convExp, &idx);
				break;
			case'+':  case'-':
				case_operator1(&stack, convExp, &idx, tok, word, i, wordLen);
				break;
			case'*':  case'/':
				case_operator2(&stack, convExp, &idx, tok);
				break;
			default:
				continue;
			}
		}
	}
	while (!SIsEmpty(&stack)){
		convExp[idx++] = (char)SPop(&stack);
		convExp[idx++] = ' ';
	}
	convExp[idx] = 0;
	return convExp;
}