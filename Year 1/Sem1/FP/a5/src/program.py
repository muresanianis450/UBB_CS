
#
# Write the implementation for A5 in this file
#

# Write below this comment
# Functions to deal with complex numbers -- list representation

def create_number(r, i):
    return [r,i]
def get_real(list):
    real,img = list
    return real
def get_imaginary(list):
    real, img = list
    return img
def set_real(list,x):
    real, img = list
    list = x,img
    return list
def set_imaginary(list,x):
    real, img = list
    list = real,x
    return list
def to_string(list):
    real, img = list
    if img>0:
        string=f"{real}+{img}i"
    elif img<0:
        string=f"{real}{img}i"
    else:
        string=f"{real}"
    return string

# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
"""
def create_number(r, i):
    return {"re":r,"im":i}
def get_real(array):
    return array["re"]
def get_imaginary(array):
    return array["im"]
def set_real(array, x):
    array["re"]=x
    return array
def set_imaginary(array, x):
    array["im"]=x
    return array
def to_string(array):
    real=array["re"]
    img=array["im"]
    if img>0:
        string=f"{real}+{img}i"
    elif img<0:
        string=f"{real}{img}i"
    else:
        string = f"{real}"
    return string

"""
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
# Write below this comment
# Functions that deal with subarray/subsequence properties

# 5.A | The longest subarray of numbers where each number's modulus is in the [0, 10] range.

def f5a(complex_numbers):
    k=0
    maxi=0
    j=0
    l=0
    for complex_number in complex_numbers:
        r=get_real(complex_number)
        i=get_imaginary(complex_number)
        s=r*r+i*i # modulus of a complex number is sqrt(r^2 + i^2) , this result should be in the interval [0,10]
        if s<=100:# raise to the 2nd power the sqrt so our interval will now be [0,100]
            k+=1
            if k>maxi:
                maxi=k
                l=j#the index of the last element in our longest subarray
        else:
            k=0
        j+=1
    return maxi,l

# 2.B
# Function to find the longest increasing subsequence by real part (using dynamic programming)
def f2b(complex_numbers):
    if not complex_numbers:
        return []

    # Dynamic programming table to store longest increasing subsequence ending at each index
    #Explanation for laboratory

    # nb:     3  5  2  1  6  2  4  9  7
    # index:  1  2  3  4  5  6  7  8  9
    # len:    1  1  1  1  1  1  1  1  1
    # prev:  -1  1„ -1 -1 -1 -1 -1 -1 -1

    n = len(complex_numbers)
    lengths = [1] * n
    predecessors = [-1] * n

    for i in range(1, n):
        for j in range(i):
            #if the next number(i) is bigger than the previous(j) and the subarray that i have formed with my j is bigger than what i have with i
            if get_real(complex_numbers[i]) > get_real(complex_numbers[j]) and lengths[i] < lengths[j] + 1:
                lengths[i] = lengths[j] + 1
                predecessors[i] = j
                #i update the length of i being length of j +1 and the predecessor of i being j


    # Find the index of the maximum length in lengths array
    max_length = max(lengths)
    max_index = lengths.index(max_length)

    # Retrieve the subsequence
    sequence = []
    while max_index != -1:
        sequence.append(complex_numbers[max_index])
        max_index = predecessors[max_index]

    return sequence[::-1]  # Reverse to get the sequence in correct order

# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

#
# Write below this comment
# UI section
# Write all functions that have input or print statements here

def read_complex():
    r=int(input("What is the real part:"))
    b=int(input("What is the imaginary part:"))
    return r,b
def display_list(complex_numbers):
    for complex_number in complex_numbers:
        print(to_string(complex_number))
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def testing():
    # f2b Tests
    try:
        assert f2b([]) == []
        print("Test 1 for f2b passed.")

        assert f2b([create_number(1, 2)]) == [create_number(1, 2)]
        print("Test 2 for f2b passed.")

        assert f2b([create_number(1, 2), create_number(2, 3), create_number(3, 4)]) == [
            create_number(1, 2),
            create_number(2, 3),
            create_number(3, 4),
        ]
        print("Test 3 for f2b passed.")

        assert f2b([
            create_number(3, 4),
            create_number(1, 2),
            create_number(2, 3),
            create_number(5, 0),
        ]) == [create_number(1, 2), create_number(2, 3), create_number(5, 0)]
        print("Test 4 for f2b passed.")

        assert f2b([
            create_number(2, 1),
            create_number(2, 2),
            create_number(2, 3),
        ]) == [create_number(2, 1)]
        print("Test 5 for f2b passed.")

    except AssertionError:
        print("An f2b test failed.")

    # f5a Tests
    try:
        assert f5a([]) == (0, 0)
        print("Test 1 for f5a passed.")

        assert f5a([
            create_number(1, 2),
            create_number(2, 3),
            create_number(3, 4),
        ]) == (3, 2)  # 3 elements ending at index 2
        print("Test 2 for f5a passed.")

        assert f5a([
            create_number(1, 1),
            create_number(3, 4),
            create_number(6, 8),
            create_number(7, 7),
            create_number(10, 10)
        ]) == (4, 3)  # The longest valid subarray has 4 elements, ending at index 3
        print("Test 3 for f5a passed.")

        assert f5a([
            create_number(11, 0),
        ]) == (0, 0)  # No valid subarray
        print("Test 4 for f5a passed.")

        assert f5a([
            create_number(3, 4),
            create_number(6, 8),
            create_number(10, 10),
            create_number(1, 1),
            create_number(2, 2),
        ]) == (2, 1)  # 2 elements ending at index 1
        print("Test 5 for f5a passed.")

    except AssertionError:
        print("An f5a test failed.")

def main():
        array = []

        while True:
            print("MENU:")
            print("1. Generate a array.")
            print("2. Display array.")
            print("3. Solve problem 5 from set A.")
            print("4. Solve problem 2 from set B.")
            print("5. Exit program.")
            x = input("Choose option: ")

            try:
                x = int(x)
            except ValueError:
                print("Please enter a valid number between 1 and 5.")
                continue
            match x:
                case 1:
                    array = []
                    try:
                        m = int(input("How many complex numbers? "))
                        for i in range(m):
                            real, img = read_complex()
                            array.append(create_number(real, img))
                    except ValueError:
                        print("Please enter a valid integer for the number of complex numbers.")

                case 2:
                    if array:
                        display_list(array)
                    else:
                        print("Generate a array first")

                case 3:
                    if array:
                        max_len, end_idx = f5a(array)
                        print("Maximum subarray has", max_len, "elements")
                        for i in range(end_idx + 1 - max_len, end_idx + 1):
                            print(to_string(array[i]))
                    else:
                        print("Generate a array first")

                case 4:
                    if array:
                        seq = f2b(array)
                        print("Maximum subsequence has", len(seq), "elements")
                        display_list(seq)
                    else:
                        print("Generate a array first")

                case 5:
                    print("Exiting program.")
                    break

                case _:
                    print("Please enter a number between 1 and 5.")
if __name__ == "__main__":
    testing()
    main()
