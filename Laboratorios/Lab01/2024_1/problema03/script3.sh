#!/bin/bash

archivo="data - pregunta 3"

while read linea; do
	first_column=$(echo "$linea" | cut -d' ' -f1)
	second_column=$(echo "$linea" | cut -d' ' -f2-)
	second_column=( $second_column )
	second_column="${second_column[@]^}"
	
	# new_second_column="${second_column[@]^}"
	# new_second_column=( $new_second_column )
	echo "$second_column $first_column" >> file_modificate
done < "$archivo"

