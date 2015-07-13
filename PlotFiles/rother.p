      set   autoscale                        # scale axes automatically
      #set logscale y                           # remove any log-scaling
      unset label  
       unset log                          # remove any previous labels
      set xtic auto                        # set xtics automatically
      set ytic auto                          # set ytics automatically
      set title "Running time of other approaches vs Number of Vertices"
      set xlabel "Number of Vertices"
      set ylabel "Running time(seconds)"
      set key bottom
      set xr [4:16]
      set yr [0.000020:0.000100]
      plot    "runtime.dat" using 1:3 title 'Approx-VC-1' with linespoints, \
              "runtime.dat" using 1:3:8 title 'STD Approx-VC-1' with yerrorbars, \
               "runtime.dat" using 1:4 title 'Refined Approx-VC-1' with linespoints, \
              "runtime.dat" using 1:4:9 title 'STD Refined Approx-VC-1' with yerrorbars, \
	      "runtime.dat" using 1:5 title 'Approx-VC-2' with linespoints, \
              "runtime.dat" using 1:5:10 title 'STD Approx-VC-2' with yerrorbars, \
               "runtime.dat" using 1:6 title 'Refined Approx-VC-2' with linespoints, \
              "runtime.dat" using 1:6:11 title 'STD Refined Approx-VC-2' with yerrorbars
