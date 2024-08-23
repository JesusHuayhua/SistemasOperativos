#!/bin/bash
if (( $# != 3 )); then
	echo "ERROR: El programa tiene que recibir 3 argumentos"
	exit 1
fi


numeros=($(seq $1 1 $2))

for i in $(seq $1 1 $2); do
	if [[ "$i" == *"$3"* ]]; then
		echo "$i"
	fi
done
