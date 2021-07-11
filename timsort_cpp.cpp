#include "Python.h"
#include "iostream"
#include "vector"

const int RUN = 64;

void insertion_sort(int arr[], long left, long right){
    for (long i=1+left; i<right; i++)
        for (long j=i; j>left && arr[j-1] > arr[j]; j--)
            std::swap(arr[j-1], arr[j]);
}

void merge(int arr[], long begin, long mid, long n){
    std::vector<int> subarr_merged;
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

static PyObject* sorted(PyObject* self, PyObject* args){
    //Python List to C Array and get n
    PyObject* pList;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &pList)){
        PyErr_SetString(PyExc_TypeError, " parameter must be a list.");
        Py_RETURN_NONE;
    }

    Py_ssize_t Py_n = PyList_Size(pList);
    long n = (long)Py_n;

    int* arr = new int[n];
    for (long i=0; i<n; i++){
        PyObject* pItem = PyList_GetItem(pList, i);
        arr[i] = PyLong_AsLong(pItem);
    }

    //timsort
    for (long l = 0; l<n; l+=RUN){
        long r = std::min(l+RUN, n);
        insertion_sort(arr, l, r);
    }

    for (long size=RUN; size<n; size*=2)
        for (long l=0; l<n; l+=2*size){
            long mid = l+size;
            long r = std::min(l+2*size, n);

            if(mid < r)
                merge(arr, l, mid, r);
        }

    //C Array to Python List
    PyObject* list = PyList_New(n);
    for (int i=0; i<n; i++)
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