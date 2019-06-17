#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int nbrCarac (char *Chemin);
void stockerFichier( char* chemin, char* texte );
void ecrireFichier (char *texte,char *chaine);
void stockerFichierA( char *chemin, char *texte );


int main (int argc , char *argv[]){
FILE *fichierCp = stdout;
int encoder = 0;
int decoder = 0;
int codeC = 0;
int cleEstLa = 0;
long int cleA = 0;
bool estNbr = true;
long int longueurFichier = 0;
long int longueurFichierA = 0;
char *tableau = 0;
char *alphabet = 0;
char nomFichierSortie[1000] ={0};
int AEstLa = 0;


for(int i = 0 ; i < argc ; i++) {

	if(argc <= 1) {
		fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
	return 1;

	}else if(strcmp(argv[i] ,"-c") == 0) {
		int longueur = strlen(argv[i+1]);

		if(longueur != 12 ){
			return 2;
		}else {
			fichierCp = fopen("cp.txt", "w");
			fprintf(fichierCp, "%s\n", argv[i+1]);
			fclose(fichierCp);
			codeC = 1;
		}
	}else if(strcmp(argv[i] ,"-d") == 0) {
		decoder = 1;
		encoder =0;
	}else if(strcmp(argv[i] ,"-e") == 0) {
		encoder =1;
		decoder =0;
        }else if(strcmp(argv[i] ,"-k") == 0) {

		for (int j = 1 ; j < strlen(argv[i+1]) ; j++) {

			if ( (argv[i+1][0] != '-') && (argv[i+1][0] != '+') && (isdigit(argv[i+1][0]))==0 ) {
				estNbr = false;
				return 7;
			}

			if ((isdigit(argv[i+1][j])) ==0) {
				estNbr = false;
				return 7;
			}

		}

		if (estNbr == true){
			cleA = strtol(argv[i+1], NULL, 0);
			cleEstLa = 1;
		}


	}else if(strcmp(argv[i] ,"-i") == 0) {

		longueurFichier = nbrCarac (argv[i+1]);
		tableau = (char *)malloc( longueurFichier*sizeof(char));
		stockerFichier( argv[i+1], tableau );


	}else if(strcmp(argv[i] ,"-a") == 0) {

		longueurFichierA = nbrCarac (argv[i+1]);
		alphabet = (char *)malloc( longueurFichierA*sizeof(char) );
		stockerFichierA( argv[i+1], alphabet );
		AEstLa = 1;
	}else if(strcmp(argv[i] ,"-o") == 0) {

		strncpy(nomFichierSortie, argv[i+1],1000);

	}else if (argv[i][0] == '-' && (argv[i][1] != 'i' || argv[i][1] != 'o' || argv[i][1] != 'a' || argv[i][1] != 'k' || argv[i][1] != 'd' || argv[i][1] != 'e' || argv[i][1] != 'a') 
			&& strcmp(argv[i-1] ,"-k") != 0){
		return 3;
	}
}

if (AEstLa != 1){
	longueurFichierA = nbrCarac ("alphabet.txt");
        alphabet = (char *)malloc( longueurFichierA*sizeof(char) );
        stockerFichierA( "alphabet.txt", alphabet );

}

if (codeC != 1){
	fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
	return 1;
}

if (decoder == 1 || encoder == 1){

}else {
	return 4;
}

if (cleEstLa != 1){
	return 7;
}

char resultat[longueurFichier];
resultat[longueurFichier] = 0;

longueurFichierA = longueurFichierA -1;


if (decoder == 1){
        cleA = (-1) * cleA;
}

long int cle = cleA;
cle = cle % longueurFichierA;



if (cle > 0) {

        for (int i =0 ; i < strlen(tableau); i++){

		if (tableau[i] < 'a' || tableau[i] > 'z'){
			resultat[i] = tableau[i];
		}else {
			resultat[i] = tableau[i];

			for(int j = 0 ; j < strlen(alphabet) ; j++){

				if (resultat[i] != alphabet[j]){
				}else {
					do{
						if(resultat[i] != 'z'){
							resultat[i] =  1 + resultat[i];
							 --cle;
						}else {
							resultat[i] = 'a';
							--cle;
						}

					} while (cle > 0 );
					j = strlen(alphabet);
					cle = cleA;
				}
			}

		}
        }

}else if (cle < 0){
        for (int i =0 ; i < strlen(tableau); i++){

                if (tableau[i] < 'a' || tableau[i] > 'z'){
                        resultat[i] = tableau[i];
                }else {
                        resultat[i] = tableau[i];

                        for(int j = 0 ; j < strlen(alphabet) ; j++){

                                if (resultat[i] != alphabet[j]){
                                }else {
                                        do{
                                                if(resultat[i] != 'a'){
                                                         --resultat[i];
                                                         ++cle;
                                                }else {
                                                        resultat[i] = 'z';
                                                        ++cle;
                                                }

                                        } while (cle < 0 );
                                        j = strlen(alphabet);
					cle = cleA;
                                }
                        }

                }
        }

}else {
	for (int i =0 ; i < strlen(tableau) ; i++){
		resultat[i] = tableau[i];
	}
}

free(alphabet);
free(tableau);
ecrireFichier (nomFichierSortie, resultat);

return 0;
}


int nbrCarac (char *Chemin){

	FILE *fichier = fopen(Chemin,"r");
	int longueur = 0;
	char carac;

	if(fichier != NULL){
		while(fscanf(fichier,"%c",&carac) != EOF){
                        longueur++;
		}
	}else {
		return 5;
	}

	fclose(fichier);
	return longueur;
}


void stockerFichier( char *chemin, char *texte ) {
    FILE *fichier = fopen(chemin,"r");

    if( fichier != NULL && texte != NULL )
      {
               int i=0;
               char carac;
               while(fscanf(fichier,"%c",&carac) != EOF)
                    {
                        texte[i]=carac;
                        i++;
                    }
      }else {
		exit(5);
	}


    fclose(fichier);
}


void ecrireFichier (char *texte,char *chaine) {
	FILE* fichier = NULL;

    fichier = fopen(texte, "w");

    if (fichier != NULL){
        fputs(chaine, fichier);
        fclose(fichier);
    }else {
	exit(5);
	}


}

void stockerFichierA( char *chemin, char *texte ) {
    FILE *fichier = fopen(chemin,"r");

    if( fichier != NULL && texte != NULL )
      {
               int i=0;
               char carac;
               while(fscanf(fichier,"%c",&carac) != EOF)
                    {
                     	texte[i]=carac;
                        i++;
                    }
      }else {
             	exit(8);
        }


    fclose(fichier);
}
