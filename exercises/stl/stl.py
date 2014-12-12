import sys, itertools

WORDS = ['professionalism', 'respect', 'perseverance']

def read_n_and_message(f):
    n = int(f.readline())
    message = f.readline().lower()
    return n, message

def scan_message(n, message, word):
    groups = []
    group = ''
    n_counter = 0
    for c in message:
        if c in word:
            group += c
            n_counter = 0
        else:
            n_counter += 1
        if n_counter > n:
            groups.append(group)
            group = ''
            n_counter = 0
    if group != '':
        groups.append(group)
    return groups

def lettercount(word):
    return dict((x, len(list(y))) for x, y in itertools.groupby(sorted(word)))

def word_in_groups(groups, word):
    def counts_fail(lc_w, lc_g):
        for l, c in lc_w.items():
            if l not in lc_g or lc_g[l] < c:
                return True
    lc_w = lettercount(word)
    for group in groups:
        if not counts_fail(lc_w, lettercount(group)):
            return True

n, message = read_n_and_message(sys.stdin)

for word in WORDS:
    groups = scan_message(n, message, word)
    if word_in_groups(groups, word):
        print 'True'
        sys.exit(0)
print 'False'
