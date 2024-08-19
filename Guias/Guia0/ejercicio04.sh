# !bin/bash
#

##################
# Pregunta01
# El ejemplo nos pide que se realize desde el directorio HOME, pero se va a realizar
# deste este directorio
directorio=$(pwd)
mkdir dir1 dir2 dir3
mkdir -p dir1/dir1.1 dir1/dir1.2
mkdir -p dir1/dir1.1/dir1.1.1. dir1/dir1.1/dir1.1.2
mkdir -p dir2/dir2.1 dir2/dor2.2
mkdir -p dir3/dir3.1  dir3/dir3.2
################
# Pregunta02
#################
tree $directorio
################
# Pregunta03
#################
cd dir1/dir1.1/
rmdir  *
cd ..
rmdir  *
cd ../dir2
rmdir  *
cd ../dir3
rmdir *
cd ..
rmdir *
# La siguiente liniea se utiliza para eliminar todos los directorios creados
#rm -r dir1 dir2 dir3
