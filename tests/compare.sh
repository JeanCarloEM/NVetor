#!/bin/bash

#
# FAZ QUATRO TESTES
# UM PARA     1000 ITEMS
# UM PARA   100000 ITEMS
# UM PARA  1000000 ITEMS
# UM PARA 10000000 ITEMS
#
for g in `seq 0 3`;
do
  param="";
  prefix="1M"

  if [ "$g" -eq "1" ]
  then
    param=" 1"
    prefix="100M"
  else
    if [ "$g" -eq "2" ]
    then
      param=" 1 1"
      prefix="1000M"
    else
      if [ "$g" -eq "3" ]
      then
        param=" 1 1 1"
        prefix="10000M"
      fi
    fi
  fi

  #
  # EXECUTANDO 3 VEZES SEGUIDAS COMPILACAO NORMAL - O0
  #
  rm main
  g++ -std=c++11 main.cpp -o main  

  for i in `seq 1 3`;
  do
    ./main $prefix-O0-$i.csv$param
  done

  #
  # EXECUTANDO 3 VEZES SEGUIDAS COMPILACAO O1
  #
  rm main
  g++ -std=c++11 -o1 main.cpp -o main

  for i in `seq 1 3`;
  do
    ./main $prefix-O1-$i.csv$param
  done

  #
  # EXECUTANDO 3 VEZES SEGUIDAS COMPILACAO O2
  #
  rm main
  g++ -std=c++11 -O2 main.cpp -o main

  for i in `seq 1 3`;
  do
    ./main $prefix-o2-$i.csv$param
  done

  #
  # EXECUTANDO 3 VEZES SEGUIDAS COMPILACAO O3
  #
  rm main
  g++ -std=c++11 -O3 main.cpp -o main

  for i in `seq 1 3`;
  do
    ./main $prefix-o3-$i.csv$param
  done
done