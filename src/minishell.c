//
// Created by bilel on 25/03/2026.
//
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>



// COMMANDES
void lire(char *f) {
    FILE *pfile = fopen(f, "r");
    if (pfile==NULL) {
        perror(ROUGE"Fichier introuvable"RESET);
        return;
    }
    char ligne[255];
    while (fgets(ligne, sizeof(ligne), pfile)) {
        printf("%s ", ligne);
    }
    printf("\n");
    fclose(pfile);
}
void man() {
    printf(GRAS BLEU"==============================================================\n"RESET
           GRAS BLEU"            📘 MANUEL DES COMMANDES - BILLYSHELL\n"RESET
           GRAS BLEU"==============================================================\n\n"RESET

    GRAS MAGENTA"--- GESTION DES FICHIERS ---\n"RESET
    GRAS JAUNE"lire <fichier>\n"RESET
    "  Affiche le contenu d'un fichier\n\n"

    GRAS JAUNE"mkfile <fichier1> <fichier2> ...\n"RESET
    "  Cree un ou plusieurs fichiers\n\n"

    GRAS JAUNE"ecrire <fichier> <texte>\n"RESET
    "  Ecrit du texte dans un fichier (ecrase le contenu existant)\n\n"

    GRAS JAUNE"rmfile <fichier1> <fichier2> ...\n"RESET
    "  Supprime un ou plusieurs fichiers\n\n"

    GRAS JAUNE"chmod <fichier/dossier> <mode_octal>\n"RESET
    "  Modifie les permissions (ex: chmod fichier 777)\n\n"

    GRAS MAGENTA"--- GESTION DES DOSSIERS ---\n"RESET
    GRAS JAUNE"mkdir <dossier>\n"RESET
    "  Cree un nouveau repertoire\n\n"

    GRAS JAUNE"rmdir <dossier>\n"RESET
    "  Supprime un repertoire (le repertoire doit etre vide)\n\n"

    GRAS JAUNE"cd <dossier>\n"RESET
    "  Change le repertoire courant\n\n"

    GRAS JAUNE"pwd\n"RESET
    "  Affiche le chemin absolu du repertoire courant\n\n"

    GRAS JAUNE"ls [options]\n"RESET
    "  Liste les fichiers (ex: ls -la)\n\n"

    GRAS MAGENTA"--- COMMANDES SYSTEME & EXTERNES ---\n"RESET
    GRAS JAUNE"echo <texte> [> <fichier>]\n"RESET
    "  Affiche le texte ou le redirige vers un fichier avec '>'\n\n"

    GRAS JAUNE"tree, curl, gcc\n"RESET
    "  Appelle directement les utilitaires systeme correspondants\n\n"

    GRAS ROUGE"Remarques:\n"RESET
    "- Les permissions (chmod) attendent une valeur octale (ex: 644, 755).\n"
    "- Les fichiers/dossiers inexistants provoquent une erreur systeme.\n");
}

void mkfile(char *f) {
    FILE *pfile = fopen(f, "w+");
    if (pfile==NULL) {
        perror(ROUGE"Fichier introuvable"RESET);
        return;
    }
    fclose(pfile);
}

void mkdir2(char *f) {
    if (mkdir(f, 0777)<0) {
        printf(ROUGE"Impossible de créer le fichier"RESET);
    }else {
        printf(VERT"Le dossier %s a bien été créé"RESET, f);
    }
}

void rmdir2(char *d) {
    if (rmdir(d)<0) {
        perror(ROUGE"Suppression impossible ");
        return;
    }else {
        printf(VERT"Le dossier %s a bien été supprimé\n"RESET, d);
    }
}

void ecrire(char *f, char *s) {
    FILE *pfile = fopen(f, "w+");
    if (pfile==NULL) {
        perror(ROUGE"Fichier introuvable"RESET);
        return;
    }
    fprintf(pfile, "%s", s);
    fclose(pfile);
}
void echo(char *s) {
    printf("%s",s);
}


void rmfile(char *f) {
    if (remove(f)) {
        perror(ROUGE"Fichier introuvable"RESET);
        return;
    }else {
        printf(VERT"Le fichier %s a bien été supprimé\n"RESET, f);
    }
}


void cd2(char *f) {
    DIR *pd = opendir(f);
    if (pd==NULL) {
        perror(ROUGE"Dossier introuvable"RESET);
        return;
    }
    chdir(f);
    closedir(pd);
}


void pwd() {
    char buffer[1024];
    getcwd (buffer, sizeof(buffer));
    printf (CYAN"Vous êtes dans ce répertoire: %s\n"RESET,  buffer);
}

void execute_extern(char **arg, char *nom) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(nom, arg);
        exit(1);
    }else if (pid>0)
        waitpid(pid, NULL, 0);
}

void chmod2(char *name, char *perm) {
    if (chmod(name, strtol(perm,NULL, 8)) == -1) {
        perror(ROUGE"Erreur lors de la modification des permissions"RESET);
    }
}

