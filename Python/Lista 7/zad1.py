import string
import threading
import urllib.request
import re
import bs4

visited = []


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
    if step < 0:
        return
    lck = threading.Condition()
    lck.acquire()
    if url in visited:
        return
    visited.append(url)
    lck.release()
    get_data(url, index_dict)
    thread_array = []
    data_thread = threading.Thread(target=get_data, args=(url, index_dict))
    data_thread.start()
    print("start " + str(url))
    for link in get_urls(url):
        # index_site(link, step - 1, words, index_dict)
        current_thread = threading.Thread(target=index_site, args=(link, step-1, words, index_dict))
        thread_array.append(current_thread)
        current_thread.start()

    for thread in thread_array:
        thread.join()
    data_thread.join()
    print("koniec " + str(url))


def count_word(url, word):
    result = len(list(filter(lambda w: w == word, get_word_list(url))))
    print(str(url) + " " + str(word) + " " + str(result))
    return result
    # return len(list(filter(lambda w: w == word, get_word_list(url))))


def sort_url_list(index_dict, k):
    index_dict[k].sort(key=lambda u: count_word(u, k), reverse=True)


def index_sites(url, max_step, words):
    index_dict = {word: [] for word in words}
    index_site(url, max_step, words, index_dict)
    thread_array = []
    for k in index_dict.keys():
        # index_dict[k].sort(key=lambda u: count_word(u, k), reverse=True)
        current_thread = threading.Thread(target=sort_url_list, args=(index_dict, k))
        thread_array.append(current_thread)
        current_thread.start()

    for thread in thread_array:
        thread.join()
    return index_dict


print(index_sites("https://ii.uni.wroc.pl", 1, ["programowanie", "informatyka", "instytut"]))
