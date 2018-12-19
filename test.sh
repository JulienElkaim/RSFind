#!/bin/bash

# vous pouvez creer une hierarchie de fichier
# 	soit dans votre depots
#	soit dans en script (et suppression en fin de test)



DATE='/bin/date'
rm -rf tmp
mkdir tmp

truthArray=(
	""
    "find DOSSIER"
    "find DOSSIER -name fir.png"
    "find DOSSIER -print"
    #"grep -r -l DOSSIER -e CHAINE"
    "find DOSSIER -type f -exec file {} \; | grep image | cut -d : -f 1"
    "find DOSSIER -exec ls -l -d {} \;"
    "find DOSSIER -exec ls -l {} \;" #o
    "find DOSSIER -exec ls -l \;"
    "find DOSSIER -name fir.png -type f -exec file {} \; | grep image | cut -d : -f 1"
    "find DOSSIER -print -exec ls -l {} \;"
    #"find DOSSIER -name REGEXP"
    #"grep -r -l DOSSIER -e REGEXP"
    "./rsfind DOSSIER"
    "./rsfind DOSSIER -i " 
    #"rsfind DOSSIER -t CHAINE"
    
	
)

testArray=(
	""
    "./rsfind DOSSIER"
    "./rsfind DOSSIER --name fir.png"
    "./rsfind DOSSIER --print"
    #"./rsfind DOSSIER -t CHAINE"
    "./rsfind DOSSIER -i" 
    "./rsfind DOSSIER -l" 
    "./rsfind DOSSIER --exec \"ls -l {}\"" #
    "./rsfind DOSSIER --exec \"ls -l\""
    "./rsfind DOSSIER --name fir.png -i"
    "./rsfind DOSSIER --print --exec \"ls -l {}\"" #  
    #"./rsfind DOSSIER --ename REGEXP"
    #"./rsfind DOSSIER -T REGEXP = grep -r -l DOSSIER -e REGEXP"
    "./rsfind DOSSIER -p 4"
    "./rsfind DOSSIER -p 4 -i"
    #"./rsfind DOSSIER -p 4 -t CHAINE"

)

test_error=false

for ((i = 0; i < ${#truthArray[@]}; i++))
do
    echo "Test : ${testArray[$i]}"

    #BEFORETRUTH=$($DATE +'%N')
    eval ${truthArray[$i]} > tmp/truthTest.txt
    #AFTERTRUTH=$($DATE +'%N')
    #CMPTTRUTH=$(($AFTERTRUTH - $BEFORETRUTH))
    #echo Truth exec is: $CMPTTRUTH
    
    #BEFORETEST=$($DATE +'%N')
    eval ${testArray[$i]} > tmp/resTest.txt
    #AFTERTEST=$($DATE +'%N')
    #CMPTTEST=$(($AFTERTEST - $BEFORETRUTH))
    #echo Test exec is: $CMPTTEST

    diff tmp/truthTest.txt  tmp/resTest.txt
    e_code=$?
    
    if [ $e_code != 0 ]
    then
        printf "TEST FAIL : %d\n" "$e_code"
        test_error=true
    else
        printf "TEST OK!\n"
    fi
    echo
    echo ============================================
    echo
done

rm -rf tmp

if [ $test_error = true ] 
then
    exit 2
else
    exit 0
fi
