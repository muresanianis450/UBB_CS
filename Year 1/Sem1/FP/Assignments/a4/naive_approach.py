#Maximize the profit when selling a rod of length n. The rod can be cut into pieces of integer lengths and pieces can be sold individually.
#The prices are known for each possible length. For example, if rod length n = 7, and the price array is price = [1, 5, 8, 9, 10, 17, 17]
#(the price of a piece of length 3 is 8), the maximum profit is 18, and is obtained by cutting the rod into 3 pieces, two of length two and one of length 3.
#Display the profit and the length of rod sections sold to obtain it.
def naive_function(price, n: int, length: int) -> int:
    if length == 0:
        return 0
    if n <= 0:
        return 0
    if n <= length: #if our piece length is less or equal than our remaining rod
        #we take into consideration if we add it's worth size to the sum
        include = price[n-1] + naive_function(price, n, length - n)
        #or we don't and go to the next piece
        exclude = naive_function(price, n - 1, length)
        #then we return the maximum between our two choices
        return max(include, exclude)
    else:
        #if a piece of size n is bigger than our remaining length, we just go to the next one
        return naive_function(price, n - 1, length)


#7
#[1, 5, 8, 9, 10, 17, 17]

# The time complexity is O(2^length) because we have a double recursion call, which results in a binary tree
#           (and every possible way is taken into consideration)
#
# The space complexity is O(length) because our recursive call can go length in
#            space depth if we consider cut=1 a possibility (this is stack memory, we don't use any additional data structures)