      set   autoscale                        # scale axes automatically
     # set logscale y                           # remove any log-scaling
      unset label  
      unset log                          # remove any previous labels
      set xtic auto                        # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Approximation Ratio of Four Different Approaches vs Number of Vertices"
      set xlabel "Number of Vertices"
      set ylabel "Approximation Ratio"
      set key bottom
      set xr [4:16]
      set yr [0:3]
      plot    "runappr.dat" using 1:2 title 'Approx-VC-1' with linespoints, \
              "runappr.dat" using 1:2:6 title 'STD Approx-VC-1' with yerrorbars, \
               "runappr.dat" using 1:3 title 'Refined Approx-VC-1' with linespoints, \
              "runappr.dat" using 1:3:7 title 'STD Refined Approx-VC-1' with yerrorbars, \
	      "runappr.dat" using 1:4 title 'Approx-VC-2' with linespoints, \
              "runappr.dat" using 1:4:8 title 'STD Approx-VC-2' with yerrorbars, \
               "runappr.dat" using 1:5 title 'Refined Approx-VC-2' with linespoints, \
              "runappr.dat" using 1:5:9 title 'STD Refined Approx-VC-2' with yerrorbars
