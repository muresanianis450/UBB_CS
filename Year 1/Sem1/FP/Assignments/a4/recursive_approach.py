def has_repeated_subsequence(x):
    """
    Check if there are any consecutive identical subsequences in x.
    """

    length = len(x)
    for size in range(1, length // 2 + 1):
        for start in range(length - 2 * size + 1):
            # comparing sequences from start-> start+size and start+size -> start+ 2
            if x[start:start + size] == x[start + size:start + 2 * size]:
                return True
    return False


def consistent(x):
    """
    Determines whether the current partial array x has no identical subsequences anywhere.
    """

    #we cannot have 0 as first digit in the number
    if x and x[0] == 0:
        return False

    return not has_repeated_subsequence(x)


def solution(x, n):
    """
    Determines whether we have a solution when x has n digits.
    """
    return len(x) == n


def solution_found(x):
    """
    Action to take when a solution is found.
    """
    # Using list comprehension
    print("Solution:", ''.join([str(i) for i in x]))


def bkt_rec(x, n, digits=range(10)):
    """
    Backtracking algorithm to generate n-digit numbers with no identical subsequences neighbors.
    """
    if len(x) == n:
        solution_found(x)
        return

    for i in digits:
        x.append(i)
        if consistent(x):
            #if the list is consistent then i go into the recursion until i find
            #a solution or my solution is inconsistent
            bkt_rec(x, n, digits)
        #after the recursive calls are over, i delete the value placed on the array
        x.pop()

