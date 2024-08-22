#! /bin/bash

#--------------------------------------
# FUNCIONES
#--------------------------------------

atoi() {
	local str=$1
	local result
	result=$(expr "$str" + 0 2>/dev/null)
	
	if (( $? != 0)); then
		echo "ERROR: expresion del str invalidad" >&2
		return 1
	fi
	echo "$result"
}

itoa(){
	local int=$1

	if ! [[ "$int" =~ ^-?[0-9]+$ ]]; then 
		echo "ERROR: El input no es un entero" >&2
		return 1
	fi	

	local result
	result=$(printf "%d" "$int")

	echo "$result"
}

#===========================
# PRUEBA 
#===========================


integer=$(atoi "123")
echo "El valor del entero es $integer"
string=$(itoa 123)
echo "El valor de la cadena es $string"
