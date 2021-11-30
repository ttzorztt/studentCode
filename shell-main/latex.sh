#! /bin/bash
file=$1
lualatex "$file.tex"
mv "$file.pdf" pdf/
rm "$file.aux" "$file.log"