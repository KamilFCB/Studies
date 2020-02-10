def compress(text):
    result = ""
    for word in text.split(" "):
        compressed_word = ""
        counter = 0
        prev_char = '0'
        for char in word:
            if prev_char is '0':
                prev_char = char
                continue
            if char == prev_char:
                counter += 1
                continue
            if char != prev_char:
                if counter > 1:  # end of sequence
                    compressed_word += (str(counter) + prev_char)
                    counter = 0
                elif counter == 1:
                    compressed_word += prev_char + prev_char
                    counter = 0
                else:
                    compressed_word += prev_char
            prev_char = char
        if counter > 1:  # end of sequence
            compressed_word += (str(counter) + prev_char)
        elif counter == 1:
            compressed_word += prev_char + prev_char
        else:
            compressed_word += prev_char
        result += compressed_word + ' '
    return result


def decompress(text):
    result = ""
    for word in text.split(" "):
        decompressed_word = ""
        string_number = ''
        for char in word:
            if char.isnumeric():
                string_number += char
                continue
            if string_number != '':
                int_number = int(string_number)
                decompressed_word += char*int_number
                string_number = ''
            decompressed_word += char
        result += decompressed_word + ' '
    return result


print(compress("ala maa, kotaaaaaaaaaaaaaa"))
print(decompress(compress("ala maa, kotaaaaaaaaaaaaaa")))
