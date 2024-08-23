#!/bin/bash

if (( $# != 2 )); then
	echo "ERROR: El script solo puede recibir 2 argumentos"
	exit 1
fi

#===================================
# FUNCIONES
#==================================

es_primo() {
	local numero=$1
	local i

	if (( $1 == 1)); then
		return 0
	fi

	sqrt=$(echo "scale=0;sqrt($numero)" | bc )

	for ((i = 2; i <= sqrt; i ++ )); do
		if (( numero % i == 0 )); then
			return 1
		fi
	done
	return 0
}

for num in $(seq $1 1 $2); do
	echo -n "$num"
	if es_primo $num; then
		echo " primo"
	else
		echo ""
	fi
done












