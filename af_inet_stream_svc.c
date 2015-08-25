/**
 * \file af_inet_stream_svc.c
 * \brief Serveur qui va recevoir des requetes du client et lui renvoyer les donnees demandees 
 * \author Dzik Timothee
 * \version finale
 * \date 06/02/2015
 *
 * Jeu Question/Reponse MCS3 Dzik Timothee Rafrafi Soukaina
 *
 */
#include "cst_in.h"
#define PORT 60666

char answer[40] = "";
char meilleurScore[40] = "";
char questionRandom[500] = "";


/**
 * \fn void myProfile (const char * pseudo)
 * \brief Permet de renseigner l'utilisateur sur son pseudo/partiegagnee/perdues/score
 *
 * \author Dzik Timothee
 * \param pseudo pseudo de l'utilisateur
 *
 * \return
 */
void myProfile(char* pseudo){
    char ligne[40]="";
    char *token = NULL;
    char *score, *username;
    FILE* fichier = NULL;
    fichier = fopen("joueurs.txt", "r");
    printf("pseudo : %s\n", pseudo);
    if (fichier != NULL) {
        while(fgets(ligne, 40, fichier) != NULL){
                if(strstr(ligne, pseudo)  != NULL) {
                    printf("----%s\n", ligne);
                    strcat(answer, ligne); 
                }
        } 
        fclose(fichier);
    } else {
        printf("Erreur dans la lecture\n");
    }
    
}

/**
 * \fn void question_Random()
 * \brief Permet de renseigner l'utilisateur sur son partiegagnee/perdues/score
 * \author Dzik Timothee
 * \return
 */
void question_Random(){
    char ligne[300];
    char buffer[100];
    FILE* fichier = fopen("question.txt", "r");
    if (fichier != NULL) {
        int aleatoire = rand() % 10;
        int cpt = 1; 
        while(cpt < aleatoire) {
            fgets(ligne, 300, fichier);
            cpt++;
            
        }
        strcpy(questionRandom, ligne);
        fclose(fichier);        
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
        
    }
}

/**
 * \fn void creationProfile (const char * pseudo)
 * \brief Permet de creer un profile
 *
 * \param pseudo pseudo du nouvel utilisateur
 * \author Dzik Timothee
 * \return
 */
void creationProfile(char* pseudo){
    char buffer[100];
    FILE* fichier = NULL;
    fichier = fopen("joueurs.txt", "a+");
        if (fichier != NULL)
            {
                    // On peut lire et écrire dans le fichier
        printf("Creation d'un nouveau profil \n");
                
                
                sprintf(buffer, "%s|0|0|0\n", pseudo);
                fputs(buffer, fichier);
                fclose(fichier);
        printf("Félicitation vous êtes enregistré !\n");
            }
        else
            {
                    // On affiche un message d'erreur si on veut
                    printf("Impossible d'ouvrir le fichier joueurs.txt");
            }
}

/**
 * \fn int incrementePerdu (const char pseudo[])
 * \brief permet de mettre a jour la base de donnees situees sur le serveur lorsqu'un utilisateur se trompe 
 *
 * \param pseudo pseudo du player
 * \author Dzik Timothee
 *
 * \return
 */
int incrementePerdu(char pseudo[]) {
    FILE* fileIn = fopen("joueurs.txt", "r+");
    FILE* fileOut = fopen("joueurs.tmp", "w+");
    char ligne[40];
    char* username;
    int perdu, gagne;
    char outputLines[40] = "";

    if (fileIn != NULL) {
        while (fgets(ligne, 40, fileIn)) {
            strcpy(outputLines, "");
            username = strtok(ligne, "|");
            gagne = atoi(strtok(NULL, "|"));
            perdu = atoi(strtok(NULL, "|"));

            if (strcmp(username, pseudo) == 0) {
                perdu++;
            }
            fprintf(fileOut, "%s|%d|%d\n", username, gagne, perdu);
        }
        if (rename("joueurs.tmp", "joueurs.txt") != 0) {
            printf("Erreur pendant le rename\n");
        }
        fclose(fileIn);
        fclose(fileOut);
        return 1;
    } else {
        printf("Erreur dans l'ouverture du fichier de donnees\n");
        exit(0);
    }
    return 0;
}

/**
 * \fn int incrementeGagne (const char pseudo[])
 * \brief permet de mettre a jour la base de donnees situees sur le serveur lorsqu'un utilisateur repond correctement 
 *
 * \param pseudo pseudo du player
 *
 * \return
 */
int incrementeGagne(char pseudo[]) {
    FILE* fileIn = fopen("joueurs.txt", "r+");
    FILE* fileOut = fopen("joueurs.tmp", "w+");
    char ligne[40];
    char* username;
    int perdu, gagne;
    char outputLines[40] = "";

    if (fileIn != NULL) {
        while (fgets(ligne, 40, fileIn)) {
            strcpy(outputLines, "");
            username = strtok(ligne, "|");
            gagne = atoi(strtok(NULL, "|"));
            perdu = atoi(strtok(NULL, "|"));

            if (strcmp(username, pseudo) == 0) {
                gagne++;
            }
            fprintf(fileOut, "%s|%d|%d\n", username, gagne, perdu);
        }
        if (rename("joueurs.tmp", "joueurs.txt") != 0) {
            printf("Erreur pendant le rename\n");
        }
        fclose(fileIn);
        fclose(fileOut);
        return 1;
    } else {
        printf("Erreur dans l'ouverture du fichier de donnees\n");
        exit(0);
    }
    return 0;
}

