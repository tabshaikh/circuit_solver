# AC Circuit Solver
This is a AC circuit solver program. It draws a SVG image of the circuit given as input in the *top.cir* file. To see this file in the browser, you can open *Circuit.html*. Please read the caution and guidelines to run the program.  
The Solved values of the components are saved in the file *result.txt*. ALso you can see the solved values of each components by clicking the svg. This will open a new tab showing the detailed values of that components.

## Running the code.
**To clean the previous output file and logs.**

```
make clean
```

**To run the program.** make execute input = /path_to_file
> For example

```
make execute input = top.cir
```

**To run the test cases**

```
make debug
```

## Rules for the Input File.
1. The input is not case-sensitive.
2. Every token should be followed by a space for the scanner to identify it.
3. Every line should contain only a single instruction.
4. The format of a instruction is:-
- Component like resistor, capacitor and inductor  
    <TYPE_NUMBER> <STARTING_NET> <ENDING_NET> <VALUE>
- Components like voltage source and current source  
    <TYPE_NUMBER> <STARTING_NET> <ENDING_NET> SINE ( <DC_OFFSET> <AMPLITUDE> <FREQENCY> <DELAY> <DAMPING_FACTOR> )

```
R1 NET2 NET3 2.2Kohm  
C1 NET3 0 1UF  
L1 Net1 Net2 10NH  
V1 Net1 0 SINE ( 0.0 1.0 10Khz 0.0S 0.0 )
```
5. Units for every component is necessary.  
    - Resistor    --> ohm  
    - Capacitor   --> F  
    - Inductor    --> H  
    - Frequency   --> khz  
6. Units extensions are availble like:-  
    - K   for kilo  
    - M   for mili  
    - N   for nano  
    - P   for pico  
    - U   for micro  

## Dependencies
- We are using firefox to open the SVG. Make sure that firefox is installed and updated.
- Install armadillo, LAPACK and BLAS.
### To install armadillo, LAPACK and BLAS
- Install LAPACK and BLAS via the folllowing insttruction:-
```
sudo apt-get install liblapack-dev
sudo apt-get install libblas-dev
```
- Download Armadillo from http://arma.sourceforge.net/download.html
- Extract the downloaded files into some directory.
Open a terminal window, change into the directory that was created
  by unpacking the armadillo archive, and type the following commands:
  ```
  cmake .
  make 
  ```
  The full stop separated from "cmake" by a space is important.
  CMake will detect which relevant libraries are installed on your system
  (eg. OpenBLAS, LAPACK, SuperLU, ARPACK, etc)
  and will modify Armadillo's configuration correspondingly.
  CMake will also generate a run-time armadillo library,
  which is a wrapper for all the detected libraries.  
If you have access to root/administrator/superuser privileges
  (ie. able to use "sudo"), type the following command:
  ```
  sudo make install
  ```
  If you don't have root/administrator/superuser privileges, 
  type the following command:
  ```
  make install DESTDIR=my_directory
  ```
  where "my_directory" is an alternative directory for storing
  C++ headers and library files.

## Caution
1. Some errors are faced using chrome to open the Circuit.html as chrome browser shows only one frame at a time.(prefer only mozilla)
2. If Mozilla Firefox failed to zoom the image, please do hard reset ( Ctrl + Shift + R ) or reload the frame.
3. Please ensure that you have flash player extension enabled in Mozilla.
4. Sometimes there can error in which thunbnail fails to work, just keep on trying hard reset for that.