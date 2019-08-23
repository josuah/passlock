#!/bin/sh -e
# usage: bin/make-h file.c [file.c...]

awk '
/^[a-zA-Z0-9_]+\(/ {
	if (match(type, "static") || match($0, ";$"))
		next

	symbol = $0
	sub("\\(.*", "", symbol)
	sub("[a-zA-Z0-9_]*\\(", "", $0)

	if (symbol == "main")
		next

	IN = 1
}

IN {
	args = args " " $0
}

IN && /\)$/ {
	gsub("[ \t]+", " ", args)
	sub("^ ", "", args)
	gsub(/[a-zA-Z0-9_]+(\[[^]]*\])+,/, "*,", args)
	gsub(/[*][a-zA-Z0-9_]+,/, "*,", args)
	gsub(/[ ][a-zA-Z0-9_]+,/, ",", args)
	gsub(/[a-zA-Z0-9_]+\[[^]]*\]\)$/, "*", args)
	gsub(/[*][a-zA-Z0-9_]+\)$/, "*", args)
	gsub(/[ ][a-zA-Z0-9_]+\)$/, "", args)
	gsub(/\.\.\.\)$/, "...", args)
	gsub(/void\)$/, "void", args)
	sub("inline ", "", type)

	printf("%-15s %s(%s);\n", type, symbol, args)

	args = ""
	IN = 0
}

!IN {
	type = $0
}
' "${1%.?}.c" | sed -r 's,^([a-zA-Z_ ]+)( *)\*+( +),\1\2\3*,' | sort
