#ifndef __SENtENCE_PROCESSING_H__
#define __SENTENCE_PROCESSING_H__

#include <stdio.h>
#include <string.h>

void removeSpace(char* word){
	char* token = NULL;
	char space[] = " ";
	char temp[100] = "";

	token = strtok(word, space);

	while (token != NULL){
		strcat(temp, token);
		token = strtok(NULL, space);
	}
	strcpy(word, temp);
}

void delete_cal(char* str)
{
	int i;
	int length = strlen(str);

	for (i = 0; i < length; i++)
	{
		if (str[i] == 'C' && str[i + 1] == 'A' && str[i + 2] == 'L'){
			str[i] = 0;
			break;
		}
	}
}
#endif