#!/bin/bash

if (($# != 1 ));then
	echo "ERROR: Solo se puede recibir un argumento"
	exit 1
fi

coincidencia=$1

for file in $(ls); do
	# fuscamos que exista la coincidencia solicitada
	if [[ "$file" == *"$coincidencia"* ]];then
		new_file=$(echo "${file//$coincidencia/}")
#		echo "$new_file"
		mv $file $new_file
	fi
done
