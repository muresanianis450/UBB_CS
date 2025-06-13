from random import randint
from pdoc import pdoc
# Utility Functions
def check_validity(real_number, imaginary_number) -> bool:
    """
    Checks if the given real and imaginary parts are valid integers.
    :param real_number: The real part of the number.
    :param imaginary_number: The imaginary part of the number.
    :return: True if both parts are valid integers, otherwise raises a ValueError.
    """
    try:
        int(real_number)
        int(imaginary_number)
        return True
    except ValueError:
        raise ValueError("Please enter a valid number")


def create_number(real: int, imaginary: int) -> list:
    """
    Creates a complex number represented as [real, imaginary].
    :param real: The real part of the complex number.
    :param imaginary: The imaginary part of the complex number.
    :return: A list containing the real and imaginary parts.
    """
    return [real, imaginary]



# Getter and Setter Functions
def get_real(complex_number: list) -> int:
    """
    Retrieves the real part of a complex number.
    :param complex_number: A list representing the complex number.
    :return: The real part of the complex number.
    """
    return complex_number[0]

def get_imaginary(complex_number: list) -> int:
    """
    Retrieves the imaginary part of a complex number.
    :param complex_number: A list representing the complex number.
    :return: The imaginary part of the complex number.
    """
    return complex_number[1]




def set_real(complex_number: list, real: int) -> list:
    """
    Sets the real part of a complex number.
    :param complex_number: A list representing the complex number.
    :param real: The new real part to set.
    :return: The updated complex number.
    """
    complex_number[0] = real
    return complex_number


def set_imaginary(complex_number: list, imaginary: int) -> list:
    """
    Sets the imaginary part of a complex number.
    :param complex_number: A list representing the complex number.
    :param imaginary: The new imaginary part to set.
    :return: The updated complex number.
    """
    complex_number[1] = imaginary
    return complex_number


# Core Functionalities
def generate_numbers() -> list:
    """
    Generates a list of 10 random complex numbers.
    :return: A list of 10 complex numbers, each represented as [real, imaginary].
    """
    numbers_list = []
    for _ in range(10):
        real = randint(-50, 50)
        imaginary = randint(-50, 50)
        numbers_list.append(create_number(real, imaginary))
    return numbers_list


def add_number(numbers_list: list, real: int, imaginary: int) -> list:
    """
    Adds a new complex number to the list.
    :param numbers_list: The list of complex numbers.
    :param real: The real part of the new complex number.
    :param imaginary: The imaginary part of the new complex number.
    :return: The updated list of complex numbers.
    """
    new_number = create_number(real, imaginary)
    numbers_list.append(new_number)
    return numbers_list


def insert_number(numbers_list: list, real: int, imaginary: int, index: int) -> list:
    """
    Inserts a new complex number at a specified position in the list.
    :param numbers_list: The list of complex numbers.
    :param real: The real part of the new complex number.
    :param imaginary: The imaginary part of the new complex number.
    :param index: The position at which to insert the new complex number.
    :return: The updated list of complex numbers.
    :raises IndexError: If the index is out of range.
    """
    new_number = create_number(real, imaginary)
    if index < 0 or index > len(numbers_list):
        raise IndexError("Index out of range")
    numbers_list.insert(index, new_number)
    return numbers_list


def remove_number_position(numbers_list: list, index: int) -> list:
    """
    Removes the complex number at a specified position in the list.
    :param numbers_list: The list of complex numbers.
    :param index: The position of the complex number to remove.
    :return: The updated list of complex numbers.
    :raises IndexError: If the index is out of range.
    """
    if index < 0 or index >= len(numbers_list):
        raise IndexError("Index out of range")
    return numbers_list[:index] + numbers_list[index+1:]


def remove_number_interval(numbers_list: list, start: int, end: int) -> list:
    """
    Removes all complex numbers within a specified range of positions.
    :param numbers_list: The list of complex numbers.
    :param start: The starting position of the range.
    :param end: The ending position of the range.
    :return: The updated list of complex numbers.
    :raises IndexError: If the specified range is invalid.
    """
    if start > end or start < 0 or end >= len(numbers_list):
        raise IndexError("Invalid range specified")
    return numbers_list[:start] + numbers_list[end+1:]


def replace_number(numbers_list: list, old_number: list, new_real: int, new_imaginary: int) -> list:
    """
    Replaces an existing complex number with a new one.
    :param numbers_list: The list of complex numbers.
    :param old_number: The complex number to replace.
    :param new_real: The real part of the new complex number.
    :param new_imaginary: The imaginary part of the new complex number.
    :return: The updated list of complex numbers.
    """
    new_number = create_number(new_real, new_imaginary)
    for i, number in enumerate(numbers_list):
        if number == old_number:
            numbers_list[i] = new_number
    return numbers_list

def display_numbers(number_list: list):
    for number in number_list:
        real=get_real(number)
        imaginary=get_imaginary(number)
        if imaginary==0:
            print(real)
        else:
            print(f"{real} + {imaginary}i")

from texttable import Texttable
from math import sqrt


def format_table(data: list) -> str:
    """
    Formats a list of complex numbers into a table.
    :param data: List of complex numbers.
    :return: A formatted string representing the table.
    """
    table = Texttable()
    table.header(["Index", "Real", "Imaginary"])
    for idx, number in enumerate(data):
        table.add_row([idx, get_real(number), get_imaginary(number)])
    return table.draw()


def list_real_range(numbers_list: list, start: int, end: int) -> str:
    """
    Returns all real numbers (imaginary part = 0) within a specified range of positions.
    :param numbers_list: The list of complex numbers.
    :param start: The starting position of the range.
    :param end: The ending position of the range.
    :return: A list of real numbers within the specified range.
    :raises IndexError: If the specified range is invalid.
    """
    if start < 0 or end >= len(numbers_list) or start > end:
        raise IndexError("Invalid range specified")
    result = [number for number in numbers_list[start:end+1] if get_imaginary(number) == 0]
    return format_table(result)


def list_modulo(numbers_list: list, operator: str, value: float) -> str:
    """
    Returns all complex numbers whose modulus satisfies a given condition.
    :param numbers_list: The list of complex numbers.
    :param operator: The comparison operator ('<', '=', '>').
    :param value: The value to compare the modulus against.
    :return: A list of complex numbers that meet the condition.
    :raises ValueError: If an invalid operator is specified.
    """
    if operator not in ("<", "=", ">"):
        raise ValueError("Invalid operator. Use '<', '=', or '>'.")
    result = []
    for number in numbers_list:
        modulus = sqrt(get_real(number)**2 + get_imaginary(number)**2)
        if (operator == "<" and modulus < value) or \
           (operator == "=" and modulus == value) or \
           (operator == ">" and modulus > value):
            result.append(number)
    return format_table(result)


"""
Generate HTML documentation using pdoc
f = open("docs.html", "wt")
f.write(pdoc("functions.py",""))
f.close()
"""