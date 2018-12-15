#!/bin/bash

# vous pouvez creer une hierarchie de fichier
# 	soit dans votre depots
#	soit dans en script (et suppression en fin de test)

rm -rf tmp
mkdir tmp

truthArray=(
	"echo test"
	"echo autre"
)

testArray=(
	"./rsfind test"
	"./rsfind autre"
)

test_error=false

for ((i = 0; i < ${#truthArray[@]}; i++))
do
    echo "Test: ${testArray[$i]}"
    eval ${truthArray[$i]} > tmp/truthTest.txt
    eval ${testArray[$i]} > tmp/resTest.txt

    diff tmp/truthTest.txt  tmp/resTest.txt
    e_code=$?

    if [ $e_code != 0 ]
    then
        printf "TEST FAIL : %d\n" "$e_code"
        test_error=true
    else
        printf "TEST OK!\n"
    fi
done

rm -rf tmp

if [ $test_error = true ] 
then
    exit 2
else
    exit 0
fi
