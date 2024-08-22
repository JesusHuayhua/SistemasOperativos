#! /bin/bash

start=60000
final=63000
array=$(seq $start 1 $final)

is_prime(){
	local num=$1
	local sqrt i
	sqrt=$(echo "scale=0; sqrt($num)" | bc )
	for (( i = 2; i <= sqrt; i++ )); do
		if (( num % i == 0 )); then
			return 1
		fi
	done
	return 0
}

for i in $(seq $start 1 $final); do
	if is_prime $i; then
		echo "$i"
	fi
done
