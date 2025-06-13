import random
import math
from SortAlgorithmsTesting import *
from time_complexity import *
from Testing import testing_list


# ok = True
# rand_list = []

# Function to generate a random list
def generate_list(n: int):
    global rand_list
    rand_list = [random.randint(0, 1000) for _ in range(n)]
    return rand_list


# Menu function to display options
def menu():
    print("What would you like to do with the list?:")
    print("1. Generate a new list")
    print("2. Search for an item in the list")
    print("3. Sort the list using Insertion sort")
    print("4. Sort the list using Stooge Sort")
    print("5. Best case for the implemented algorithms: ")
    print("6. Average case for the implemented algorithms: ")
    print("7. Worst case for the implemented algorithms: ")
    print("0. Exit")


def Jump_search(rand_list, x, n):
    step = math.sqrt(n)
    prev = 0
    # searching the first position a number is greater than x so that we know the end of the liniar interval
    while rand_list[int(min(step, n) - 1)] < x:
        prev = step
        step += math.sqrt(n)
        if prev >= n:
            return -1
    # liniar search from the last number smaller than x to the first number which is greater than x
    # arr[prev] < x < arr[step]
    while rand_list[int(prev)] < x:
        prev = prev + 1
        if prev == min(step, n):
            return -1

    if rand_list[int(prev)] == x:
        return int(prev)

    return -1


# Insertion sort function
def Insertion_sort_pas(arr, n: int, pas: int):  # Insertion Sort with pas for the sorting and demonstration purposes
    if n <= 1:
        return
    knt = 0

    for i in range(1, n):
        if knt == pas:
            print(arr)
            knt = 0
        else:
            knt += 1
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

        if knt == pas:
            print(arr)
            knt = 0
        else:
            knt += 1
    return arr


def Insertion_sort(arr, n):  # Insertion Sort without pas, for the searching algorithm
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr


def is_sorted(rand_list, n):
    if n <= 1:
        return True
    for i in range(n - 1):
        if rand_list[i] > rand_list[i + 1]:
            return False
    return True


def Stooge_sort_pas(arr, l, h, pas: int, knt: int):
    if l >= h:
        return
    if len(arr) == 1:
        return arr[0]

    if knt == pas:
        print(arr)
        knt = 0

    if arr[l] > arr[h]:
        arr[l], arr[h] = arr[h], arr[l]

    if h - l + 1 > 2:
        t = (h - l + 1) // 3

        Stooge_sort_pas(arr, l, h - t, pas, knt + 1)
        Stooge_sort_pas(arr, l + t, h, pas, knt + 1)
        Stooge_sort_pas(arr, l, h - t, pas, knt + 1)

    return arr


def Stooge_sort(arr, l, h):  # stooge sort for the search algorithm
    if len(arr) == 0:
        return []
    if len(arr) == 1:
        return arr
    if l >= h:
        return
    if arr[l] > arr[h]:
        arr[l], arr[h] = arr[h], arr[l]

    # If there are more than 2 elements
    if h - l + 1 > 2:
        t = (int)((h - l + 1) / 3)

        Stooge_sort(arr, l, h - t)
        Stooge_sort(arr, l + t, h)
        Stooge_sort(arr, l, h - t)

        return arr


# Main loop for menu interaction
def main():
    ok = True
    rand_list = []
    while ok:
        if len(rand_list) == 0:
            print("You must build your list, please enter the number of items it should contain ")
            number = input()
            try:
                number = int(number)
                if number <= 0:
                    raise ValueError
                rand_list = generate_list(number)
                print("Generated List: ", rand_list)
            except ValueError:
                print("Invalid input, please enter a valid number ")
        else:
            menu()
            choice = input("Enter your choice: ")
            try:
                choice = int(choice)
            except ValueError:
                print("Invalid input. Please enter a number between 0 and 4.")
                continue

            match choice:
                case 1:
                    number = input("Choose the size of the random list: ")
                    try:
                        n = int(number)
                        rand_list = generate_list(n)
                        print(rand_list)
                    except ValueError:
                        print("Please enter a natural number")

                case 2:
                    if not is_sorted(rand_list, len(rand_list)):
                        print("The list must be sorted first before the search can occur.")
                        print("Which sorting algorithm would you like to use?:")
                        print("1. Insertion sort")
                        print("2. Stooge sort")
                        sorting_method = input()
                        try:
                            sorting_method = sorting_method.strip().lower()
                            match sorting_method:
                                case "insertion sort":
                                    rand_list = Insertion_sort(rand_list, len(rand_list))
                                    print("Your list is:", rand_list)

                                case "stooge sort":
                                    Stooge_sort(rand_list, 0, len(rand_list) - 1)
                                    print("Your list is:", rand_list)

                                case _:
                                    raise TypeError("Invalid sorting method name.")
                        except ValueError:
                            print("Please insert the correct name of the sorting algorithm.")
                    else:
                        print("Your list is:", rand_list)
                    print("Which number would you like to search with jump search?:  ")
                    number = input()
                    try:
                        number = int(number)
                        position = Jump_search(rand_list, number, len(rand_list) - 1)
                        if position == -1:
                            print("This number is not in the list.")
                        else:
                            print("Your number is the", int(position) + 1, "element in the list")
                    except ValueError:
                        print("Please enter a number")

                case 3:
                    pas = input(
                        "Please enter the frequency you want the process of the sorting algorithm to be shown: ")
                    try:
                        pas = int(pas)
                        rand_list = Insertion_sort_pas(rand_list, len(rand_list), pas)
                    except ValueError:
                        print("Please insert a natural number for the frequency.")

                case 4:
                    pas = input(
                        "Please enter the frequency you want the process of the sorting algorithm to be shown: ")
                    try:
                        pas = int(pas)
                        rand_list = Stooge_sort_pas(rand_list, 0, len(rand_list) - 1, pas, 0)
                    except ValueError:
                        print("Please insert a natural number for the frequency.")
                case 5:
                    best_case()

                case 6:
                    average_case()
                case 7:
                    worst_case()
                case 0:
                    ok = False
                    print("Exiting...")
                    break

                case _:
                    print("Please enter one of the shown numbers.")


if __name__ == "__main__":
    testing_list()
    main()
