#!/bin/bash

if (($# != 3));then
	echo "Se tiene que ingresar 3 parametros"
	exit 1
fi

# Pasamos los parametros a variables
n1=$1
n2=$2
factor=$3

#Definimos la funcion is_prime
is_prime(){
	local number=$1
	if ((number  < 0 ));then
		return 1 # No es primo porque es negativo
	elif ((number == 1 )); then
		return 0 # Es primo por defecto
	fi
	sqrt=$(echo "sqrt($number)" | bc ) # hallamos la raiz cuadrada
	local j=2
	for(( j = 2; j <= sqrt ; j++ ))  do
		if (( number % j == 0)); then
			return 1 # no es primo porque se encontro otro numero divisible
		fi
	done
	return 0 # El numero es primo
}

i=$n1
for (( i = $n1; i <= $n2 ; i++)) do
	cnt=$i
	while (( cnt > 0 ));do
		dig=$((cnt%10))
		if ((dig == factor));then
			if is_prime $i ; then
				echo "$i (primo)"
			else
				echo "$i"
			fi
		fi
		cnt=$((cnt/10))
	done

done
