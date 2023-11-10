import pandas
import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline
from scipy.signal import lfilter
from matplotlib.pyplot import text

FILENAME = ['./20k_1.csv', './20k_2.csv', './20k_3.csv', './20k_4.csv', './50pF_20k_3.csv']
LOW_VOLT = 0.8
HIGH_VOLT = 2.0

for f in FILENAME:
    csv = pandas.read_csv(f)
    df = pandas.DataFrame(csv)

    df = df.drop(['Record Length', '2500', 'Points', 'Unnamed: 5'],axis=1)

    n = 15  # the larger n is, the smoother curve will be
    b = [1.0 / n] * n
    a = 1
    yy = lfilter(b, a, df.iloc[:, 1])
    ax = plt.gca()
    plt.plot(df.iloc[:, 0], yy, linewidth=2, linestyle="-", c="b")  # smooth by filter
    
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
    

    ax.axvline(stop, zorder=0)
    ax.axhline(HIGH_VOLT, zorder=0)
    text(stop, 1, str(stop), rotation=90, verticalalignment='center')
    ax.axvline(start, zorder=0)
    ax.axhline(LOW_VOLT, zorder=0)
    text(start, 1, str(start), rotation=90, verticalalignment='center')
    saturate_time = stop - start
    plt.savefig(f[:-4] + '-' + str(saturate_time) + '.png')
    plt.show()
    


    #df.plot()

    #plt.show()
