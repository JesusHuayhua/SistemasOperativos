#! /bin/bash

echo "Solucion con solo while"
number=0
max=10
while  (( max > number ))
do
    impresion=$number
    while (( impresion >= 0 ))
    do
        echo -n "$impresion "
        (( impresion--))
    done
    echo ""
    ((number++))
done 

echo "Solucion con solo for"
number=0
max=10

for (( i = 0; i < max; i++)) do
    for (( j = i; j >= 0; j--)) do
        echo -n "$j "
    done
    echo ""
done

echo "Solucion con for y seq"

number=0
max=9
for i in $(seq 1 1 $max); do
    for j in $( seq $i -1 0 ); do
        echo -n "$j "
    done
    echo ""
done

# seq va des la siguiente manera:
# seq inicio incremento fin