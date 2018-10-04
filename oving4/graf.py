from matplotlib import pyplot as plt

len, t_def_quick, t_def_heap, t_dob_quick, t_dob_heap, t_sor_quick, t_sor_heap = [],[],[],[],[],[],[]
s = input()
while(s):
    [x.append(float(y)) for x, y in zip( [len, t_def_quick, t_def_heap, t_dob_quick, t_dob_heap, t_sor_quick, t_sor_heap ], s.split(" "))]
    s = input()

fig, axes = plt.subplots(1,3)

axes[0].plot(len, t_def_quick, 'r', label="quick")
axes[0].plot(len, t_def_heap, 'g', label="heap")
axes[0].set_title("Random data")
axes[0].set_xlabel("array size")
axes[0].set_ylabel("ns")

axes[1].plot(len, t_dob_quick, 'r', label="quick")
axes[1].plot(len, t_dob_heap, 'g', label="heap")
axes[1].set_title("Every value posted twice data")
axes[1].set_xlabel("array size")
axes[1].set_ylabel("ns")

axes[2].plot(len, t_sor_quick, 'r', label="quick")
axes[2].plot(len, t_sor_heap, 'g', label="heap")
axes[2].set_title("prev. data pre-sorted")
axes[2].set_xlabel("array size")
axes[2].set_ylabel("ns")

import matplotlib.patches as mpatches

red_patch = mpatches.Patch(color='r', label='quick')
blue_patch = mpatches.Patch(color='g', label='heap')
plt.legend(handles=[red_patch, blue_patch])

plt.show()

