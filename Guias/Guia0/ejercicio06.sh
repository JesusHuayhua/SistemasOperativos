#! /bin/bash

####################
# Pregunta01
####################

find /etc/ -size +20
find /etc/ -size 10000c

##########################
# Pregunta02
#########################

find / -type f -empty
#find / -type d -empty # if you like search empty directories

########################
# Pregunta03
########################

find / -name *.c -20

######################
# Pregunta04
#######################

find / -type f -print0 | xargs -0 ls -lt | head -n 1

######################
# Pregunta05
######################
find ~ -type d -emtpy -delete # Delete the all empty directories in your home directoriy
