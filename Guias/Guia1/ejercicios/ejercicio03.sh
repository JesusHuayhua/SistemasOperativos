#! /bin/bash

# Verificamos si realmente se agrego 1 archivo
if (($# == 0)); then
    echo "Falta indicar el nombre del archivo"
    exit 1
fi

# verificamos que solo tenga 1 argumento
if (( $# != 1)); then
    echo "Solo se puede tener 1 argumento"
    exit 1
fi

# Verificamos si existe el archivo ingresado
if ! test -f "$1" ; then
    echo "El archivo no existe"
    exit 1
fi

# Si existe el archivo
if test -f "new$1"; then
    rm "new$1"
fi

# Leemos el archivo linea por linea
while read -r line; do
    echo -ne "$line" >> "new$1" # esta expresion sirve para concatener 2 strings
    echo -e "\n\n\n" >> "new$1" # Así mismo, sirve para que las nuevas lineas sean escritas al final del archivo
done <"$1"

if test -f "old$1"; then
    rm "old$1"
fi

while read -r line; do
    if [[ $line != "" ]]; then
        echo -e "$line" >> "old$1"
    fi
done <"new$1"
