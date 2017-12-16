#ifndef __ERROR_CHECKING_H__
#define __ERROR_CHECKING_H__

#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"

int syntax_search(char* word)
{
	Stack sstack;
	int j = 0, i = 0;
	int ncount = 0;
	char symbol = 0, opr = 0;		//simbol=word[i]   opr=word[i+1]
	int length = strlen(word);
	StackInit(&sstack);

	for (i = 0; i < length; i++)
	{
		symbol = word[i];
		if (word[0] == '-'){
			return -1;
		}
		switch (symbol)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			opr = word[i + 1];
			if (opr == '+' || opr == '-' || opr == '*' || opr == '/'){
				return -1;
			}
			break;

		case '(':
		case '[':
			opr = word[i + 1];
			if (opr == '*' || opr == '/'){		//printf("(* or (/   Error!!");
				return -1;
			}

			else if (opr == '+' &&  word[i + 2] == '('){		//printf("(+(  Error!!");
				return -1;
			}

			else if (opr == '-'&&  word[i + 2] == '('){		//printf("(-(   Error!!");
				return -1;
			}

			else if (word[i - 1] > '0' && word[i - 1] < '9'){		//isdigit printf("����(   Error \n");
				return -1;
			}

			SPush(&sstack, symbol);
			break;

		case ')':
			if (word[i + 1] == '('){		//printf("  )(  �ݿ� �ٷο��� �ȵ� ����\n");
				return -1;
			}

			if (!SIsEmpty(&sstack) == 0){		//printf("' ) ' ���� ��ȣ�� �־�� �մϴ�.\n");
				return -1;
			}
			else
			{
				if ((char)SPop(&sstack) != '('){		//printf("���� ��ȣ�� �����մϴ�.\n");
					return -1;
				}
			}

			break;

		case ']':
			if (!SIsEmpty(&sstack) == 0){		//printf("���� ���ȣ�� �־�� �մϴ�.\n");
				return -1;
			}
			else
			{
				if ((char)SPop(&sstack) != '['){		//printf("���� ���ȣ ����\n");
					return -1;
				}
			}
			break;

		default:
			if ((symbol < '0' || symbol > '9') && symbol != '.' && (symbol<'a' || symbol >'z') && symbol != '-'&&symbol != '>')
			{
				return -1;
			}
			ncount++;
			break;
		}
	}
	if (ncount == 0){
		return -1;
	}
	while (!SIsEmpty(&sstack))
	{
		opr = (char)SPop(&sstack);
		if (opr == '(' || opr == '{' || opr == '[' || opr == '+' || opr == '-' || opr == '*' || opr == '/'){			// ������ ������ Ȥ�� ���� ��ȣ�� ���� �� �����ϴ�. 
			return -1;
		}
	}
	return 0;
}

#endif
