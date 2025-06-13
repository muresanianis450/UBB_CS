import timeit
import random

import texttable
from texttable import Texttable
from main import generate_list, Stooge_sort, Insertion_sort, Jump_search


def best_case():
    x = 10
    table = texttable.Texttable()
    table.set_precision(7)
    table.set_cols_align(["l", "r", "c"])
    table.set_cols_valign(["m", "m", "m"])
    table.add_row(["Size", "Sorting method", "Time complexity (ms)"])
    for i in range(5):
        arr = generate_list(x)
        time_stooge = timeit.timeit(lambda: Stooge_sort(arr, 0, len(arr) - 1), globals=globals(), number=1) * 1000
        arr.sort()
        time_insertion = timeit.timeit(lambda: Insertion_sort(arr, x), globals=globals(), number=1) * 1000
        time_jump = timeit.timeit(lambda: Jump_search(arr, arr[0], len(arr)), globals=globals(), number=1) * 1000
        table.add_row([x, "Stooge Sort", f"{time_stooge:.7f}"])
        table.add_row([x, "Insertion Sort", f"{time_insertion:.7f}"])
        table.add_row([x, "Jump Search", f"{time_jump:.7f}"])
        x *= 2
    print(table.draw())


def average_case():
    x = 10
    table = texttable.Texttable()
    table.set_precision(7)
    table.set_cols_align(["l", "r", "c"])
    table.set_cols_valign(["m", "m", "m"])
    table.add_row(["Size", "Sorting method", "Time complexity (ms)"])
    for i in range(5):
        arr = generate_list(x)
        time_stooge = timeit.timeit(lambda: Stooge_sort(arr, 0, x - 1), globals=globals(), number=1) * 1000
        time_insertion = timeit.timeit(lambda: Insertion_sort(arr, x), globals=globals(), number=1) * 1000
        arr.sort()

        # generate random index for the search algorithm

        random_number = random.randint(0, len(arr) - 1)
        time_jump = timeit.timeit(lambda: Jump_search(arr, arr[random_number], x - 1), globals=globals(),
                                  number=1) * 1000
        table.add_row([x, "Stooge Sort", f"{time_stooge:.7f}"])
        table.add_row([x, "Insertion Sort", f"{time_insertion:.7f}"])
        table.add_row([x, "Jump Search", f"{time_jump:.7f}"])
        x *= 2
    print(table.draw())


def worst_case():
    x = 10
    table = texttable.Texttable()
    table.set_precision(7)
    table.set_cols_align(["l", "r", "c"])
    table.set_cols_valign(["m", "m", "m"])
    table.add_row(["Size", "Sorting method", "Time complexity (ms)"])
    for i in range(5):
        arr = generate_list(x)
        time_insertion = timeit.timeit(lambda: Insertion_sort(arr, x), globals=globals(), number=1) * 1000
        arr.sort()
        time_stooge = timeit.timeit(lambda: Stooge_sort(arr, 0, x - 1), globals=globals(), number=1) * 1000
        time_jump = timeit.timeit(lambda: Jump_search(arr, arr[len(arr) - 1], x - 1), globals=globals(),
                                  number=1) * 1000
        table.add_row([x, "Stooge Sort", f"{time_stooge:.7f}"])
        table.add_row([x, "Insertion Sort", f"{time_insertion:.7f}"])
        table.add_row([x, "Jump Search", f"{time_jump:.7f}"])
        x *= 2
    print(table.draw())


if __name__ == '__main__':
    best_case()
