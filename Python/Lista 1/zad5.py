import math


def pierwsza(x):
    for i in range(2, math.ceil(math.sqrt(x))):
        if x % i == 0:
            return False
    return True


def nastepna_pierwsza(x):
    x += 1
    while not pierwsza(x):
        x += 1
    return x


def rozklad(x):
    result = []
    tmp_pierwsza = 2
    while x != 1:
        licznik = 0
        while x % tmp_pierwsza == 0:
            x /= tmp_pierwsza
            licznik += 1

        if licznik > 0:
            result.append([tmp_pierwsza, licznik])

        tmp_pierwsza = nastepna_pierwsza(tmp_pierwsza)

    print(result)


rozklad(756)
rozklad(512)
rozklad(13)
rozklad(36)
