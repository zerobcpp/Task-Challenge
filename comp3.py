def max_items_after_freeing(A, R):
    N = len(A)

    l = 0

    for i in range(N):
        c = set()
        for j in range(i, N):
            if len(c) == R:
                break
            c.add(A[j])



# Examples
print(max_items_after_freeing([2, 1, 2, 3, 2, 2], 3))  # Output: 2
print(max_items_after_freeing([2, 3, 1, 1, 2], 2))       # Output: 3
print(max_items_after_freeing([20, 10, 10, 10, 30, 20], 3))  # Output: 3
print(max_items_after_freeing([1, 1000000, 1], 3))        # Output: 0
