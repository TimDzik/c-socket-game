/**
 * \file af_inet_stream_clt.c
 * \brief Client, qui gere le menu principal du jeu de Question/reponse en communiquant avec le serveur
 * \brief Client, send and receive request from the server
 * \author Dzik Timothee
 * \final version 
 *
 *
 */

#include "cst_in.h"
#define MSG "Mon pseudo :jfjfjkd"
#define SOCKET_CLT "/tmp/SRI Centrale Lille"
#define PORT 60666

char pseudo[50]="";


 /**
 * \fn void creation_message(char* message)
 * \brief Function which allow user to send a request to the server
 *
 * \param char* message 
 * \author Dzik Timothee
 *
 * \return Buff server response
 */  
char* creation_message(char* message){
    int s_clt;
    int svclen;
    char *Buff;
    struct sockaddr_in svc;

    CHECK(s_clt=socket(AF_INET, SOCK_STREAM, 0), "Erreur socket");
    
    //bind facultatif
    //moi.sin_family=AF_INET;
    //CHECK(bind(s_clt, (struct sockaddr *)&moi, sizeof(moi)), "Err bind");
    //Preparation de l'adressage du serveur
    svc.sin_family=AF_INET;
    svc.sin_port = htons(PORT);
    svc.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&svc.sin_zero, 0, 8);
    svclen=sizeof(svc);
    //CHECK(sendto(s_clt, MSG, strlen(MSG)+1, 0, (struct sockaddr *)&svc, svclen), "Erreur d'envoi");
    //CHECK(recvfrom(s_clt, Buff, MAXBUFF, 0, (struct sockaddr *)&svc, &svclen), "Erreur de reception");
    
    CHECK(connect(s_clt, (struct sockaddr *)&svc, svclen), "Err connect");  
    //printf("connecte\n");  
    CHECK(write(s_clt, message, strlen(MSG)+1), "Err write");   
    //printf("envoye\n");
    CHECK(read(s_clt, Buff, MAXBUFF), "Err read");
    //printf("recu\n");
    printf("Buff : %s\n", Buff);
    
    close(s_clt);
    return Buff;
}


 /**
 * \fn void create_profil()
 * \brief Create user profile
 *
 * \author Dzik Timothee
 * \return
 */
void create_profil() {
    char mess[100] = "";
    

    printf("Quel pseudo voulez vous utiliser ? \n");
    scanf("%s", pseudo); fflush(stdin);
    printf("fdp\n");
    strcat(mess, "create|");
    strcat(mess, pseudo);
    printf("----->%s\n", creation_message(mess));
    //printf("Félicitation %s vous êtes enregistré !\n", pseudo);

}


 /**
 * \fn void identification()
 * \brief Identification
 *
 * \author Dzik Timothee
 * \return
 */
void identification() {
    char message[50] = "";
    
    //On demande a utilisateur si il a un profil
        //Demander le pseudo du user : Myprofil(user) => cette fonction prends comme arg le pseudo, vérifie s'il éxiste sur le 		fichier joueurs.txt et affiche ses infos
        //Son pseudo | victoires | Défaite | Score
        
        //On concatene pseudo
        strcat(message, "identification|");
        strcat(message, pseudo);
        //On envoie le message
        
        if(strcmp(creation_message(message), "oui") == 0){
            printf("Salut babe !\n");
        }else{
            printf("Votre pseudo n'existe pas\n");
        }
        
    }

 /**
 * \fn void myProfile(const char pseudo[40]){
 * \brief List current profile
 *
 * \author Dzik Timothee
 * \return
 */  
void myProfile(char pseudo[40]){

    char message[50] = "";
    char *token;
    int ga, scr, perdu;
    
    strcat(message, "score|");
    strcat(message, pseudo);
    
    token = strtok(creation_message(message),"|");
    printf(" Votre pseudo est : %s \n", token);
    token = strtok(NULL,"|");

    printf(" Le nombre de vos parties gagnées est : %s \n", token);
    ga=atoi(token);

    token = strtok(NULL,"|");       
    printf(" Le nombre de vos parties perdues est : %s \n", token);
    perdu=atoi(token);
    
    scr = ga-perdu; 
    if( (scr > 0 ) || (scr ==0 ) )
    {
        printf(" Votre score est : %d \n", scr);
    }
    else if (scr < 0 ) 
        printf(" Votre score est : 0 \n ");

}

 /**
 * \fn void score_joueur(const char pseudo[40]){
 * \brief List user score
 *
 * \author Dzik Timothee
 * \return
 */  
