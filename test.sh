#!/bin/bash

# vous pouvez creer une hierarchie de fichier
# 	soit dans votre depots
#	soit dans en script (et suppression en fin de test)


DATE='/bin/date'
rm -rf tmp
mkdir tmp

truthArray=(
	"find"
    "find"
    "find DOSSIER"
    "find DOSSIER"
    
	
)

testArray=(
	"find"
    "find"
    "find DOSSIER -print "
    "./rsfind DOSSIER"
)

test_error=false

for ((i = 0; i < ${#truthArray[@]}; i++))
do
    echo "Test: ${testArray[$i]}"
    BEFORETRUTH=$($DATE +'%N')
    eval ${truthArray[$i]} > tmp/truthTest.txt
    CMPTTRUTH=$(($($DATE +'%N') - $BEFORETRUTH))
    echo Truth exec is: $CMPTTRUTH
    BEFORETEST=$($DATE +'%N')
    eval ${testArray[$i]} > tmp/resTest.txt
    CMPTTEST=$(($($DATE +'%N') - $BEFORETRUTH))
    echo Test exec is: $CMPTTEST
    diff tmp/truthTest.txt  tmp/resTest.txt
    e_code=$?
    echo APRES DIF
    if [ $e_code != 0 ]
    then
        printf "TEST FAIL : %d\n" "$e_code"
        test_error=true
    else
        printf "TEST OK!\n"
    fi
    echo
done

rm -rf tmp

if [ $test_error = true ] 
then
    exit 2
else
    exit 0
fi
