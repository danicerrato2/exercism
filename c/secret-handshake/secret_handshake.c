#include "secret_handshake.h"

char *all_actions[] = {"", "jump", "close your eyes", "double blink", "wink"}; 

const char **commands(size_t number)
{
    char **actions = 0;
    int binary[5] = {0, 0, 0, 0, 0}, num_actions = 0;
    
    if (number == 0 || number > 31)
        return (const char **)calloc(1, sizeof(char *));

    for (size_t mult2, i = 5; i > 0; i--){
        mult2 = 1 << (i - 1);
        if (mult2 <= number){
            number -= mult2;
            binary[5 - i] = 1;
            if (i != 5)
                num_actions++;
        }
    }   

    if (num_actions == 0 && binary[0] == 1)
        return (const char **)calloc(1, sizeof(char *));
    
    actions = (char **)malloc(num_actions * sizeof(char *));
    if (!actions)
        return (const char **)calloc(1, sizeof(char *));
    
    if (binary[0] == 0){
        for (size_t i = 4, j = 0; i > 0; i--)
            if (binary[i] == 1)
                actions[j++] = all_actions[i];
    }
    else {
        for (size_t i = 1, j = 0; i < 5; i++)
            if (binary[i] == 1)
                actions[j++] = all_actions[i];
    }

    return (const char **)actions;
}