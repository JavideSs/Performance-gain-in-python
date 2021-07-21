import timsort_py
import timsort_cython
import timsort_cpp

import time, random

def timing(func):
    def wrap(*args, **kwargs):
        time0 = time.time()
        ret = func(*args, **kwargs)
        timet = time.time() - time0
        return ret, timet
    return wrap

@timing
def do_sorted(func, arr):
    return func(arr)

def check_sorted(arr, sorted_arr):
    has_same_items = set(arr) == set(sorted_arr)
    is_sorted = all(sorted_arr[i] <= sorted_arr[i+1] for i in range(len(sorted_arr)-1))
    return has_same_items and is_sorted

implementations = {
    "python": (timsort_py.sorted, []),
    "cython": (timsort_cython.sorted, []),
    "c++": (timsort_cpp.sorted, []),
    "built-in": (sorted, []),
}

#_________________________________________________________________________________________________

print("\nTIME IN MS TO SORT A PYTHON LIST", end="\n\n")
print("Nº items", end="|\t")
for implementation in implementations:
    print(implementation, end="\t\t" if len(implementation)<8 else "\t")
print("\n"+"-"*16*(len(implementations)+1))

for i in range(10,22):
    arr_len = 2**i
    arr = list(range(arr_len))
    random.shuffle(arr)

    print(arr_len, end="\t|\t", flush=True)

    for implementation in implementations:
        implementation_func = implementations[implementation][0]
        sorted_arr, timet = do_sorted(implementation_func, arr)

        if not check_sorted(arr, sorted_arr):
            print(f"Error in timsort with {implementation} implementation")
            exit()

        timet_ms = timet*1000
        implementations[implementation][1].append(timet_ms)
        print("{:.3f}".format(timet_ms), end="\t\t" if timet_ms<1000 else "\t", flush=True)

    print()

#_________________________________________________________________________________________________

print("\nPERFORMANCE GAIN WITH TIMSORT WITH DIFFERENTS IMPLEMENTATIONS COMPARED TO PYTHON", end="\n\n")
print("\t\t\t", end="|\t")
for implementation in implementations:
    print(implementation, end="\t\t" if len(implementation)<8 else "\t")
print("\n"+"-"*16*(len(implementations)+2))

print("Nº times faster mean", end="\t|\t")

for implementation in implementations:
    times_faster_acc = 0
    n_times_faster_undefined = 0
    for i, timet_python in enumerate(implementations["python"][1]):
        timet_implementation = implementations[implementation][1][i]

        if timet_implementation != 0:
            times_faster_acc += timet_python / timet_implementation
            n_times_faster_undefined+=1

    times_faster_mean = times_faster_acc / n_times_faster_undefined
    print("{:.3f}".format(times_faster_mean), end="\t\t" if times_faster_mean<1000 else "\t")

print("\n")