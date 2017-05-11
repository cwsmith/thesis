#Contents
iostream/ss.cc     - C++ iostream example
CMakeLists.txt     - 'build system'
rdtsc.c            - timer src
rdtsc.h            - timer header
README.md          - this file
stream_simple.c    - POSIX stream example without timers
stream.c           - POSIX stream example with timers

#C++ iostream
##build 
```
cd iostream
g++ ss.cc -o ss
```

##run
`./ss`

#POSIX C
##run stream_simple
```
./stream stream read 10000
./stream stream write 10000
...
```

##build stream on pachisi
```
module load intel
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=icc ../
make
```

##run stream
on pachisi there are 3998 cycles per microsecond
run ./stream without the last argument to compute cycles per microsecond

```
method=stream; mode=read; for((i=1;i<=10;i++)); do ./stream $method $mode $((i*10*1000*1000)) 3998; done &> ${method}${mode}.log
```

##create a plot of effective bandwidth
###extract
`for i in *log; do grep effective $i > $i.effective; done`

###gnuplot
```
set xlabel "Bytes"
set ylabel "MB/s"
p 'posixwrite.log.effective' u 2:9 w lines, 'streamwrite.log.effective' u 2:9 w lines, 'streamwriteprealloc.log.effective' u 2:9 w lines
p 'posixread.log.effective' u 2:9 w lines, 'streamread.log.effective' u 2:9 w lines, 'streamreadprealloc.log.effective' u 2:9  w lines
```

##run valgrind
```
valgrind ./stream stream read 10000 3998
valgrind ./stream stream readprealloc 10000 3998
valgrind ./stream stream write 10000 3998
valgrind ./stream stream writeprealloc 10000 3998
valgrind ./stream posix read 10000 3998
valgrind ./stream posix write 10000 3998
```
