from matplotlib import pyplot as plt

len, t_def_1piv, t_def_2piv, t_def_ipiv, t_dob_1piv, t_dob_2piv, t_dob_ipiv, t_sor_1piv, t_sor_2piv, t_sor_ipiv = [],[],[],[],[],[],[],[],[],[]
s = input()
while(s):
    [x.append(float(y)) for x, y in zip([len, t_def_1piv, t_def_2piv, t_def_ipiv, t_dob_1piv, t_dob_2piv, t_dob_ipiv, t_sor_1piv, t_sor_2piv, t_sor_ipiv], s.split(" "))]
    s = input()

fig, axes = plt.subplots(1,3)

axes[0].plot(len, t_def_1piv, 'r', label="singlepivot")
axes[0].plot(len, t_def_2piv, 'b', label="doublepivot")
axes[0].plot(len, t_def_ipiv, 'g', label="insertpivot")
axes[0].set_title("Random data")
axes[0].set_xlabel("array size")
axes[0].set_ylabel("ns")

axes[1].plot(len, t_dob_1piv, 'r', label="singlepivot")
axes[1].plot(len, t_dob_2piv, 'b', label="doublepivot")
axes[1].plot(len, t_dob_ipiv, 'g', label="insertpivot")
axes[1].set_title("Every value posted twice data")
axes[1].set_xlabel("array size")
axes[1].set_ylabel("ns")

axes[2].plot(len, t_sor_1piv, 'r', label="singlepivot")
axes[2].plot(len, t_sor_2piv, 'b', label="doublepivot")
axes[2].plot(len, t_sor_ipiv, 'g', label="insertpivot")
axes[2].set_title("prev. data pre-sorted")
axes[2].set_xlabel("array size")
axes[2].set_ylabel("ns")

import matplotlib.patches as mpatches

red_patch = mpatches.Patch(color='r', label='single pivot')
blue_patch = mpatches.Patch(color='b', label='double pivot')
green_patch = mpatches.Patch(color='g', label='insert/double pivot')
plt.legend(handles=[red_patch, blue_patch, green_patch])

plt.show()

