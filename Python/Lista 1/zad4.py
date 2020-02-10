def zaszyfruj(szyfr, klucz):
    wynik = ""
    for znak in szyfr:
        wynik += chr(ord(znak) ^ klucz)
    return wynik


def odszyfruj(szyfr, klucz):
    wynik = ""
    for znak in szyfr:
        wynik += chr(ord(znak) ^ klucz)
    return wynik


print(zaszyfruj("Python", 7))
print(odszyfruj("W~sohi", 7))

print(odszyfruj(zaszyfruj("Uniwersytet Wrocławski", 142), 142))
