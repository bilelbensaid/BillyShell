#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <ctype.h>
#include <string.h>


int main() {
    char *input;
    display();
    while(1) {
        input = readline("\033[34mBillyShell$>");
        if (!input)
            break;
        if (*input=='\0') {
            free(input);
            continue;
        }
        char **s = ft_split(input);
        executercommande(compterMot(input), s);
        add_history(input);
        free(input);
        int i = 0;
        while (s[i]) free(s[i++]);
        free(s);


        printf("\n");

    }
}