import sys

def loop(row, n):
    if row == 0:
        print (n -1)*' ' + '*'
    elif row == n*2 -2:
        print (n-1)*' ' + '*'
        return
    elif row < n:
        print (n -1 -row) * ' ' + '*' + (1 + 2*(row -1))*' ' + '*'
    else:
        print (row -n +1) * ' ' + '*' + ((2*n -3) - 2*(row - n +1))*' ' + '*'
    loop(row +1, n)

n = int(sys.stdin.readline())
if n == 1:
    print '*'
elif n > 1:
    loop(0, n)