/**
 * \fn void bestscore()
 * \brief renvoie le BestScore de la forme pseudo|sonscore
 *
 *return
 */
void bestscore(){
    char ligne[40];
    char *token, *pseudo, usernameBestScore[40]="";
    char *g;
    char *p;
    int nbligne = 0;
    char score[40];
    int scr=0;
    int perdu=0;
    int ga=0;
    int nbelement=0;
    int maxscore=0;

    FILE* fichier = NULL;
    fichier = fopen("joueurs.txt", "r");

    while(fgets(ligne, 40, fichier) != NULL){

        pseudo = strtok(ligne,"|");  
        token = strtok(NULL,"|");                   // token contient la deuxième partie de la ligne : parties gagnées 
        ga = atoi(token);                           // Le nombre de parties gagnées : conversion en int
        token = strtok(NULL,"|");                   // token contient la troisième partie de la ligne : parties perdues       
        perdu = atoi(token);                        // Le nombre de parties perdues : convertion en int
        if(ga - perdu >= 0) {
            scr = ga - perdu;   
        } else {
            scr = 0;
        } 
        if (scr > maxscore) {
            maxscore = scr;
            strcpy(usernameBestScore, pseudo);
        }
    }

    fclose(fichier);
    sprintf(score, "%d", maxscore);
    strcat(meilleurScore, usernameBestScore);
    strcat(meilleurScore, "|");
    strcat(meilleurScore, score);
    
}

/**
 * \fn char* pseudo_existant (const char* pseudo)
 * \brief verifie si le client donne appartien a la base de donnee situee sur le serveur
 *
 *\return oui si le pseudo existe| Pseudo inexistant si le pseudo existe deja
 */
char* pseudo_existant(char* pseudo){
    char ligne[100] ;
    FILE* fichier = NULL;
    char *token;
    
    fichier = fopen("joueurs.txt", "r");
    if (fichier != NULL)
    {
        //vérification de l'existance de pseudo dans le fichier joueurs.txt
        while(fgets(ligne, 80, fichier) != NULL)
        {
            if(strstr(ligne , pseudo)  != NULL )
            {
                printf("%s\n",pseudo); // affiche la ligne d'enregistrement user
                token = strtok(pseudo,"|");
                fclose(fichier);
                return "oui";
            }
        }
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Erreur de lecture du fichier d'enregistrement \n");
        return "Pseudo inexistant";
    }
    return "";
}


/**
 * \fn int main ()
 * \brief main , il receptionne les requetes client, les identifie et appel les bonnes fonctions 
 *
 *\return 0
 */
int main(){ 
    int s_svc;
    int s_echClt;
    int cltlen;
    char question[100], *message, *token;
    
    
    struct sockaddr_in moi, clt; //Declatation
    char Buff[50];
    printf("c");
    //creation socket
    CHECK(s_svc=socket(AF_INET, SOCK_STREAM, 0), "Err creation socket");
    printf("Socket cree");
    //preparation de l'adressage
    moi.sin_family=AF_INET;
    moi.sin_port = htons(PORT);
    moi.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&moi.sin_zero, 0, 8);
    printf("addressage cree");
    //association addr_socket
    CHECK(bind(s_svc, (struct sockaddr *)&moi, sizeof(moi)), "Err bind");
    CHECK(listen(s_svc, 5), "Erreur listen");
    printf("association DONE");
    
    while(1)
    {
        
        cltlen=sizeof(clt);
        CHECK(s_echClt=accept(s_svc, (struct sockaddr *)&clt, (socklen_t*)&cltlen), "Err accept");
        CHECK(read(s_echClt, Buff, MAXBUFF), "Err read");

       /*
        if (strcmp(Buff, "1") == 0) {
            CHECK(write(s_echClt, "tu m'as envoye 1", 25), "Err write");
        }
        */
        token = strtok(Buff,"|");

        if (strcmp(token, "identification") == 0) {
            token = strtok(NULL, "|");
            message = pseudo_existant(token);
            CHECK(write(s_echClt, message, strlen(message)+1), "Err write");

        }
        if (strcmp(token, "score") == 0) {
            token = strtok(NULL, "|");
            myProfile(token);
            printf("%s\n", answer);
            CHECK(write(s_echClt, answer, strlen(answer)+1), "Err write");
            answer[0] = '\0';
        }
        
        

        if (strcmp(token, "create") == 0) {
            token = strtok(NULL, "|");
            printf("%s\n", token);
            creationProfile(token);
            CHECK(write(s_echClt, "ok", 3), "Err write");
        }
        
        if (strcmp(token, "bestScore") == 0) {
            bestscore();
            printf("%s\n", meilleurScore);
            CHECK(write(s_echClt, meilleurScore, strlen(meilleurScore)+1), "Err write");
            meilleurScore[0] = '\0';
        }

        if (strcmp(token, "question") == 0) {
            question_Random();
            CHECK(write(s_echClt, questionRandom, strlen(questionRandom)+1), "Err write");
            questionRandom[0] = '\0';
        }
        if (strcmp(token, "win") == 0) {
            token = strtok(NULL, "|");
            incrementeGagne(token);
            CHECK(write(s_echClt, "Mise a jour faite", 18), "Err write");
        }
        if (strcmp(token, "loose") == 0) {
            token = strtok(NULL, "|");
            incrementePerdu(token);
            CHECK(write(s_echClt, "Mise a jour faite", 18), "Err write");
        }

    }
    return 0;

}


