import pandas
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline
from scipy.signal import lfilter
from matplotlib.pyplot import text

FILENAME = './noise/20k_3_'
LOW_VOLT = 0.8
HIGH_VOLT = 2.0

csv = pandas.read_csv(FILENAME + '0.csv')
df = pandas.DataFrame(csv)
df = df.drop(['Record Length', '2500', 'Points', 'Unnamed: 5'],axis=1)


for i in range(1,10):

    csv_temp = pandas.read_csv(FILENAME + str(i) + '.csv')
    df_temp = pandas.DataFrame(csv_temp)

    print(df_temp.iloc[:,3])
    
    df.insert( loc=1, column='data' + str(i), value=df_temp.iloc[:,4])
    #plt.savefig(f[:-4] + '-' + str(saturate_time) + '.png')
    #plt.show()
    
    print(df)


    #df.plot()

    #plt.show()


df['mean'] = df.mean(axis=1)
df['var'] = df.var(axis=1)

stop = 0
start = 0
is_trigger = False
is_zero = False

for i in range(len(df['mean'])-1, 0, -1):
    if df['mean'][i] < HIGH_VOLT and not is_trigger:
        stop = df.iloc[:,0][i]
        is_trigger = True
    if (df['mean'][i] < LOW_VOLT or i == 1) and not is_zero:
        start = df.iloc[:,0][i]
        is_zero = True

plt.plot(df.iloc[:, 0], df['mean'], linewidth=2, linestyle="-", c="b")  # smooth by filter
plt.plot(df.iloc[:, 0], df['var'], linewidth=2, linestyle="-", c="r")  # smooth by filter
ax = plt.gca()
ax.axvline(stop, zorder=0)
ax.axhline(HIGH_VOLT, zorder=0)
text(stop, 1, str(stop), rotation=90, verticalalignment='center')
ax.axvline(start, zorder=0)
ax.axhline(LOW_VOLT, zorder=0)
text(start, 1, str(start), rotation=90, verticalalignment='center')
saturate_time = stop - start
plt.savefig('mean-var.png')
plt.show()


print(df)