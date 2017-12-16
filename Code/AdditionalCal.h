#ifndef __ADDITIONAL_CAL_H__
#define __ADDITIONAL_CAL_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "RegNode.h"
#include "PostCalculator.h"
#include "InfixToPostfix.h"

// #define RAD ((3.141592)/(180))

void additional_cal(char* total_word, RegNode* reg_exp[])
{
	char temp_double[100];
	memset(temp_double, '0', 100);
	char temp_word[100] = { 0 };

	double value = 0.0;
	int i = 0, j = 0, tempLen = 0;

	int temp = 0, first_pos = 0, last_pos = 0;
	char tok = 0;
	int num = 1;
	int length = strlen(total_word);

	for (i = 0; i < length; i++)
	{
		tok = total_word[i];
		num = 1;
		memset(temp_word, '\0', 100);

		if ((tok == 's' && total_word[i + 1] == 'i' && total_word[i + 2] == 'n') || (tok == 'c' && total_word[i + 1] == 'o' && total_word[i + 2] == 's')
			|| (tok == 'e' && total_word[i + 1] == 'x' && total_word[i + 2] == 'p') || (tok == 'l' && total_word[i + 1] == 'o' && total_word[i + 2] == 'g'))
		{
			first_pos = i;

			if (total_word[i + 3] == '(')
			{
				while (num != 0)
				{
					if (total_word[i + 4] == '('){
						num++;
					}
					else if (total_word[i + 4] == ')'){
						num--;
					}
					strncat(temp_word, &total_word[i + 4], 1);
					i++;
				}

				i += 3;
				last_pos = i;
				tempLen = strlen(temp_word);
				temp_word[tempLen - 1] = 0;

				additional_cal(temp_word, reg_exp);
				value = EvalRPNExp(ConvToRPNExp(temp_word, reg_exp), reg_exp);
			}
			if (tok == 's'){
				//value = sin(value * RAD);
				value = sin(value);
			}
			else if (tok == 'c'){
				//value = cos(value * RAD);
				value = cos(value);
			}
			else if (tok == 'e'){
				value = exp(value);
			}
			else if (tok == 'l'){
				if (value <= 0){
					printf("\nERROR ! ");
					return;
				}
				value = log(value);
			}
			sprintf(temp_double, "%f", value);
			temp_double[strlen(temp_double)] = '0';

			temp = first_pos;
			
			if (value < 0)
			{
				total_word[first_pos++] = '(';
				for (j = 0; j < last_pos - temp; j++)
				{
					total_word[first_pos++] = temp_double[j];
				}
				total_word[--first_pos] = ')';
			}
			else {
				for (j = 0; j < last_pos - temp + 1; j++)
				{
					total_word[first_pos++] = temp_double[j];
				}
			}
		}
	}
}
#endif