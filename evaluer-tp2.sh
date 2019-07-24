#!/bin/bash
# evaluer-tp2.sh
if [ -z $1 ]
then
  correction=inf3135-e2019-tp1.correction
else
  correction=$1
fi
if [ ! -f ${correction} ] ; then
  wget -q -nc https://github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/${correction} -O ${correction}
  # -nc est no-clobber, ne telecharge pas le fichier s'il existe.
fi
if [ ! -f ${correction} ]
then
  echo "erreur fatale, fichier correction inexistant."
  exit 1
fi
#code Permanent de l'etudiant qui se lit du fichier cp.txt
codePermanent=`cat cp.txt`
#la variable ou on stock tous les points reussis de l'etudiant
pointsReussis=0
#la variable qui calcule le nombre de test passer
i=0
#si le test passe il est reussi sinon echec
boolean="reussi"
p="points"

#boucle principale pour lire chaque ligne extraire les informations et la traite
while read line
do
#les points que vaut chaque test
points=${line:0:1}
#le temps d'execution accorder pour chaque test
tempsExec=${line:2:2}
#le code de retour attendu apres lexecution de chaque commande
codeRetour=${line:4:3}
#la commande utilisee pour le test
commande=${line:29}

#Si le temps dexecution depasse le maximum accorder c est un echec
if [ $tempsExec -ne "00" ]
then
commande="timeout ${tempsExec}s $commande"
fi

#Une fois le test passer on stock ce qui s affiche dans le stdout dans la variable resultat
eval $commande > /dev/null 2>&1
resultat=$? 



#si le resultat qu on a obtenu est egal au code d erreur attendu 
#alors le test est passe avec scces et on ajoute le point a l etudiant sinon eche
if [ ${resultat} -eq ${codeRetour} ]
then
resultat="$boolean $points $p"
pointsReussis=$((pointsReussis + points))
else
resultat="echec"
fi
#on incremente le nombre de test passer
i=$((i+1))
# si le nombre de test depasse 10 on enleve un espace pour que l affichage soit bien fait
if [ $i -lt 10 ]
then
echo "$i : $resultat"
else
echo "$i : $resultat"
fi

#fin de la boucl qui lit le fichier correction
done < $correction

#affichage du resultat final obtenu par l'etudiant
echo ""
echo "Note (total) pour $codePermanent dans inf3135-e2019-tp2: $pointsReussis"
echo $codePermanent	$pointsReussis
