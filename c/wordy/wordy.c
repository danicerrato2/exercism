#include "wordy.h"

#define QUESTION_INIT "What is "

int ReadNumber(const char *question, int *i, char *operation, int *result) {
	int numberLen = 0, ret = 1;
	char *number;

	while (!isspace(question[*i + numberLen]) && question[*i + numberLen] != '?') {
		numberLen++;
	}
	number = malloc((numberLen + 1) * sizeof(char));
	strncpy(number, question + *i, numberLen);

	switch (*operation) {
		case 0:
			*result = atoi(number);
			break;
		case '+':
			*result += atoi(number);
			break;
		case '-':
			*result -= atoi(number);
			break;
		case '*':
			*result *= atoi(number);
			break;
		case '/':
			*result /= atoi(number);
			break;
		default:
			ret = -1;
			break;
	}
	
	*operation = 0;
	*i += numberLen;
	
	return ret;
}

int ReadOperation(const char *question, int *i, char *operation) {
	if (*operation != 0)
		return -1;

	if (strncmp(question + *i, "plus", strlen("plus")) == 0) {
		*operation = '+';
		*i += strlen("plus");
	} else if (strncmp(question + *i, "minus", strlen("minus")) == 0) {
		*operation = '-';
		*i += strlen("minus");
	} else if (strncmp(question + *i, "multiplied by", strlen("multiplied by")) == 0) {
		*operation = '*';
		*i += strlen("multiplied by");
	} else if (strncmp(question + *i, "divided by", strlen("divided by")) == 0) {
		*operation = '/';
		*i += strlen("divided by");
	} else {
		return -1;
	}
	return 0;
}

bool answer(const char *question, int *result) {
	int i, ret = 0;
	char operation = 0;

	i = strlen(QUESTION_INIT);
	if (strncmp(question, QUESTION_INIT, i) != 0) {
		return false;
	}

	while (ret >= 0 && question[i] != '?') {
		if ((isdigit(question[i]) || question[i] == '-') && ret == 0) {
			ret = ReadNumber(question, &i, &operation, result);
		} else if (isalpha(question[i]) && ret == 1) {
			ret = ReadOperation(question, &i, &operation);
		} else if (isspace(question[i])) {
			i++;
		} else {
			ret = -1;
		}
	}
	return ret == 1;
}
