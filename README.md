# Performance gain in Python
Interpreted language will never match the performance of compiled languages. But what happens if we combine these two worlds? To gauge performance benefits we can extend Python with c/c++.  

The timsort algorithm has been implemented for testing. It is used by the standard Python sorted().  

There are four implementations that will be executed by the Python interpreter:
- **Python**: The algorithm is implemented purely in Python.
- **Cython**: Although we can use c declarations, purely python code has been used. This is translated into c and compiled.
- **C++**: The algorithm is implemented purely in c++. With the Python.h header we extend the code. This is compiled.
- **Python built-in function**: It is the standard Python algorithm. It is implemented in c.

The results are:

```
TIME IN MS TO SORT A PYTHON LIST

Nº items|       python          cython          c++             built-in
--------------------------------------------------------------------------------
1024    |       5.984           2.996           0.000           0.000
2048    |       13.952          5.983           0.000           0.000
4096    |       28.893          12.994          0.000           0.995
8192    |       57.878          27.919          1.024           1.025
16384   |       119.679         56.850          1.995           2.992
32768   |       253.323         119.709         2.993           5.984
65536   |       541.631         282.173         7.978           21.953
131072  |       1205.288        607.764         17.979          54.819
262144  |       2574.034        1391.209        41.917          120.673
524288  |       5995.790        3179.805        81.294          252.359
1048576 |       12459.218       7004.614        183.057         647.273
2097152 |       26984.776       14037.816       371.007         1388.636

PERFORMANCE GAIN WITH TIMSORT WITH DIFFERENTS IMPLEMENTATIONS COMPARED TO PYTHON

                        |       python          cython          c++             built-in
------------------------------------------------------------------------------------------------
Nº times faster mean    |       1.000           2.016           68.003          29.825
```

We can see a big performance gain.  
Cython is twice as fast as Python even with the same code, this is due to compilation.  
My c++ implementation is faster than the built-in python implementation, this is because my implementation is very simple and does not keep in mind things like other data types, incorrect data, the sort key, etc.

---

## How to use it
### Running from source code
Tested with MinGW GCC and Python-32 3.7.4 in Windows Powershell

```
# Clone project
git clone https://github.com/JavideSs/Performance-gain-in-python.git
cd Performance-gain-in-python

# Build .cpp and .pyx
python setup.py build

#Copy .pyd
cp build\*\timsort_cpp.*.pyd .
cp build\*\timsort_cython.*.pyd .

# Run the peformance comparison program
python main.py
```
---

## Feedback
Your feedback is most welcomed by filling a
[new issue](https://github.com/JavideSs/Sudoku-Generator-Checker-Solver/issues/new).

---

Author:  
Javier Mellado Sánchez  
2021