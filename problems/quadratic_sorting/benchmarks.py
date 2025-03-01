import subprocess
from sys import argv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import os

COUNT_OF_MEASUREMENTS = int(1e5)

def get_times(N, orderliness, count):
    output = subprocess.run([argv[1], str(N), str(orderliness), str(count)], 
                            capture_output=True, text=True).stdout.split("\n")
    return float(output[0]), float(output[1]), float(output[2])

def get_benchmark_of_N(orderliness):
    Ns = []
    bubble_measurements = []
    shaker_measurements = []
    comb_measurements = []
    for pN in range(1, 6):
        N = 10 ** pN
        times = get_times(N, orderliness, COUNT_OF_MEASUREMENTS / N)
        Ns += [N]
        bubble_measurements += [times[0]]
        shaker_measurements += [times[1]]
        comb_measurements += [times[2]]
    plt.plot(Ns, bubble_measurements, label="bubble")
    plt.plot(Ns, shaker_measurements, label="shaker")
    plt.plot(Ns, comb_measurements, label="comb")
    plt.xlabel("N")
    plt.xscale("log")
    plt.ylabel("time, s")
    plt.yscale("log")
    plt.title(f"orderliness = {int(100 * orderliness)}%")
    plt.legend()
    plt.savefig(f"benchmarks/No{int(100 * orderliness)}.png")
    print(f"benchmarks/No{int(100 * orderliness)}.png")
    plt.clf()

def get_benchmark_of_orderliness(N, mc):
    os = []
    bubble_measurements = []
    shaker_measurements = []
    comb_measurements = []
    for o in range(0, 101, 10):
        times = get_times(N, o / 100, (mc * 100) if (o == 100) else mc)
        os += [o]
        bubble_measurements += [times[0]]
        shaker_measurements += [times[1]]
        comb_measurements += [times[2]]
        print("\r", o, "%", sep="", end="")
    plt.plot(os, bubble_measurements, label="bubble")
    plt.plot(os, shaker_measurements, label="shaker")
    plt.plot(os, comb_measurements, label="comb")
    plt.xlabel("orderliness, %")
    plt.ylabel("time, s")
    plt.title(f"N = {N}")
    plt.legend()
    plt.savefig(f"benchmarks/N{N}o.png")
    print(f"\rbenchmarks/N{N}o.png")
    plt.clf()

os.makedirs("benchmarks", exist_ok=True)
# get_benchmark_of_N(0)
# get_benchmark_of_N(0.2)
# get_benchmark_of_N(0.4)
# get_benchmark_of_N(0.6)
# get_benchmark_of_N(0.8)
# get_benchmark_of_N(.97)
# get_benchmark_of_orderliness(100, 10000)
# get_benchmark_of_orderliness(1000, 100)
# get_benchmark_of_orderliness(10000, 1)
