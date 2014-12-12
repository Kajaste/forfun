import itertools as t,sys
e=enumerate
s=sorted
c=s([(x,len(list(y)))for x,y in t.groupby(s(sys.stdin.read()))],key=lambda x:(x[1],x[0]))
for n,i in e(c,1):print n,repr(i[0])[1:-1]if i[0]!='\\'else'\\',i[1]
print sum([(i*c[1])for i,c in e(c,1)])
