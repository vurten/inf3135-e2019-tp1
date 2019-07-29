#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>






int main (int argc , char *argv[]){
int codeC = 0;
int encoder = 0;
int decoder = 0;
int cleEstLa = 0;
int AEstLa = 0;
bool estNbr = true;
long int cleA = 0;

FILE *alpha = NULL;
int nbrAlpha = 0;
char *tableau = 0;
long int longueur = 0;
FILE *entree = stdin;
FILE *sortie = stdout;

for(int i = 0 ; i < argc ; i++) {

	if(argc <= 1) {
		fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
	return 1;

// validation du code permanent -c

	}else if(strcmp(argv[i] ,"-c") == 0) {
		int longueur = strlen(argv[i+1]);
		codeC = 1;

		if(longueur != 12 ){
			return 2;
		}

// compteur pour decoder -d

	}else if(strcmp(argv[i] ,"-d") == 0) {
		decoder = 1;

// compteur pour encoder -e

	}else if(strcmp(argv[i] ,"-e") == 0) {
		encoder =1;

// valider la cle -k

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

// valider le input -i

	}else if(strcmp(argv[i] ,"-i") == 0) {

		entree = fopen( argv[i+1], "r");

		if (entree == NULL){
			return 5;
		}else {

		}if (entree != NULL){
			int carac = 0;

			while(carac != EOF){
				carac = fgetc(entree);
				if (carac != EOF){
					longueur = longueur +1;
				}
			}


		}

		fclose(entree);
		entree = fopen( argv[i+1], "r");

		longueur = longueur -1;
		



// valider le output -o

	}else if(strcmp(argv[i] ,"-o") == 0) {

		sortie = fopen( argv[i+1], "w");
		if (sortie == NULL){
			return 6;
		}
// valider le fichier alphabet -a

	}else if(strcmp(argv[i] ,"-a") == 0) {
		char alphabet [13]= "alphabet.txt";
		char alphabetSlash[14] = "/alphabet.txt";
		char cheminAlphabet [1000] = {0};
		int  longChaine = strlen(argv[i+1]);
		AEstLa = 1;

		strcat(cheminAlphabet,argv[i+1]);

		if(cheminAlphabet[longChaine-1] == '/'){
			strcat(cheminAlphabet,alphabet);
		}else if(cheminAlphabet[longChaine-1] != '/'){
			strcat(cheminAlphabet,alphabetSlash);
		}


		alpha = fopen( cheminAlphabet, "r");

		if (alpha == NULL){
			return 8;
		}else if (alpha != NULL){
			int carac = 0;

			while(carac != EOF){
				carac = fgetc(alpha);
				if (carac != EOF){
					nbrAlpha = nbrAlpha +1;
				}
			}


		}

		fclose(alpha);
		tableau = (char *)malloc( nbrAlpha*sizeof(char));
		alpha = fopen( cheminAlphabet, "r");
		if( alpha != NULL && tableau != NULL ){
                	int j = 0;
                	char caract = 0;
                	while(fscanf(alpha,"%c",&caract) != EOF){
                     		tableau[j]=caract;
                        	j++;
                	}
      		}else {
             		exit(8);
        	}
		fclose(alpha);

// valider si argument non valide

	}else if (argv[i][0] == '-' && (argv[i][1] != 'i' || argv[i][1] != 'o' || argv[i][1] != 'a' || argv[i][1] != 'k' || argv[i][1] != 'd' || argv[i][1] != 'e' || argv[i][1] != 'a')
			&& strcmp(argv[i-1] ,"-k") != 0){
		return 3;
	}


}


if (codeC == 0){

}

// gerer les erreurs de -d et -e

if (decoder == 0 && encoder == 0){
	return 4;
}
 if (decoder == 1 && encoder == 1){
	return 9;
}

// si le -k est pas la on lance une erreur

if (cleEstLa != 1){
	return 7;
}

// si le -a est pas la on ouvre le fichier alphabet.txt

if (AEstLa != 1){
	alpha = fopen( "alphabet.txt", "r");

	if (alpha == NULL){
		return 8;
	}else if (alpha != NULL){
			int carac = 0;

			while(carac != EOF){
				carac = fgetc(alpha);
				if (carac != EOF){
					nbrAlpha = nbrAlpha +1;
				}
			}


		}
fclose(alpha);
tableau = (char *)malloc( nbrAlpha*sizeof(char));
alpha = fopen( "alphabet.txt", "r");
if( alpha != NULL && tableau != NULL ){
               int j = 0;
               char caract = 0;
               while(fscanf(alpha,"%c",&caract) != EOF)
                    {
                     	tableau[j]=caract;
                        j++;
                    }
      }else {
             	exit(8);
        }
fclose(alpha);


}

// si -d est la on multiplie la cle * -1

if (decoder == 1){
        cleA = (-1) * cleA;
}



if (entree != NULL){



int carac = 0;

	while(carac != EOF){
	carac = fgetc(entree);
	if (carac != EOF){
	longueur = longueur +1;
	}
	}
rewind(entree);



int caractere = 0;
long int cle = 0;
long int a = strlen(tableau) -1;
if(cleA > a){
	cle = cleA % a;
}else if (cleA == a ){
	cle = 0;
}else{
	cle = cleA % a;

}



long int z = cle;
    	    
	while( caractere != EOF && longueur > 0){

		caractere = fgetc(entree);
		longueur = longueur -1;
		if (caractere != EOF ){
			for(long int i = 0 ; i < strlen(tableau)-1 ; i++){
				if ( caractere == tableau[i] ){
					if ( (i + cle ) > a-1){
						while((i+ cle )>  a-1){
							cle = cle-1;
							i = i+1;
							if (i == a){

							i =0;
							}
						}
					
					fputc(tableau[i+cle], sortie);
					
					i = strlen(tableau);
					cle = z;
					}else {
						fputc(tableau[i+cle], sortie);
					}
					i = strlen(tableau);
				
				}else if ( (caractere != tableau[i]) && ((i) == strlen(tableau)-2) ){
					fputc(caractere, sortie);
					i = strlen(tableau);
				}
			}            		

	
		}
	

        }
fclose (entree);
fclose(sortie);
free(tableau);

}

return 0;
}



