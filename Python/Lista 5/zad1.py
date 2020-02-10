import math
import time
from itertools import islice

from prettytable import PrettyTable


def jest_pierwsza_iter(n):
    if n == 2:
        return True
    for j in range(2, math.ceil(math.sqrt(n)) + 1):
        if n % j is 0:
            return False
    return True


def pierwsze_imperatywna(n):
    result = []
    for j in range(2, n+1):
        if jest_pierwsza_iter(j):
            result.append(j)
    return result


def jest_pierwsza_funkc(n):
    return len(list(filter(lambda x: n % x == 0 and n != 2, range(2, math.ceil(math.sqrt(n)) + 1)))) == 0


def pierwsze_funkcyjna(n):
    return list(filter(jest_pierwsza_funkc, range(2, n + 1)))


def pierwsze_skladana(n):
    return [x for x in range(2, n+1) if x == 2 or all(x % j != 0 for j in range(2, math.ceil(math.sqrt(x)) + 1))]


def generator_pierwszych():
    pierwsza = 1
    while True:
        pierwsza += 1
        if jest_pierwsza_iter(pierwsza):
            yield pierwsza


def pierwsze_iterator(n):
    return [x for x in islice(generator_pierwszych(), 1, n) if x <= n]


wynik = PrettyTable(['', 'imperatywna', 'funkcyjna', 'skladana', 'iterator'])

for i in [10, 100, 1000, 10000, 100000]:
    start = time.time()
    pierwsze_imperatywna(i)
    imperatywna = time.time() - start
    start = time.time()
    pierwsze_funkcyjna(i)
    funkcyjna = time.time() - start
    start = time.time()
    pierwsze_skladana(i)
    skladana = time.time() - start
    start = time.time()
    pierwsze_iterator(i)
    iterator = time.time() - start
    wynik.add_row([i, imperatywna, funkcyjna, skladana, iterator])

print(wynik)
