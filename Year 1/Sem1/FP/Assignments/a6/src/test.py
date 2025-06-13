from functions import *
# Test check_validity
def testing():
    assert check_validity(5, 3) == True
    assert check_validity(0, -10) == True
    try:
        check_validity("a", 2)
    except ValueError:
        assert True

    # Test create_number
    assert create_number(5, 3) == [5, 3]
    assert create_number(0, 0) == [0, 0]
    assert create_number(-10, 20) == [-10, 20]

    # Test get_real
    assert get_real([5, 3]) == 5
    assert get_real([0, -10]) == 0
    assert get_real([-20, 15]) == -20

    # Test get_imaginary
    assert get_imaginary([5, 3]) == 3
    assert get_imaginary([0, -10]) == -10
    assert get_imaginary([-20, 15]) == 15

    # Test set_real
    assert set_real([5, 3], 10) == [10, 3]
    assert set_real([0, -10], -15) == [-15, -10]
    assert set_real([-20, 15], 0) == [0, 15]

    # Test set_imaginary
    assert set_imaginary([5, 3], 10) == [5, 10]
    assert set_imaginary([0, -10], -15) == [0, -15]
    assert set_imaginary([-20, 15], 0) == [-20, 0]

    # Test generate_numbers
    numbers = generate_numbers()
    assert len(numbers) == 10
    assert all(isinstance(num, list) and len(num) == 2 for num in numbers)

    # Test add_number
    numbers = [[1, 1], [2, 2]]
    assert add_number(numbers, 3, 3) == [[1, 1], [2, 2], [3, 3]]
    assert add_number(numbers, -4, 5) == [[1, 1], [2, 2], [3, 3], [-4, 5]]
    assert add_number(numbers, 0, 0) == [[1, 1], [2, 2], [3, 3], [-4, 5], [0, 0]]

    # Test insert_number
    numbers = [[1, 1], [2, 2]]
    assert insert_number(numbers, 3, 3, 1) == [[1, 1], [3, 3], [2, 2]]
    assert insert_number(numbers, -4, 5, 0) == [[-4, 5], [1, 1], [3, 3], [2, 2]]
    assert insert_number(numbers, 0, 0, 3) == [[-4, 5], [1, 1], [3, 3], [0, 0], [2, 2]]

    # Test remove_number_position
    numbers = [[1, 1], [2, 2], [3, 3]]
    assert remove_number_position(numbers, 1) == [[1, 1], [3, 3]]
    assert remove_number_position(numbers, 0) == [[2, 2], [3, 3]]
    assert remove_number_position(numbers, 2) == [[1, 1], [2, 2]]

    # Test remove_number_interval
    numbers = [[1, 1], [2, 2], [3, 3], [4, 4]]
    assert remove_number_interval(numbers, 1, 2) == [[1, 1], [4, 4]]
    assert remove_number_interval(numbers, 0, 1) == [[3, 3], [4, 4]]
    assert remove_number_interval(numbers, 2, 3) == [[1, 1], [2, 2]]

    # Test replace_number
    numbers = [[1, 1], [2, 2], [3, 3]]
    assert replace_number(numbers, [2, 2], 4, 4) == [[1, 1], [4, 4], [3, 3]]
    assert replace_number(numbers, [1, 1], 0, 0) == [[0, 0], [4, 4], [3, 3]]
    assert replace_number(numbers, [3, 3], -1, -1) == [[0, 0], [4, 4], [-1, -1]]

    # Test list_real_range
    numbers = [[1, 0], [2, 2], [3, 0], [4, 0]]
    assert list_real_range(numbers, 0, 2) == format_table([[1, 0], [3, 0]])
    assert list_real_range(numbers, 1, 3) == format_table([[3, 0], [4, 0]])
    assert list_real_range(numbers, 0, 3) == format_table([[1, 0], [3, 0], [4, 0]])

    # Test list_modulo
    numbers = [[3, 4], [5, 12], [8, 15]]
    assert list_modulo(numbers, "<", 13) == format_table([[3, 4]])
    assert list_modulo(numbers, "=", 13) == format_table([[5, 12]])
    assert list_modulo(numbers, ">", 13) == format_table([[8, 15]])


