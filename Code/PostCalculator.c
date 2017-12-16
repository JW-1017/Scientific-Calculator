#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "RegNode.h"
#include "ListBaseStack.h"

double EvalRPNExp(char* word, RegNode* reg_exp[])
{
	Stack stack;
	int wordLen = strlen(word);
	int i, count = 0;
	double value = 0;
	char tok;
	double op1, op2;

	StackInit(&stack);

	for (i = 0; i < wordLen; i++)
	{
		tok = word[i];

		if (isalpha(tok)){																			// �������Ͱ� ������ �ȵǾ� �ִµ� ���� ���� 
			if (reg_exp[tok - 'a']->judge == 0){
				printf("\nERROR ! ");
				return -1;
			}
			value = reg_exp[tok - 'a']->num;
			SPush(&stack, value);
		}

		else if ((tok == '+' || tok == '-') && (word[i + 1] == '-') && isdigit(word[i + 2]))		// �������� �Ѿ�� --10 ���� ó���ϱ� ����
		{
			if (tok == '+'){
				word[i + 1] = '-';
			}
			else if (tok == '-'){
				word[i + 1] = '+';
			}
		}

		else if(isdigit(tok) || ((tok == '+' || tok == '-') && isdigit(word[i + 1])))				// (+1)���� ó��
		{
			while (word[i + count] != ' ')
			{
				count++;
			}
			value = atof(&word[i]);
			i += count;
			count = 0;
			SPush(&stack, value);
		}
		else
		{
			if (tok != ' ')
			{
				op2 = SPop(&stack);
				op1 = SPop(&stack);

				switch (tok)
				{
				case'+':
					SPush(&stack, op1 + op2);
					break;
				case'-':
					SPush(&stack, op1 - op2);
					break;
				case'*':
					SPush(&stack, op1 * op2);
					break;
				case'/':
					if (op2 == 0){
						printf("\nERROR ! ");
						return -1;
					}
					SPush(&stack, op1 / op2);
					break;
				}
			}
		}
	}
	if (SSize(&stack) > 1){
		printf("\nERROR ! ");
		return -1;
	}

	return SPop(&stack);
}