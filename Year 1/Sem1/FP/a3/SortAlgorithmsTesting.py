# sort_algorithms.py

def Insertion_sort(arr, n):
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr


def Stooge_sort(arr, l, h):
    if len(arr) == 0:
        return []
    if len(arr) == 1:
        return arr
    if l >= h:
        return
    if arr[l] > arr[h]:
        arr[l], arr[h] = arr[h], arr[l]

    if h - l + 1 > 2:
        t = ((h - l + 1) // 3)

        Stooge_sort(arr, l, h - t)
        Stooge_sort(arr, l + t, h)
        Stooge_sort(arr, l, h - t)

    return arr


def Jump_search(arr, x, n):
    if len(arr) == 1:
        if arr[0]==x:
            return 0
        else:
            return -1
    step = int(n ** 0.5)
    prev = 0

    while arr[min(step, n) - 1] < x:
        prev = step
        step += int(n ** 0.5)
        if prev >= n:
            return -1

    for i in range(prev, min(step, n)):
        if arr[i] == x:
            return i
    return -1