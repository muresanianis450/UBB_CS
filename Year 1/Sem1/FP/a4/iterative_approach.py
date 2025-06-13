from collections import deque
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
    # Ensure the first digit isn't 0 (if we don't want numbers to start with 0)
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
    print("Solution:", ''.join(str(i) for i in x))


def bkt_iter(n, digits=range(10)):
    """
    Iterative backtracking algorithm to generate n-digit numbers with no identical subsequences in ascending order.
    """
    queue = deque([([])])  # Use a deque for the queue to store partial sequences `x`

    while queue:
        x = queue.popleft()  # Dequeue the first element

        # Check if we have a complete solution
        if solution(x, n):
            solution_found(x)
            continue

        # Generate new states by adding each digit in `digits`
        for i in digits:
            #adding i to the list x
            new_x = x + [i]
            if consistent(new_x):
                queue.append(new_x)  # Enqueue the new state
