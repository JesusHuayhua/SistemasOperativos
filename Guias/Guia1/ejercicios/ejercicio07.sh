#!/bin/bash

# Función para calcular la suma de todos los números de cinco dígitos que contienen exactamente dos dígitos distintos
suma_numeros() {
    local suma=0
    
    # Digitos posibles
    local digitos=(4 5 6)

    # Iterar sobre cada combinación de dos dígitos diferentes
    for d1 in "${digitos[@]}"; do
        for d2 in "${digitos[@]}"; do
            if [ "$d1" -ne "$d2" ]; then
                # Generar todos los números de cinco dígitos con exactamente d1 y d2
                for i in {0..4}; do
                    for j in {0..4}; do
                        if [ "$i" -ne "$j" ]; then
                            for k in {0..4}; do
                                if [ "$k" -ne "$i" ] && [ "$k" -ne "$j" ]; then
                                    for l in {0..4}; do
                                        if [ "$l" -ne "$i" ] && [ "$l" -ne "$j" ] && [ "$l" -ne "$k" ]; then
                                            m=$((10 - i - j - k - l))
                                            num="$d1$d1$d1$d1$d1"
                                            num=$(echo "$num" | sed "s/$d1/$d2/g")
                                            num=$(echo "$num" | sed "s/..../$d2$d1$d2$d1$d2/")
                                            suma=$((suma + num))
                                        fi
                                    done
                                fi
                            done
                        fi
                    done
                done
            fi
        done
    done
    
    echo "$suma"
}

# Llamar a la función para obtener la suma
total_suma=$(suma_numeros)

# Imprimir el resultado
echo "La suma total es: $total_suma"
