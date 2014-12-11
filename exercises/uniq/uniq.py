import itertools,sys
e=enumerate
c=sorted([(x,len(list(y))) for x,y in itertools.groupby(sorted(sys.stdin.read()[:-1]))],key=lambda x:(x[1],x[0]))
for n,i in e(c,1):print n,repr(i[0])[1:-1],i[1]
print sum([(i*c[1]) for i,c in e(c,1)])
