#include <ctype.h>
#include <string.h>

#include "libft.h"

#include <stdlib.h>

/*Compte le nombre de mot dans la string*/
int compterMot(char *s) {
    int n=0;
    if (s==NULL || *s=='\n') return 0;
    while (*s) {
        if (!isspace(*s)) {

            while (*s && !isspace(*s)) s++;
            n++;
        }else {
            s++;
        }

    }
    return n;
}

/*Retourne un tabeau de string*/
char **ft_split(char *s) {
    int n_mots = compterMot(s); // Une petite fonction à créer
    char **tab = malloc(sizeof(char *) * (n_mots + 1));
    int i = 0;
    while (*s != '\0') {
        if (!isspace(*s)) { // On a trouvé un mot
            int len = 0;
            while (s[len] && s[len] != ' ') len++; // Mesure du mot

            // "Ajout" de l'élément au tableau :
            tab[i] = malloc(sizeof(char) * (len + 1));
            strncpy(tab[i], s, len);
            tab[i][len] = '\0'; // Fin de chaîne

            i++;
            s += len; // On saute le mot qu'on vient de copier
        } else {
            s++; // On saute l'espace
        }
    }
    tab[i] = NULL;// On ferme le tableau avec NULL pour execve
    return tab;
}