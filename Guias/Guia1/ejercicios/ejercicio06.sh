#! /bin/bash

#==========================
# Variable global para almacenar las 2 soluciones de la funcion
#==========================
declare -a soluciones

#==========================
# Funciones
#=========================
cuadratic_equation(){
	local a=$1
	local b=$2
	local c=$3
	local potencia
	local discriminate
	local denominador
	local sol1
	local sol2

	potencia=$(echo "scale=5; $b^2" | bc )
	discriminate=$(echo "scale=5; sqrt($potencia - 4 * $a * $c)" | bc )
	denominador=$(echo "scale=5; 2 * $a" | bc)
	sol1=$(echo "scale=5; (-1 * $b + $discriminate) / $denominador" | bc )
	sol2=$(echo "scale=5; (-1 * $b - $discriminate) / $denominador" | bc )
	soluciones=("$sol1" "$sol2")
}

if (( $# != 3 )); then
	echo "El script recibie unicament 3 valores (A B C)"
fi

# Verificamos que todos los valores ingresados sean enteros

for i in "$@"; do
	if ! [[ "$i" =~ ^-?[0-9]+(\.[0-9]+)?$ ]]; then
		echo "Todos los valores ingresados tienen que ser enteros o decimales"
		exit 1
	fi
done

cuadratic_equation "$@"

echo "Las soluciones son: ${soluciones[@]}"

