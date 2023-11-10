import pandas
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline
from scipy.signal import lfilter
from matplotlib.pyplot import text

FILENAME = './noise/20k_3_'
LOW_VOLT = 0.8
HIGH_VOLT = 2.0

data = []

for i in range(10):

    csv = pandas.read_csv(FILENAME + str(i) + '.csv')
    df = pandas.DataFrame(csv)

    df = df.drop(['Record Length', '2500', 'Points', 'Unnamed: 5'],axis=1)

    n = 15  # the larger n is, the smoother curve will be
    b = [1.0 / n] * n
    a = 1
    yy = lfilter(b, a, df.iloc[:, 1])
    ax = plt.gca()
    #plt.plot(df.iloc[:, 0], yy, linewidth=2, linestyle="-", c="b")  # smooth by filter
    
    #plt.plot(df.iloc[:, 0], df.iloc[:, 1], linewidth=2, linestyle="-", c="b")

    stop = 0
    start = 0
    is_trigger = False
    is_zero = False

    for i in range(len(df.iloc[:,0])-1, 0, -1):
        if df.iloc[:,1][i] < HIGH_VOLT and not is_trigger:
            stop = df.iloc[:,0][i]
            is_trigger = True
        if (df.iloc[:,1][i] < LOW_VOLT or i == 1) and not is_zero:
            start = df.iloc[:,0][i]
            is_zero = True
    

    saturate_time = stop - start
    data.append(saturate_time)

data = np.array(data)
print(data)

mean = np.mean(data)
var = np.var(data)

print(mean)
print(var)

ax = plt.gca()
ax.axhline(mean, zorder=0)
plt.plot(range(10), data, linewidth=2, linestyle="-", c="b") 

plt.show()

data_minus_mean = []

for i in range(len(data)):
    data_minus_mean.append(data[i] - mean)

data_minus_mean = np.array(data_minus_mean)

plt.plot(range(10), data_minus_mean, linewidth=2, linestyle="-", c="b") 
plt.show()

mean2 = np.mean(data_minus_mean)
var2 = np.var(data_minus_mean)

print(mean2)
print(var2)