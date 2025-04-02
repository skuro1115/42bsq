#!/bin/sh

# XXX と YYY の範囲を指定
start_X=100
end_X=101
start_Y=1000
end_Y=1001

# XXX と YYY の組み合わせでループ
for XXX in $(seq $start_X $end_X); do
  for YYY in $(seq $start_Y $end_Y); do
    echo "Running: perl map_gen.pl $XXX $YYY 2 | valgrind --leak-check=full --show-leak-kinds=all -q ./bsq"
    perl map_gen.pl $XXX $YYY 2 | valgrind --leak-check=full --show-leak-kinds=all -q ./bsq
  done
done
