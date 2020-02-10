import time


def perfect_func(n):
    return n == sum(list(filter(lambda x: not n % x, range(1, n))))


def perfect_iter(n):
    dividers = []
    for i in range(1, n):
        if n % i == 0:
            dividers.append(i)
    return sum(dividers) == n


def doskonale_imperatywna(n):
    result = []
    for i in range(1, n+1):
        if perfect_iter(i):
            result.append(i)
    return result


def doskonale_funkcyjna(n):
    return list(filter(perfect_func, range(1, n+1)))


def doskonale_skladana(n):
    return [x for x in range(1, n+1) if x == sum([i for i in range(1, x) if x % i == 0])]


print(doskonale_imperatywna(1000))
print(doskonale_funkcyjna(1000))
print(doskonale_skladana(1000))

max_number = 10000
start = time.time()
doskonale_imperatywna(max_number)
end = time.time() - start
print("Czas dla wersji imperatywnej: {0}".format(end))

start = time.time()
doskonale_skladana(max_number)
end = time.time() - start
print("Czas dla wersji list skladanych: {0}".format(end))

start = time.time()
doskonale_funkcyjna(max_number)
end = time.time() - start
print("Czas dla wersji funkcyjnej: {0}".format(end))
