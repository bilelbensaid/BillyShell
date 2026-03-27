#pragma once


typedef struct {
    char        *nom;
    void        (*handler)(int, char**);
} t_command;


extern void display();
extern void lire(char *f);
extern void echo(char *s);
extern void créerFichier(char *f);
extern void ecrire(char *f, char *s);
extern void man();
extern void executercommande(int argc, char **arg);
extern void execute_extern(char **arg, char *nom);