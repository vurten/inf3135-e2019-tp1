#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// prototypes de fonctions utilisees
int nbrCarac (char *Chemin);
void stockerFichier( char* chemin, char* texte );
void ecrireFichier (char *texte,char *chaine);
void stockerFichierA( char *chemin, char *texte );

// declaration des variables utilisess
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


// boucle principale qui traite les validations
for(int i = 0 ; i < argc ; i++) {

// s'il y a un seul argument ou moins le programme renvoie une erreur
	if(argc <= 1) {
		fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
	return 1;
// si le code permanent a -12 caracteres le programme renvoie une erreur sinon il ouvre le fichier cp.txt et le stock dedans

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

// verification des arguments pour savoir si on veut decoder ou encoder
	}else if(strcmp(argv[i] ,"-d") == 0) {
		decoder = 1;
		encoder =0;
	}else if(strcmp(argv[i] ,"-e") == 0) {
		encoder =1;
		decoder =0;

// verification de la cle elle doit etre juste un chiffre positif ou negatif sinon on renvoi une erreur
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
// si l'argument est -i on va aller chercher l'autre argument puis ouvrir le fichier et le stocker dans un tableau

	}else if(strcmp(argv[i] ,"-i") == 0) {

		longueurFichier = nbrCarac (argv[i+1]);
		tableau = (char *)malloc( longueurFichier*sizeof(char));
		stockerFichier( argv[i+1], tableau );
// si l'argument est -a on va aller chercher l'autre argument puis ouvrir le fichier et le stocker dans un tableau

	}else if(strcmp(argv[i] ,"-a") == 0) {

		longueurFichierA = nbrCarac (argv[i+1]);
		alphabet = (char *)malloc( longueurFichierA*sizeof(char) );
		stockerFichierA( argv[i+1], alphabet );
		AEstLa = 1;

// si l'argument est -o on va aller chercher le prochain argument pour le stocker comme etant le nom de fichier
	}else if(strcmp(argv[i] ,"-o") == 0) {

		strncpy(nomFichierSortie, argv[i+1],1000);

// traitement des arguments non valide on renvoi -3 si c'est different de -i -o -a -k -s -d -e

	}else if (argv[i][0] == '-' && (argv[i][1] != 'i' || argv[i][1] != 'o' || argv[i][1] != 'a' || argv[i][1] != 'k' || argv[i][1] != 'd' || argv[i][1] != 'e' || argv[i][1] != 'a') 
			&& strcmp(argv[i-1] ,"-k") != 0){
		return 3;
	}
}
// on verifie si le fichier alphabet et dans le meme dossier  que le projet 
if (AEstLa != 1){
	longueurFichierA = nbrCarac ("alphabet.txt");
        alphabet = (char *)malloc( longueurFichierA*sizeof(char) );
        stockerFichierA( "alphabet.txt", alphabet );

}
// si le code permanent n'est pas present on retourne une erreur
if (codeC != 1){
	fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
	return 1;
}

// si dans les arguments on ne sait pas si la personne veut encoder ou decoder on recoit une erreur
if (decoder == 1 || encoder == 1){

}else {
	return 4;
}
// si la cle n'est pas on retourne une erreur
if (cleEstLa != 1){
	return 7;
}
// creation du tableau qui va contenir le resultat qu'on va affiche au final
char resultat[longueurFichier];
resultat[longueurFichier] = 0;

longueurFichierA = longueurFichierA -1;

// si on veut decoder on va multiplier la cle par -1
if (decoder == 1){
        cleA = (-1) * cleA;
}

long int cle = cleA;
cle = cle % longueurFichierA;


// traitement pour les cles qui sont >0
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

// traitement pour les cles qui sont inferieur a 0  
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
// sinon si la cle est egal a 0 on laisse le message comme il est
}else {
	for (int i =0 ; i < strlen(tableau) ; i++){
		resultat[i] = tableau[i];
	}
}

free(alphabet);
free(tableau);

// on ecrit le fichier sauvegarder dans un fichier
ecrireFichier (nomFichierSortie, resultat);

return 0;
}

// une methode qui calcule le nombre de caractere dans un fichier
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

// cette methode permet de stocker le contenu d un fichier dans un tableau
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

// cette methode permet d ecrire le contenu du resultat final dans un fichier
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

// cette methode permet de stocker le fichier alphabet
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
