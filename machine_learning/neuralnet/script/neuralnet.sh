#!/bin/sh

#################
#run Neuralnet program
################
#params
BASEDIR=$(dirname $0)/..
PARAM=${BASEDIR}/prm/param.txt
BIN=${BASEDIR}/build-src-Desktop-Default/neuralnet
OUTDIR=${BASEDIR}/result
OUTIMGNAME=${OUTDIR}/error.png
LOGBASENAME=log.txt
NN_NUM=4

#run
cp $PARAM $OUTDIR
$BIN $PARAM

#plot
if [ ${NN_NUM} = 4 ]; then
gnuplot <<- EOF
set xlabel "iteration number"
set ylabel "cost J"
set grid
set term png
set output "$OUTIMGNAME"
plot "$OUTDIR/id0$LOGBASENAME" using 1:2 with l title "0th neuralnet", "$OUTDIR/id1$LOGBASENAME" using 1:2 with l title "1st neuralnet", "$OUTDIR/id2$LOGBASENAME" using 1:2 with l title "2nd neuralnet", "$OUTDIR/id3$LOGBASENAME" using 1:2 with l title "3rd neuralnet"
EOF
fi
