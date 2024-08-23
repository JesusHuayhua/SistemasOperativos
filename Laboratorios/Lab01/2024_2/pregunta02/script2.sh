#!/bin/bash
if (( $# != 1 )); then
	echo "ERROR: El script solo puede recibir 1 argumento"
	exit 1
fi

file_name=$1

while read line; do
	# Como el codigo tiene una cifra fija, podemos saber  que 
	# parte de la linea queremos quedarnos
	codigo=${line:0:8}
	nombre_completo=${line:9}
	nombre=$( echo "${nombre_completo##*, }" )
	apellido=$(echo "${nombre_completo%%,*}" )
	apellidos=( $apellido )
	nombres=( $nombre )
	declare -l nombre_completo_minuscula=$(echo "${nombre[@]}")
	nombre_completo_minuscula=( $nombre_completo_minuscula )
	nombre_final=$( echo "${nombre_completo_minuscula[@]^}")
#	echo "${nombre_completo_minuscula[@]^}"
	primer_nombre="${nombres[0]}"
	primer_apellido="${apellidos[0]}"
	declare -l nombre_correo="$primer_nombre"
	declare -l apellido_correo="$primer_apellido"
#	echo "$codigo:$apellido,${nombre_completo_minuscula[@]^}:$nombre_correo.$apellido_correo@pucp.edu.pe"
	echo "$codigo:$apellido,$nombre_final:$nombre_correo.$apellido_correo@pucp.edu.pe"
done < "$file_name"
