#pragma once





//Constantes de couleurs
#define ROUGE   "\033[31m"
#define VERT    "\033[32m"
#define JAUNE   "\033[33m"
#define BLEU    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
#define GRAS    "\033[1m"

typedef struct {
    char        *nom;
    void        (*handler)(int, char**);
} t_command;

// Fonctions principales
extern void display();
extern void executercommande(int argc, char **arg);
extern void execute_extern(char **arg, char *nom);

// Commandes fichiers
extern void lire(char *f);
extern void mkfile(char *f);
extern void ecrire(char *f, char *s);
extern void rmfile(char *f);

// Commandes dossiers
extern void mkdir2(char *f);
extern void rmdir2(char *d);
extern void cd2(char *f);
extern void pwd();

// Commandes utilitaires
extern void echo(char *s);
extern void man();
extern void chmod2(char *name, char *perm);

// Wrappers commandes
extern void cmd_lire(int argc, char *arg[]);
extern void cmd_file(int argc, char **arg);
extern void cmd_ecrire(int argc, char **arg);
extern void cmd_rmfile(int argc, char **arg);
extern void cmd_echo(int argc, char **arg);
extern void cmd_man(int argc, char **arg);
extern void cmd_ls(int argc, char **arg);
extern void cmd_cd(int argc, char **arg);
extern void cmd_pwd(int argc, char **arg);
extern void cmd_tree(int argc, char **arg);
extern void cmd_curl(int argc, char **arg);
extern void cmd_gcc(int argc, char **arg);
extern void cmd_mkdir(int argc, char **arg);
extern void cmd_rmdir(int argc, char **arg);
extern void cmd_chmod2(int argc, char **arg);

// Tableau de commandes
extern t_command tableau_command[];