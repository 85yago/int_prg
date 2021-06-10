#!/bin/sh

echo "フォルダ番号を入力"

read NUM

mkdir -p ./${NUM}/rep ./${NUM}/src

for i in `seq 1 4`
do
    touch ./${NUM}/src/ex${NUM}-${i}.c
    touch ./${NUM}/rep/0${i}.md
done
