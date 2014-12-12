import itertools as t,sys
e=enumerate
s=sorted
c=s([(x,len(list(y)))for x,y in t.groupby(s(sys.stdin.read()))],key=lambda x:(x[1],x[0]))
for n,b in e(c,1):print n,repr(b[0])[1:-1]if b[0]!='\\'else'\\',b[1]
print sum([(b*c[1])for b,c in e(c,1)])