void score_joueur(char pseudo[40]){

    char message[50] = "";
    char *token;
    int ga, scr, perdu;
    
    strcat(message, "score|");
    strcat(message, pseudo);

    
    token = strtok(creation_message(message),"|");
    token = strtok(NULL,"|");

    printf(" Le nombre de vos parties gagnées est : %s \n", token);
    ga=atoi(token);

    token = strtok(NULL,"|");       
    printf(" Le nombre de vos parties perdues est : %s \n", token);
    perdu=atoi(token);
    
    scr = ga-perdu; 
    if( (scr > 0 ) || (scr ==0 ) )
    {
        printf(" Votre score est : %d \n", scr);
    }
    else if (scr < 0 ) 
        printf(" Votre score est : 0 \n ");

}

 /**
 * \fn void jouer()
 * \brief Launch the game
 *
 * \author Dzik Timothee
 * \return
 */  
void jouer(){
    char *token;
    char userAnswer[40]="", secondAnswer[40]="",result[40]="";
    char rep[300]="";

    printf("COUCOUC\n");
    strcpy(rep, creation_message("question|"));
    
    token = strtok(rep, "|");
    printf("Question : %s\n", token);

    token = strtok(NULL,"|");       
    printf(" %s \n", token);

    token = strtok(NULL,"|"); 
    printf("Your answer ?\n"); 
    scanf("%s", userAnswer); fflush(stdin);
    printf("bonne reponse token0 :%c\n", token[0]);
    printf("user rep :%s\n", userAnswer);
    if(token[0] == userAnswer[0]){
        printf("Bonne reponse\n");
        strcat(result, "win|");
        strcat(result, pseudo);
        printf("%s\n", creation_message(result));
    }
    else{
        printf("Mauvaise reponse\n");
        strcat(result, "loose|");
        strcat(result, pseudo);
        printf("%s\n", creation_message(result));
    }

    printf("Autre question ? (o/n) \n");
    scanf("%s", secondAnswer); fflush(stdin);
    if(strcmp(secondAnswer, "o") == 0) {
        jouer();
    }
    
}

 /**
 * \fn void bestScore()
 * \brief Display bestscore
 *
 * \author Dzik Timothee
 *
 * \return 
 */  
void bestScore(){
    printf("Le BestScore est :  %s\n", creation_message("bestScore|"));
}

 /**
 * \fn void lancerMenu()
 * \brief Menu
 *
 * \author Dzik Timothee
 *
 * \return 
 */  
void lancerMenu() {
    printf("%s\n", pseudo);
    int choix = 0;
    while (choix != 5) {
        printf("Que voulez vous faire ?\n 1- Voir mon profil\n 2- Mon score\n 3- Best Score ! \n4- Jouer !\n5- Quitter\n");
        scanf("%d", &choix); fflush(stdin);
        switch (choix) {
            case 1:
                myProfile(pseudo);
                break;
            case 2:
                score_joueur(pseudo);
                break;
            case 3:
                bestScore();
                break;
            case 4:
                jouer();
                break;
            default:
                break;
        }
    }
}

//main
int main(void)
{
    char d;

    printf("Bonjour et bienvenue dans \"Question/Réponse \" \n Avez vous un profil ? (o/n) ");
    scanf("%s", &d);fflush(stdin);
    
    if(d == 'o'){
        printf("Quel est votre Pseudo ?\n");
        scanf("%s", pseudo); fflush(stdin);
        printf("pseudo menu %s\n", pseudo);
        identification();
        lancerMenu();
    }
    if(d == 'n') {
        create_profil();
        lancerMenu();
    }

    return 0;
}
