#!/bin/bash

# Generar 50 números aleatorios
for ((i=0; i<50; i++))
do
  echo -n "$RANDOM "
done | xargs ./push_swap
