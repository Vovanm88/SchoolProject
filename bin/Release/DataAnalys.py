import matplotlib.pyplot as plt 

fig, ax = plt.subplots()

with open('C:/C++/Pitone/Data.txt') as file:
    a = file.read()

b = a.split('\n')
t=[]
v=[]
a=[]
f=[]
n=[]
Ek=[]
Ep=[]
Eng=[]
for i in range(0, len(b)-1):
    tmp=b[i].split(' ')
    t.append(float(tmp[0]))
    v.append(float(tmp[1]))
    a.append(float(tmp[2]))
    f.append(float(tmp[3]))
    n.append(float(tmp[4]))
    Ek.append(float(tmp[5]))
    Ep.append(float(tmp[6]))
    Eng.append(float(tmp[6])+float(tmp[5]))

ax.plot(t, v, label='v', color='#0000AA')
ax.plot(t, a, label='a', color='#E0DA7F')
ax.plot(t, f, label='f', color='#00AA00')
ax.plot(t, n, label='n', color='#BB0000')
ax.plot(t, Ek, label='Ek', color='#009FAA')
ax.plot(t, Ep, label='Ep', color='#0D0D0D')
ax.plot(t, Eng, label='Eng', color='#9D0D9D')

ax.legend()
plt.show()