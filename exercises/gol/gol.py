import copy
import sys

LIVE = '#'
DEAD = '.'

def read_lines(f):
    lines = [list(line.rstrip()) for line in f
             if len(line.rstrip()) != 0]
    return lines

def get_neighbors(lines, cell):
    rowmax = len(lines) - 1
    colmax = len(lines[0]) - 1
    vpos = cell[0]
    hpos = cell[1]
    u, ur, r, dr, d, dl, l, ul = None, None, None, None, None, None, None, None

    if vpos != 0:
        u = (vpos - 1, hpos)
        if hpos != 0:
            ul = (vpos - 1, hpos - 1)
        if hpos != colmax:
            ur = (vpos - 1, hpos + 1)
    if vpos != rowmax:
        d = (vpos + 1, hpos)
        if hpos != 0:
            dl = (vpos + 1, hpos - 1)
        if hpos != colmax:
            dr = (vpos + 1, hpos + 1)
    if hpos != 0:
        l = (vpos, hpos - 1)
    if hpos != colmax:
        r = (vpos, hpos + 1)
    return u, ur, r, dr, d, dl, l, ul

def count_neighbors(lines, nbrs, liveness):
    count = 0
    for nbr in nbrs:
        if nbr and lines[nbr[0]][nbr[1]] == liveness:
            count += 1
    return count

def determine_fates(lines):
    new_lines = copy.deepcopy(lines)
    for rownum, row in enumerate(lines):
        for colnum, cell in enumerate(row):
            nbrs = get_neighbors(lines, (rownum, colnum))
            livecount = count_neighbors(lines, nbrs, LIVE)
            if cell == LIVE:
                if livecount < 2 or livecount > 3:
                    new_lines[rownum][colnum] = DEAD
            elif cell == DEAD:
                if livecount == 3:
                    new_lines[rownum][colnum] = LIVE
    return new_lines

def print_world(lines):
    print '\n'.join(''.join(line) for line in lines)

lines = read_lines(sys.stdin)
new_lines = determine_fates(lines)
print_world(new_lines)
