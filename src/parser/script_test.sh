#!/bin/bash

RELATIVE_PATH="../../maps"

clear
make &> /dev/null
echo "Caso 00: Programa solo, sin argumentos"
./cub3D
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

echo "Caso 01: Con múltiples argumentos"
./cub3D multiples argumentos
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D multiples argumentos
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

echo "Caso 02: Con argumento inválido: un argumento no .cub"
./cub3D map.txt
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D map.txt
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/nonexist.cub"
echo "Caso 03: Con argumento inválido: mal path"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/04.cub"
echo "Caso 04: Archivo vacío"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/05.cub"
echo "Caso 05: Parámetro de textura faltante"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/06.cub"
echo "Caso 06: Parámetro de textura repetido"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/07.cub"
echo "Caso 07: Ruta de textura no declarada"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/08.cub"
echo "Caso 08: Textura no es un .xpm"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/09.cub"
echo "Caso 09: Ruta de textura inválida"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/10.cub"
echo "Caso 10: Parámetro RGB faltante"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/11.cub"
echo "Caso 11: Parámetro RGB repetido"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/12.cub"
echo "Caso 12: Valor/es RGB no declarado/os"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/13.cub"
echo "Caso 13: Valor/es RGB fuera de rango"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/14.cub"
echo "Caso 14: Carácter inválido en los valores RGB"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/15.cub"
echo "Caso 15: Mapa inexistente"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/16.cub"
echo "Caso 16: Mapa abierto"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/17.cub"
echo "Caso 17: Mapa sin jugador"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/18.cub"
echo "Caso 18: Mapa con múltiples jugadores"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/19.cub"
echo "Caso 19: Mapa con caracteres inválidos"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/20.cub"
echo "Caso 20: Mapa cortado con saltos de línea"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/21.cub"
echo "Caso 21: Mapa no es el último parámetro"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

MAP_PATH="$RELATIVE_PATH/22.cub"
echo "Caso 22: TODO BIEN"
./cub3D $MAP_PATH
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./cub3D $MAP_PATH
if cat valgrind-out.txt | grep -q "no leaks are possible"; then
    echo -e "\e[32mNO LEAKS\e[0m"
else
    echo -e "\e[31mLEAKS FOUND\e[0m"
	cat valgrind-out.txt
fi

rm valgrind-out.txt
make fclean &> /dev/null