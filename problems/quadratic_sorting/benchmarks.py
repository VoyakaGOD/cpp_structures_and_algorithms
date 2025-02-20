import subprocess
from sys import argv
import matplotlib.pyplot as plt
import os

COUNT_OF_MEASUREMENTS = 15

def get_times(N, orderliness, count):
    output = subprocess.run([argv[1], str(N), str(orderliness), str(count)], 
                            capture_output=True, text=True).stdout.split("\n")
    return float(output[0]), float(output[1]), float(output[2])

Ns = []
bubble_measurements = []
shaker_measurements = []
comb_measurements = []
for N in range(300, 3000, 500):
    times = get_times(N, 0.5, COUNT_OF_MEASUREMENTS)
    Ns += [N]
    bubble_measurements += [times[0]]
    shaker_measurements += [times[1]]
    comb_measurements += [times[2]]

os.makedirs("benchmarks", exist_ok=True)
plt.plot(Ns, bubble_measurements, label="bubble")
plt.plot(Ns, shaker_measurements, label="shaker")
plt.plot(Ns, comb_measurements, label="comb")
plt.xlabel("N")
plt.ylabel("time, s")
plt.legend()
plt.savefig("benchmarks/No5.png")
