#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "RegNode.h"
#include "AdditionalCal.h"
#include "PostCalculator.h"
#include "InfixToPostfix.h"
#include "ErrorChecking.h"
#include "SentenceProcessing.h"

#define SAFE_FREE(a) if(a){free(a); a=NULL;}

void register_exp(char* total_word, RegNode* reg_exp[]);

int main(void)
{
	int length = 0;
	RegNode* reg_exp[26];
	char* postfix = NULL;
	char word[100] = { 0 };
	char total_word[10000];

	reg_node_init(reg_exp);

	while (1)
	{	
		puts("\n---- Scientific Calculator ----\n");
		fputs("End: EXIT\n", stdout);

		memset(total_word, 0, 10000);
		while (1)
		{
			printf("Input : ");
			fgets(word, 100, stdin);

			length = strlen(word);
			word[length-1] = 0;

			removeSpace(word);

			strcat(total_word, word);

			if (strstr(total_word, "CAL")){
				break;
			}
			if (strstr(total_word, "EXIT")){
				reg_node_free(reg_exp);
				return -1;
			}
		}
		delete_cal(total_word);			// CAL부터 뒤에 문자 제거

		if (strstr(total_word, "EXIT")){
			reg_node_free(reg_exp);
			return -1;
		}

		if (syntax_search(total_word) != -1)
		{
			register_exp(total_word, reg_exp);
			additional_cal(total_word, reg_exp);
			postfix = ConvToRPNExp(total_word, reg_exp);
			printf("\n%f \n", EvalRPNExp(postfix, reg_exp));
			SAFE_FREE(postfix);
			reg_node_clear(reg_exp);
		}
		else{
			printf("\nERROR ! \n");
		}
	}
	return 0;
}

void register_exp(char* total_word, RegNode* reg_exp[])
{	
	int temp_loc = 0;
	int length = strlen(total_word);

	for (int i = 0; i < length; i++)
	{
		if (total_word[i] == '>' && total_word[i-1] == '-')
		{
			if (isalpha(total_word[i + 2]) && islower(total_word[i + 2])){
				total_word[i - 1] = 0;
				reg_exp[total_word[i + 2] - 'a']->judge = 1;
				additional_cal(total_word, reg_exp);
				reg_exp[total_word[i + 2] - 'a']->num = EvalRPNExp(ConvToRPNExp(total_word, reg_exp), reg_exp);

				for (int j = temp_loc; j < i + 4; j++){
					total_word[j] = ' ';
				}
				i = i + 3;
				temp_loc = i + 1;
			}
			else {
				printf("\nERROR ! ");
				return;
			}
		}
	}
}