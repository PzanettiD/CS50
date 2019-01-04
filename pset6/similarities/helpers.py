from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    set_a = set(a.splitlines())
    set_b = set(b.splitlines())
    same_line = list(set_a & set_b)
    return same_line


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    sentences_a = set(sent_tokenize(a))
    sentences_b = set(sent_tokenize(b))
    same_sentence = list(sentences_a & sentences_b)
    return same_sentence


def slicing(s, m):
    sub = set()
    len_s = len(s)
    for i in range(len_s):
        if i + (m - 1) < len_s:
            sub.add(s[i:i+m])
        else:
            break
    return sub


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    substring_a = slicing(a, n)
    substring_b = slicing(b, n)
    same_substring = list(substring_a & substring_b)
    return same_substring
