#!/bin/bash
# 26-04-2018
# alex
# ordre.sh

PAS=()
MET=()
PAS[0]=2000
PAS[1]=500
PAS[2]=200
PAS[3]=100
PAS[4]=50
PAS[5]=10
MET[0]="sb_6_4"
MET[1]="ss_5_4"
MET[2]="sa_5_4"



cd ..
mkdir .tmp_dat
for i in ${MET[@]} ; do
    for j in ${PAS[@]} ; do
	k=$(echo $i | cut -d'_' -f 1)
	l=$(echo $i | cut -d'_' -f 2-)
	echo "Execució de composicio (tipus = $k, coeficients = $l, h = $j)"
	./composicio $k $l $j >> .tmp_dat/$i.dat
    done
done
cd .tmp_dat

echo "reset" >> plot.plt
echo "set terminal pdf enhanced font 'Verdana, 10'" >> plot.plt
echo "set key font ',8'" >> plot.plt
echo "set xtics font 'Verdana,8'" >> plot.plt
echo "set output \"../graf/ordre.pdf\"" >> plot.plt
echo "set key out vert" >> plot.plt
echo "set key right" >> plot.plt
echo "set title \"Efficiency\"" >> plot.plt
echo "set ylabel \"log(max(H-H_0)/H_0)\"" >> plot.plt
echo "set xlabel \"log(N_{eval})\"" >> plot.plt
echo -n "plot " >> plot.plt
IT=0
for i in ${MET[@]} ; do
    k=$(echo $i | cut -d'_' -f 1 | tr [[:lower:]] [[:upper:]])
    l=$(echo $i | cut -d'_' -f 2)
    m=$(echo $i | cut -d'_' -f 3-)
    l="_$l^{[$m]}"
    echo -n "\"$i.dat\" u (log10(\$3)):(log10(\$4)) t \"$k$l\" w lp lw 2 ps 0.5 pt 2, " >> plot.plt
    let "IT++"
done
gnuplot plot.plt
rm plot.plt
cd ..
rm -rf .tmp_dat
