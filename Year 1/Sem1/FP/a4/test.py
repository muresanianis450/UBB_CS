from iterative_approach import *
from naive_approach import naive_function
from dynamic_programming import dynamic_function


def test_functions():
    assert has_repeated_subsequence([1, 2, 1, 2]) == True, "Failed on input [1, 2, 1, 2]"
    assert has_repeated_subsequence([1, 2, 3, 4]) == False, "Failed on input [1, 2, 3, 4]"
    assert has_repeated_subsequence([0, 0, 0, 0]) == True, "Failed on input [0, 0, 0, 0]"
    assert has_repeated_subsequence([1, 1, 2, 3, 1, 2]) == True

    assert consistent([1, 2, 3]) == True, "Failed on input [1, 2, 3]"
    assert consistent([1, 2, 1, 2]) == False, "Failed on input [1, 2, 1, 2]"
    assert consistent([0, 2, 3]) == False, "Failed on input [0, 2, 3]"

    assert solution([1, 2, 3, 4], 4) == True
    assert solution([1, 2, 3], 4) == False

    assert naive_function( [3, 5, 8, 9, 10, 17, 17, 20], 8,8) == 24
    assert naive_function( [2, 2, 2, 2, 2, 2, 2],  7, 7) == 14
    assert naive_function( [0, 0, 0, 0],  4,4) == 0
    assert naive_function([1],1,1) == 1

    assert dynamic_function([3, 5, 8, 9, 10, 17, 17, 20], 8) == 24
    assert dynamic_function([2, 2, 2, 2, 2, 2, 2], 7) == 14
    assert dynamic_function([0, 0, 0, 0], 4) == 0
    assert dynamic_function([1],1) == 1






