#include <stdlib.h>
#include "RegNode.h"

#define SAFE_FREE(a) if(a){free(a); a=NULL;}

void reg_node_init(RegNode* reg_exp[])
{
	for (int i = 0; i < 26; i++){
		reg_exp[i] = (RegNode*)malloc(sizeof(RegNode));
		reg_exp[i]->judge = 0;
		reg_exp[i]->num = 0.0;
	}
}
void reg_node_clear(RegNode* reg_exp[])
{
	for (int i = 0; i < 26; i++){
		reg_exp[i]->judge = 0;
		reg_exp[i]->num = 0.0;
	}
}
void reg_node_free(RegNode* reg_exp[])
{
	for (int i = 0; i < 26; i++){
		SAFE_FREE(reg_exp[i]);
	}
}