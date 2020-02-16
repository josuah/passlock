#!/bin/sh

for file in src/*.c; do file=${file%.c}
	header=$(awk '$0 == "/**/" { exit(0) } 1' "$file.h"
		proto "$file.c")
	printf '%s\n' "$header" >"$file.h"
done
