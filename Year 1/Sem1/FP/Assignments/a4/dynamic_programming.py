def dynamic_function(price, n):
    dp = [0] * (n + 1)
    # Build the table dp[] in a bottom-up manner
    for length in range(1, n + 1):
        max_profit = 0
        for cut in range(1, length + 1):
            # Ensure the cut is within bounds and calculate the maximum profit
            if cut <= len(price):
                max_profit = max(max_profit, price[cut - 1] + dp[length - cut])
                #price[cut-1] the profit for a piece of length cut (arr indexed from 0 )
                #dp[length-cut] the best possible profit for the remaining length

                #print("length", length,"cut: ", cut, "max_profit: ", max_profit)

        dp[length] = max_profit

    # The answer is the maximum obtainable profit for rod length `n`
    return dp[n]

#7
# 1  2  3  4   5   6   7
#[1, 5, 8, 9, 10, 17, 17]


#dynamic_function([1, 5, 8, 9, 10, 17, 17], 7)



# The time complexity is O(cut * length) -> O(n^2)
# The space complexity is O(length+ n) -> O(2n) -> O(n) because we use an array to store the value for each length
#               and one for the maximum value for a length of n
