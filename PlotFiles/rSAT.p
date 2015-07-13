      set   autoscale                        # scale axes automatically
      #set logscale y                           # remove any log-scaling
      unset label  
      unset log                          # remove any previous labels
      set xtic auto                        # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Running time of SAT solver vs Number of Vertices (Without log Sclae)"
      set xlabel "Number of Vertices"
      set ylabel "Running time(seconds)"
      set key bottom
      set xr [4:16]
      set yr [0.000300:10]
      plot    "runtime.dat" using 1:2 title 'CNF-SAT-VC' with linespoints, \
              "runtime.dat" using 1:2:7 title 'Standard deviation SAT' with yerrorbars
               
