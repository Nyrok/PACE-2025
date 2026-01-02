#!/bin/sh

# Si vous le souhaitez, adapter le script sh suivant qui exécute votre programme sur chaque instance de test et affiche les résultats dans un fichier results.csv
# Le script prend en paramètre le nom du programme à tester et le répertoire contenant les instances de test
# Le programme est exécuté avec une limite de temps de 5 minutes par instance
# Le script utilise le fichier jar ds_verifier-1.0.jar pour vérifier la validité des solutions
# Le format du fichier results.csv est le suivant :
# instance1 ; valeur_solution1
# instance2 ; valeur_solution2
# ...
# instance3 ; TO (si le programme a dépassé la limite de temps)
# instance4 ; KO (si la solution est incorrecte)
# instance5 ; ERR (si le programme a rencontré une erreur)



if [ "$#" -ne 2 ]; then
    echo "Illegal number of parameters. Usage : $0 PROGRAM DIRECTORY_OF_INSTANCES"
    exit 1
fi

PROGNAME=$2
INSTANCES=$3

OUTPUT="results.csv"

DATE=$(date)

echo "$PROGNAME ; $DATE "

for inst in `ls $INSTANCES/*.gr | sort -V`; do
    echo -n "$inst "
    instName=$(basename $inst)

    solFile=$(mktemp -t sol"$instName"XXXXX)
    errFile=$(mktemp -t err"$instName"XXXXX)

    timeout -k 10s $1 $PROGNAME < $inst > $solFile

    STATUS=$?
    if [ $STATUS -eq 137 ] ; then #was killed, so timeouted
        echo "; TO "
    elif [ $STATUS -eq 0 -o $STATUS -eq 124 ] ; then
        OUTVER=$(java -jar ds_verifier-1.0.jar $inst $solFile)
        STATUSVERIF=$?
        
        if [ -z "$OUTVER" ] ; then
            STATUSVERIF=1
        fi

        WIDTH=$(echo $OUTVER | grep -o -E '[0-9]+'); 

        if [ $STATUSVERIF -eq 0 ] ; then
            echo "; $WIDTH "
	    elif [ ! -s $solFile ]; then
	        echo "; TO "
        else
            echo "; KO "
	        echo "KO with output verifier : $OUTVER and status verifier: $STATUSVERIF and status timeout $STATUS"
        fi
    else
	    echo "; ERR "
	    echo "ERR $STATUS"
    fi
done 