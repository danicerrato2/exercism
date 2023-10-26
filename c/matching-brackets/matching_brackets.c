#include "matching_brackets.h"

bool is_paired(const char *input)
{
    int input_len = 0, stack_top = 0;

    if (!input)
        return false;
    
    while (input[input_len] != 0)
        input_len++;

    char stack[input_len];

    for (int i = 0; i < input_len; i++){
        switch (input[i]){
            case '(':
            case '{':
            case '[':
                stack[stack_top++] = input[i];
                break;
            case ')':
                if (stack[stack_top - 1] == '(')
                    stack_top--;
                else
                    return false;
                break;
            case '}':
                if (stack[stack_top - 1] == '{')
                    stack_top--;
                else
                    return false;
                break;
            case ']':
                if (stack[stack_top - 1] == '[')
                    stack_top--;
                else 
                    return false;
                break;
            default:
                continue;
        }
    }

    return stack_top == 0;
}