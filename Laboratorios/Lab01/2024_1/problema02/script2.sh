#!/bin/bash
if (( $# != 1 )); then
	echo "ERROR: Solo se acepta 1 parametros"
	exit 1
fi

for file in $(ls); do
	if [[ "$file" == *"$1"* ]]; then
		new_file="${file//$1/}"
		mv $file $new_file
	fi
done
