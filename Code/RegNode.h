#ifndef __REG_NODE_H__
#define __REG_NODE_H__

#include <stdlib.h>

typedef struct _regnode
{
	int judge;
	double num;
} RegNode;

void reg_node_init(RegNode* reg_exp[]);
void reg_node_clear(RegNode* reg_exp[]);
void reg_node_free(RegNode* reg_exp[]);

#endif