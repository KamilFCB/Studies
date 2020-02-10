import itertools


def get_letters(word):
    result = []
    for char in word:
        if char not in result:
            result.append(char)
    return result


def calculate_value(dictionary, word):
    result = 0
    factor = 10 ** len(word)
    for ch in word:
        result += factor * dictionary[ch]
        factor /= 10
    return result


def solve(arg1, arg2, sum):
    letters = get_letters(arg1+arg2+sum)
    permutations = list(itertools.permutations([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], len(letters)))
    for permutation in permutations:
        dictionary = dict(zip(letters, permutation))
        number1 = calculate_value(dictionary, arg1)
        number2 = calculate_value(dictionary, arg2)
        sum_number = calculate_value(dictionary, sum)

        if number1 + number2 == sum_number:
            print(number1)
            print(number2)
            print(sum_number)
            print(dictionary)
            break


solve("KIOTO", "OSAKA", "TOKIO")
solve("KTO", "KOT", "TOK")
solve("TEST", "JEST", "SUPER")
solve("KWARTA", "KWARTA", "POLOWA")