from random import randrange


def usun_losowo(slowa, ilosc):
    for i in range(0, ilosc):
        del slowa[randrange(len(slowa))]
    result = ""
    for slowo in slowa:
        result += slowo + " "
    return result.rstrip(" ")


def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    result = ""
    for slowo in tekst.lstrip(" ").replace(".", "").replace(",", "").split(" "):
        if len(slowo) <= dl_slowa:
            result += slowo + ' '
    if len(result.rstrip(" ").split(" ")) > liczba_slow:
        return usun_losowo(result.rstrip(" ").split(" "), len(result.split(" ")) - liczba_slow - 1)
    return result


test = "Podział peryklinalny inicjałów wrzecionowatych \
kambium charakteryzuje się ścianą podziałową inicjowaną \
w płaszczyźnie maksymalnej."
f = open("pan-tadeusz.txt", "r")
content = f.read()
for sentence in content.replace("!", ".").replace("?", ".").split("."):
    print(uprosc_zdanie(sentence, 7, 3) + ".")
# print(uprosc_zdanie(test, 10, 5))
