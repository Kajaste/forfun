import sys

X = 'x'
O = '0'
DELIMITER = '|'
BORDERLINE = '-+-+-'
GAME_LINECOUNT = 5

def parse_game(f):
    game = []
    for line in f.read().split('\n')[:GAME_LINECOUNT]:
        if line == BORDERLINE:
            continue
        game.append(line.split(DELIMITER))
    return game

def x_wins(xs):
    rowset = set([square[0] for square in xs])
    colset = set([square[1] for square in xs])
    if len(rowset) == 1 or len(colset) == 1:
        return True
    elif len(rowset) == 3 and len(colset) == 3:
        return True
    return False

def solve_game(game):
    xs = []
    frees = []
    for rownum, row in enumerate(game):
        for colnum, square in enumerate(row):
            if square == X:
                xs.append((rownum, colnum))
            elif square != O:
                frees.append((rownum, colnum))

    if len(xs) == 2:
        for spot in frees:
            if x_wins(xs + [spot]):
                game[spot[0]][spot[1]] = X
                break

    return game

def print_game(game):
    print ('\n' + BORDERLINE + '\n').join([DELIMITER.join(row)
                                           for row in game])

print_game(solve_game(parse_game(sys.stdin)))
