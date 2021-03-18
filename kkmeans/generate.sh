#!/bin/bash

for ((i = 0 ; i < 1000 ; i++)); do
  x=$(echo $(( $RANDOM % 1001 - 500 )))
  y=$(echo $(( $RANDOM % 1001 - 500 )))
  cat >> stars.csv << EOF
$x;$y
EOF
done
