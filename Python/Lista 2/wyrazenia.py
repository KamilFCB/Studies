class Formula:
    def __init__(self):
        pass

    def oblicz(self, zmienne):
        raise NotImplementedError

    def __str__(self):
        raise NotImplementedError

    def zwroc_zmienne(self):
        raise NotImplementedError


class Impl(Formula):
    def __init__(self, arg1, arg2):
        super().__init__()
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        if self.arg1.oblicz(zmienne) is True and self.arg1.oblicz(zmienne) is False:
            return False
        return True

    def __str__(self):
        return self.arg1.__str__() + ' => ' + self.arg2.__str__()

    def zwroc_zmienne(self):
        zmienne = self.arg1.zwroc_zmienne()
        zmienne_arg2 = self.arg2.zwroc_zmienne()
        for zmienna in zmienne_arg2:
            if zmienna not in zmienne:
                zmienne[zmienna] = False
        return zmienne


class And(Formula):
    def __init__(self, arg1, arg2):
        super().__init__()
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        if self.arg1.oblicz(zmienne) is True and self.arg2.oblicz(zmienne) is True:
            return True
        return False

    def __str__(self):
        return self.arg1.__str__() + ' ∧ ' + self.arg2.__str__()

    def zwroc_zmienne(self):
        zmienne = self.arg1.zwroc_zmienne()
        zmienne_arg2 = self.arg2.zwroc_zmienne()
        for zmienna in zmienne_arg2:
            if zmienna not in zmienne:
                zmienne[zmienna] = False
        return zmienne


class Or(Formula):
    def __init__(self, arg1, arg2):
        super().__init__()
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        if self.arg1.oblicz(zmienne) is True:
            return True
        if self.arg2.oblicz(zmienne) is True:
            return True
        return False
        # return self.arg1.oblicz(zmienne) or self.arg2.oblicz(zmienne)

    def __str__(self):
        return self.arg1.__str__() + ' v ' + self.arg2.__str__()

    def zwroc_zmienne(self):
        zmienne = self.arg1.zwroc_zmienne()
        zmienne_arg2 = self.arg2.zwroc_zmienne()
        for zmienna in zmienne_arg2:
            if zmienna not in zmienne:
                zmienne[zmienna] = False
        return zmienne


class Eq(Formula):
    def __init__(self, arg1, arg2):
        super().__init__()
        self.arg1 = arg1
        self.arg2 = arg2

    def oblicz(self, zmienne):
        return self.arg1.oblicz(zmienne) == self.arg2.oblicz(zmienne)

    def __str__(self):
        return self.arg1.__str__() + ' <=> ' + self.arg2.__str__()

    def zwroc_zmienne(self):
        zmienne = self.arg1.zwroc_zmienne()
        zmienne_arg2 = self.arg2.zwroc_zmienne()
        for zmienna in zmienne_arg2:
            if zmienna not in zmienne:
                zmienne[zmienna] = False
        return zmienne


class Not(Formula):
    def __init__(self, arg):
        super().__init__()
        self.arg = arg

    def oblicz(self, zmienne):
        return not(self.arg.oblicz(zmienne))

    def __str__(self):
        return '~(' + self.arg.__str__() + ')'

    def zwroc_zmienne(self):
        return [].append(self.arg.zwroc_zmienne())


class Zmienna(Formula):
    def __init__(self, arg):
        super().__init__()
        self.arg = arg

    def oblicz(self, zmienne):
        if self.arg in zmienne:
            return zmienne.get(self.arg)
        else:
            raise BrakZmiennej("Brak zdefiniowanej zmiennej " + str(self.arg))

    def __str__(self):
        return str(self.arg)

    def zwroc_zmienne(self):
        return {self.arg: False}


class true(Formula):
    def __init__(self):
        super().__init__()

    def oblicz(self, zmienne):
        return True

    def __str__(self):
        return str("true")

    def zwroc_zmienne(self):
        return []


class false(Formula):
    def __init__(self):
        super().__init__()

    def oblicz(self, zmienne):
        return False

    def __str__(self):
        return str("false")

    def zwroc_zmienne(self):
        return []


class BrakZmiennej(Exception):
    def __init__(self, message):
        self.message = message


def dodaj_zera(zapis, dlugosc):
    for i in range(dlugosc-zapis.__len__()):
        zapis = '0' + zapis
    return zapis


def generuj_wartosciowania(zmienne):
    tmp_zmienne = zmienne
    result = []
    for i in range(pow(2, tmp_zmienne.__len__())):  # len(tmp_zmienne)
        wartosci = dodaj_zera("{0:b}".format(i), tmp_zmienne.__len__())
        for j in range(tmp_zmienne.__len__()):
            klucz = list(tmp_zmienne.keys())[j]
            if wartosci[j] == '1':
                tmp_zmienne.__setitem__(klucz, True)
            else:
                tmp_zmienne.__setitem__(klucz, False)
        result.append(tmp_zmienne.copy())
    return result


def tautologia(wyrazenie, zmienne):
    for wartosci in generuj_wartosciowania(zmienne):
        print(wartosci)
        if wyrazenie.oblicz(wartosci) is False:
            return False
    return True


c = {
    "p": True,
    "q": False,
    "r": True
}

formula = (Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r"))))
print(formula)
print(formula.zwroc_zmienne())
print(formula.oblicz(formula.zwroc_zmienne()))

# print(Not(Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r")))))
# print(tautologia((Not(Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r"))))), c))
# print(Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r"))))
# print(tautologia((Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r")))), c))
# print(Or(Zmienna("p"), true()))
# print(Or(Zmienna("p"), true()).oblicz(c))
# print(Eq(Or(Zmienna("p"), Zmienna("q")), Or(Zmienna("p"), Zmienna("r"))).zwroc_zmienne())