//WRAPPER
void display() {
    printf(GRAS BLEU);
    printf("==============================================================================\n");
    printf("        BIENVENUE DANS L'INTERPRÉTEUR DE COMMANDE BILLY SHELL\n");
    printf("==============================================================================\n");
    printf(RESET);
}

void cmd_lire(int argc, char *arg[]) {
    if (strcmp(*arg, "lire") == 0) {
        if (argc!=2) {
            printf(JAUNE"Usage : lire <nom du fichier> "RESET);
            return;
        }else{
            lire(*(arg+1));
        }
    }
}


void cmd_file(int argc, char **arg) {
    if (strcmp(*arg, "mkfile")==0) {
        if (argc<2) {
            printf(JAUNE"Usage : mkfile <nom du fichier> "RESET);
            return;
        }else {
            arg++;
            while (*arg) {
                mkfile(*arg);
                arg++;
            }

        }
    }
}


void cmd_ecrire(int argc, char **arg) {
    if (argc < 3) {
        printf(JAUNE"Usage : ecrire <nom du fichier> <chaine de caractères>\n"RESET);
        return;
    }
    if (arg) {
        arg++;
        char *name = *arg; // nom du fichier
        arg++;

        char buffer[1024] = "";

        while (*arg) {
            snprintf(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer),"%s ",*arg);
            arg++;
        }
        ecrire(name, buffer);
    }
}


void cmd_rmfile(int argc, char **arg) {
    if (argc==1) {
        printf(JAUNE"Usage : rmfile <nom du fichier> "RESET);
        return;
    }
    arg++;
    while (*arg) {
        rmfile(*arg);
        arg++;
    }
}


void cmd_echo(int argc, char **arg) {
    if (argc<2) {
        printf(JAUNE"Usage : echo <chaine de caractères> "RESET);
        return;
    }else {
        arg++;
        char buffer[1024]="";
        while (*arg) {
            if (strcmp(*arg, ">") == 0) {
                if (!*++arg) {
                    printf(ROUGE"Redirection impossible => Usage : echo <chaine de caractères> > <nom du fichier> "RESET);
                    return;
                }else {
                    ecrire(*arg, buffer);
                }
                return;
            }

            snprintf(buffer + strlen(buffer),sizeof(buffer) - strlen(buffer),"%s ",*arg);
            arg++;
        }
        echo(buffer);
    }

}

void cmd_man(int argc, char **arg) {
    man();
}

void cmd_ls(int argc, char **arg) {
    execute_extern(arg, "ls");
}

void cmd_cd(int argc, char **arg) {

        cd2(*(arg+1));

}

void cmd_pwd(int argc, char **arg) {
    pwd();
}

void cmd_tree(int argc, char **arg) {
    execute_extern(arg, "tree");
}

void cmd_curl(int argc, char **arg) {
    execute_extern(arg, "curl");
}
void cmd_gcc(int argc, char **arg) {
    execute_extern(arg, "gcc");
}

void cmd_mkdir(int argc, char **arg) {
    if (argc<2) {
        printf(JAUNE"Usage : mkdir <nom du fichier> "RESET);
        return;
    }else {
        mkdir2(*(arg+1));
    }

}

void cmd_rmdir(int argc, char **arg) {
    if (argc<2) {
        printf(JAUNE"Usage : rmdir <nom du fichier> "RESET);
        return;
    }else {
        rmdir2(*(arg+1));
    }
}

void cmd_chmod2(int argc, char **arg) {
    if (argc<3) {
        printf(JAUNE"Usage : chmod <nom du fichier> <mode> (Mettre le mode en nombre pour un dossier) "RESET);
        return;
    }
        chmod2(*(arg+1), *(arg+2));
        printf(VERT"La permission de %s a été modifiée"RESET, *(arg+1));

}

//EXECUTION
t_command tableau_command[] = {
    { "lire",   cmd_lire   },
   { "mkfile",   cmd_file   },
    {"mkdir", cmd_mkdir},
    {"rmdir", cmd_rmdir},
   { "ecrire", cmd_ecrire },
   { "echo",   cmd_echo   },
   { "rmfile", cmd_rmfile },
   { "man",    cmd_man    },
    {"ls", cmd_ls},
    {"cd", cmd_cd},
    {"pwd", cmd_pwd},
{"tree", cmd_tree},
    {"curl", cmd_curl},
    {"gcc", cmd_gcc},
    {"chmod", cmd_chmod2},
   { NULL,     NULL       },
};

void executercommande(int argc, char *arg[]){
        t_command *p;
        p = tableau_command;
        while (p->nom) {
            if (strcmp(*arg, p->nom)==0) {
                p->handler(argc, arg);
                return;
            }
            p++;
        }

            printf(ROUGE"Commande inconnue\n"RESET);

    }