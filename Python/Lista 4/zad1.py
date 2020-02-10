import math
import time


def prime_iter(n):
    if n == 2:
        return True
    for i in range(2, math.ceil(math.sqrt(n)) + 1):
        if n % i is 0:
            return False
    return True


def pierwsze_imperatywna(n):
    result = []
    for i in range(2, n+1):
        if prime_iter(i):
            result.append(i)
    return result


def prime_func(n):
    return len(list(filter(lambda x: n % x == 0 and n != 2, range(2, math.ceil(math.sqrt(n)) + 1)))) == 0


def pierwsze_funkcyjna(n):
    return list(filter(prime_func, range(2, n+1)))


def pierwsze_skladana(n):
    return [x for x in range(2, n+1) if x == 2 or all(x % i != 0 for i in range(2, math.ceil(math.sqrt(x)) + 1))]


print(pierwsze_imperatywna(100))
print(pierwsze_funkcyjna(100))
print(pierwsze_skladana(100))

max_number = 100000
start = time.time()
pierwsze_imperatywna(max_number)
end = time.time() - start
print("Czas dla wersji imperatywnej: {0}".format(end))

start = time.time()
pierwsze_skladana(max_number)
end = time.time() - start
print("Czas dla wersji list skladanych: {0}".format(end))

start = time.time()
pierwsze_funkcyjna(max_number)
end = time.time() - start
print("Czas dla wersji funkcyjnej: {0}".format(end))
