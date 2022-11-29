import numpy as np
a = np.array([[2], [3], [4]])
print(a)
b = a.tolist()
for j in b:
    print(type(j))
    for k in j:
        print(k)
for i in a:
    print(type(i))
    #print(i[0])
    #print(i[1])