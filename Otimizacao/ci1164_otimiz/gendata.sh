#!/bin/bash

CMD_DIR=`dirname $0`

PROG=${1:-matmult}
tipo=${2:-avx}
CPU=${3:-3}

DATA_DIR="resultados/${PROG}"
TEMPOS="${DATA_DIR}/Tempos.csv"

METRICA="FLOPS_DP L3CACHE ENERGY"

TAMANHOS="64 100 128 170 256 350 512 1024 1900 2048 3000" # 2048 3000 4096 6000 7000 10000 50000 60000 70000 100000"

mkdir -p ${DATA_DIR}

likwid-setFrequencies -g performance -c ${CPU}

make purge ${tipo} 

for m in ${METRICA}
do
    LIKWID_LOG="${DATA_DIR}/${m}_${tipo}.log"
    rm -f ${TEMPOS}
    rm -f ${LIKWID_LOG}
    
    for n in $TAMANHOS
    do
	LIKWID_OUT="${DATA_DIR}/${m}_${tipo}_${n}.txt"
	
	echo "--->>  $m: ./${PROG} $n" >/dev/tty
	# Assume que programa 'matmult' imprime em stdout (via printf) os valores de tempo
	# medidos para cada função com 5 colunas: N, t_matVet, t_matVet_otim, t_matMat, t_matmat_otim
	likwid-perfctr -O -C ${CPU} -g ${m} -o ${LIKWID_OUT} -m ./${PROG} ${n} >>${TEMPOS}
	    
	# echo "===> N: ${n} <==" >> ${LIKWID_LOG}
	cat ${LIKWID_OUT} >> ${LIKWID_LOG}
	rm -f ${LIKWID_OUT}
    done

    # Colocar aqui comando(s) que, a partir dos arquivos '.txt', gera (para cada métrica) um arquivo
    # CSV com 5 colunas:
    # N, metrica_matvet,metrica_matvet_otim, metrica_matmat, metrica_matmat_otim
    #
    ${CMD_DIR}/genplot.py < ${LIKWID_LOG} > ${LIKWID_LOG%%.log}.csv
done

likwid-setFrequencies -g powersave -c ${CPU}

echo ""
echo ""
