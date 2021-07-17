#include "Python.h"
#include "iostream"
#include "vector"

void insertion_sort(long arr[], long left, long right){
    for (long i=1+left; i<right; i++)
        for (long j=i; j>left && arr[j-1] > arr[j]; j--)
            std::swap(arr[j-1], arr[j]);
}

void merge(long arr[], long begin, long mid, long n){
    std::vector<long> subarr_merged;
    subarr_merged.reserve(n-begin);

    long l = begin;
    long r = mid;

    while (l<mid && r<n){
        if (arr[l] < arr[r]){
            subarr_merged.push_back(arr[l]);
            l++;
        }
        else{
            subarr_merged.push_back(arr[r]);
            r++;
        }
    }
    for(; l<mid; l++) subarr_merged.push_back(arr[l]);
    for(; r<n;   r++) subarr_merged.push_back(arr[r]);

    std::copy(subarr_merged.begin(), subarr_merged.end(), &arr[begin]);
}

//Function extracted from Python source code
long get_minrun(long n){
    long r = 0;

    while (n >= 64){
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

static PyObject* sorted(PyObject* self, PyObject* args){
    //Python List to C Array and get n
    PyObject* pList;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)){
        PyErr_SetString(PyExc_TypeError, " parameter must be a list.");
        Py_RETURN_NONE;
    }

    Py_ssize_t Py_n = PyList_Size(pList);
    long n = (long)Py_n;

    long* arr = new long[n];
    for (long i=0; i<n; i++){
        PyObject* pItem = PyList_GetItem(pList, i);
        arr[i] = PyLong_AsLong(pItem);
    }

    //timsort
    long run = get_minrun(n);
    for (long l = 0; l<n; l+=run){
        long r = std::min(l+run, n);
        insertion_sort(arr, l, r);
    }

    for (long size=run; size<n; size*=2)
        for (long l=0; l<n; l+=2*size){
            long mid = l+size;
            long r = std::min(l+2*size, n);

            if(mid < r)
                merge(arr, l, mid, r);
        }

    //C Array to Python List
    PyObject* list = PyList_New(n);
    for (long i=0; i<n; i++)
        PyList_SET_ITEM(list, i, PyLong_FromLong(arr[i]));

    delete[] arr;
    arr = NULL;

    return list;
}

static PyMethodDef methods[] = {
    {"sorted", sorted, METH_VARARGS, "Timsort method"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT, "timsort", "Timsort implemented in c", -1, methods
};

PyMODINIT_FUNC PyInit_timsort_cpp(void){
    return PyModule_Create(&module);
}