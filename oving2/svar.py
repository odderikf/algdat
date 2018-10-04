def f(x,n): #Theta(n)
	if n:
		return x*f(x,n-1) # Theta(n)
	else:
		return 1 # Theta(1)

def g(x,n): #Theta(ln(n)) da en dobling i n gir +1 i tid. Ignorerer forskjell mellom elif og else, da den vil bytte mellom disse vilt
	if not n:
		return 1 #Theta(1)
	elif n%2: #oddetall
		return x* g( x*x , (n-1)/2) # 
	else:
		return g( x*x, n/2 ) # Theta(Theta(g)/2)

def n(x,n):
	return x**n

from matplotlib import pyplot as plt
import sys
sys.setrecursionlimit(8*sys.getrecursionlimit())
xs1 = []
xs2 = []
fs1 = []
gs1 = []
ns1 = []
ns2 = []
x = 1.0001
import time
for i in range(10000000000000,100000000000000,10000000000000):
        t0 = time.time()
        g(x,i)
        t = time.time()
        xs1.append(t-t0)

plt.plot(xs1)
plt.show()
##
##row = input()
##while "DONE" not in row:
##	x,f1,n1 = [int(x) for x in row.split(" ")]
##	xs1.append(x)
##	fs1.append(f1)
##	ns1.append(n1)
##	row = input()
##
##row = input()
##while row:
##	x,g1,n1 = [int(x) for x in row.split(" ")]
##	xs2.append(x)
##	gs1.append(g1)
##	ns2.append(n1)
##	row = input()

##fig, axes = plt.subplots(1,2)
##axes[0].plot(xs1,fs1, 'r')
##axes[1].plot(xs2,gs1, 'b')
##axes[0].plot(xs1,ns1, 'g--')
##axes[1].plot(xs2,ns2, 'g--')
##plt.show()

