def insertion_sort(arr, left, right):
    for i in range(1+left, right):
        j=i
        while j>left and arr[j-1] > arr[j]:
            arr[j-1], arr[j] = arr[j], arr[j-1]
            j-=1

def merge(arr, begin, mid, n):
    subarr_merged = []

    l = begin
    r = mid

    while(l<mid and r<n):
        if arr[l] < arr[r]:
            subarr_merged.append(arr[l])
            l+=1
        else:
            subarr_merged.append(arr[r])
            r+=1
    for l in range(l, mid):
        subarr_merged.append(arr[l])
    for r in range(r, n):
        subarr_merged.append(arr[r])

    for i in range(len(subarr_merged)):
        arr[begin+i] = subarr_merged[i]

def get_minrun(n):
    r = 0

    while (n >= 64):
        r |= n & 1
        n >>= 1
    return n + r

def sorted(arr):
    n = len(arr)
    arr = arr.copy()

    run = get_minrun(n)
    for l in range(0,n,run):
        r = min(l+run, n)
        insertion_sort(arr, l, r)

    size=run
    while size<n:
        for l in range(0,n,2*size):
            mid = l+size
            r = min(l+2*size, n)

            if mid < r:
                merge(arr, l, mid, r)
        size*=2

    return arr