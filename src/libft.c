#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

int compterMot(char *s) {
    int n = 0;
    if (s == NULL) return 0;

    while (*s) {
        if (!isspace(*s)) {
            while (*s && !isspace(*s)) s++;
            n++;
        } else {
            s++;
        }
    }
    return n;
}

char **ft_split(char *s) {
    if (s == NULL) return NULL;

    int n_mots = compterMot(s);
    char **tab = malloc(sizeof(char *) * (n_mots + 1));
    if (!tab) return NULL;

    char **p = tab;
    char *q = s;

    while (*q != '\0') {
        if (!isspace(*q)) {
            char *debut_mot = q;
            int len = 0;

            while (*q && !isspace(*q)) {
                len++;
                q++;
            }

            *p = malloc(len + 1);
            strncpy(*p, debut_mot, len);
            (*p)[len] = '\0';
            p++;
        } else {
            q++;
        }
    }

    *p = NULL;
    return tab;
}