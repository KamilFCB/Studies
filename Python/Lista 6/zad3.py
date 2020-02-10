import string
import urllib.request
import re
import bs4


def get_page_soup(url):
    try:
        urllib.request.urlopen(url)
    except urllib.request.HTTPError as ex:
        print('ERROR: ', ex)
        return "ERROR"

    req = urllib.request.Request(url)
    page = urllib.request.urlopen(req).read()
    return bs4.BeautifulSoup(page, "html.parser")


def get_text(url):
    page_soup = get_page_soup(url)
    if page_soup == "ERROR":
        return ""
    texts = page_soup.findAll(text=True)
    visible_texts = filter(lambda tag: tag.parent.name in ['b', 'p', 'title', 'h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'a',
                                                           'li', 'span', 'td', 'th'], texts)
    result = " ".join(text.strip() for text in visible_texts)
    punctuation = str.maketrans(dict.fromkeys(string.punctuation))
    return result.translate(punctuation)


def get_word_list(url):
    return [word.lower() for word in get_text(url).split(" ") if len(word) and
            re.match('[a-zA-Z]+[a-zA-Z0-9]*', word)]


def get_data(url, data):
    for word in get_word_list(url):
        if word in data and url not in data[word]:
            data[word].append(url)


def get_urls(url):
    page = get_page_soup(url)
    if page == "ERROR":
        return []

    urls = [str(link.get('href')) for link in page.find_all('a')]
    return list(filter(lambda l: l.startswith('http') or l.startswith('https'), urls))


def index_site(url, step, words, index_dict):
    if step >= 0:
        get_data(url, index_dict)

    for link in get_urls(url):
        index_site(link, step - 1, words, index_dict)


def count_word(url, word):
    result = len(list(filter(lambda w: w == word, get_word_list(url))))
    print(str(url) + " " + str(word) + " " + str(result))
    return result
    # return len(list(filter(lambda w: w == word, get_word_list(url))))


def index_sites(url, max_step, words):
    index_dict = {word: [] for word in words}
    index_site(url, max_step, words, index_dict)
    for k in index_dict.keys():
        index_dict[k].sort(key=lambda u: count_word(u, k), reverse=True)
    return index_dict


# def count_words_occurrence(url, step, words, word_occurrence):
#     if step >= 0:
#         for word in filter(lambda w: w in words, get_word_list(url)):
#             if url in word_occurrence[word]:
#                 word_occurrence[word][url] += 1
#             else:
#                 word_occurrence[word][url] = 1
#
#         for link in get_urls(url):
#             count_words_occurrence(link, step - 1, words, word_occurrence)
#
#
# def count_words_occurrences(url, max_step, words):
#     word_occurrence = {word: {} for word in words}
#     count_words_occurrence(url, max_step, words, word_occurrence)
#     return dict(sorted(word_occurrence.items(), key=lambda k: len(k[1]), reverse=True))


# print(count_words("https://ii.uni.wroc.pl", "instytut"))
print(index_sites("https://ii.uni.wroc.pl", 1, ["programowanie", "informatyka", "instytut"]))
# print(count_words_occurrences("https://ii.uni.wroc.pl", 1, ["programowanie", "informatyka", "instytut"]))
