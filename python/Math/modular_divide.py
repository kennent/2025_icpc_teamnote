# (a/b)%M => (a%M * pow(b,M-2,M)) % M

M = 1000000007
a=7
b=3
print((a%M * pow(b,M-2,M)) % M)