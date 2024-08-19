# !/bin/bash

#############
# Pregunta01
############

cal -y 2024

#############
# Pregunta02
############

MES=$(date -d "$D" +"%m")
mes=$(echo "$MES - 1" | bc -l)
cal -B$mes
