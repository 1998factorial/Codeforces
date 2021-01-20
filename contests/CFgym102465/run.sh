#!/bin/bash
valid=true
count=1
while [ $valid ]
do
g++ -std=c++17 gen.cpp -o a && ./a > in
g++ -std=c++17 B.cpp -o a && ./a < in
g++ -std=c++17 B2.cpp -o a && ./a < in
if [ $count -eq 10 ];
then
break
fi
((count++))
done