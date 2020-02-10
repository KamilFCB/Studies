def pierwiastek(n):
    result = 0
    i = 0
    while result <= n:
        i += 1
        result += (2 * i - 1)
    return i-1


assert 13 == pierwiastek(170)
assert 13 == pierwiastek(169)
assert 12 == pierwiastek(168)
assert 3 == pierwiastek(9)
assert 2 == pierwiastek(8)
assert 2 == pierwiastek(7)
assert 2 == pierwiastek(6)
assert 2 == pierwiastek(5)
assert 2 == pierwiastek(4)
assert 1 == pierwiastek(3)
assert 1 == pierwiastek(2)
assert 1 == pierwiastek(1)
