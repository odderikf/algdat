def stringa(s):
    val = 0
    for i,c in enumerate(s):
        val += 3*ord(c) << i
    return val


def hashint(k):
    return k%6000011

def hashint2(k):
    return k%(6000011-1)+1


from matplotlib import pyplot as plt
keys = []
hashes = []
with open("names.txt") as file:
    for line in file.readlines():
        keys.append(line)
        hashes.append(stringa(line))
hashes = [i % 110 for i in hashes]

counts = [hashes.count(i) for i in set(hashes)]
print(*[(i,counts.count(i)) for i in set(counts)])


#plt.scatter(keys, hashes, c=range(0,len(keys)))
import random
keys = [random.randint(-5000000, 30000000) for _ in range(0, 5000)]
hashes = [hashint(i) for i in keys]

plt.scatter(keys, hashes, c=range(0, len(keys)))

plt.show()
