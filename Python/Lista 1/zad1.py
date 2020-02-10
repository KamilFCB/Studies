def vat_faktura(zakupy):
    return round(sum(zakupy) * 1.23, 2)


def vat_paragon(zakupy):
    wynik = 0.0
    for i in zakupy:
        wynik += round(i * 1.23, 2)
    return wynik


lista = [1, 1, 1, 1]
print(vat_paragon(lista) == vat_faktura(lista))
lista = [123, 111, 13, 44]
print(vat_paragon(lista) == vat_faktura(lista))
lista = [1241, 2141, 989801, 100000]
print(vat_paragon(lista) == vat_faktura(lista))
lista = [0.2, 0.5, 4.59, 6]
print(vat_faktura(lista) == vat_paragon(lista))
