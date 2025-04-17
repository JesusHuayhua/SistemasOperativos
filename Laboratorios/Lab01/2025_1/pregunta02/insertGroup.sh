#!/bin/bash
#
if (( $# < 2 )); then
	echo "El script tiene que recibir como parametros:"
	echo "- Nombre del usuario"
	echo "- Nombres de los grupos(minimo 1)"
	exit
fi

cnt_grupos=$(($# - 1 ))
usuario=$1


uid=$(cat passwd | grep $usuario | cut -d":" -f3)
if ((uid==0)) ; then
	echo "El usuario no existe"
	exit 1
fi

for arg in $*
do
	# No se analiza el usuario
	if [ $arg = $1 ]; then
		continue
	fi
	grupo=$(cat group | grep $arg ) # encontramos al grupo
	echo $grupo
	if  [ -z grupo ]; then
		echo "El grupo no existe"
		continue
	fi
	# El grupo existe
	nuevo_grupo=$(echo "$grupo,$usuario")
	sed "s/$grupo/$nuevo_grupo/" -i group
done
