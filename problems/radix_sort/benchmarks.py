import subprocess
from sys import argv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import os

COUNT_OF_MEASUREMENTS_FACTOR = int(5e6)

def get_times(N, orderliness, count, digits):
    output = subprocess.run([argv[1], str(N), str(orderliness), str(count), str(digits)], 
                            capture_output=True, text=True).stdout.split("\n")
    return float(output[0]), float(output[1])

def get_benchmark_of_N(orderliness, digits):
    Ns = []
    radix_measurements = []
    std_measurements = []
    for pN in range(1, 7):
        N = 10 ** pN
        times = get_times(N, orderliness, COUNT_OF_MEASUREMENTS_FACTOR / N, digits)
        Ns += [N]
        radix_measurements += [times[0]]
        std_measurements += [times[1]]
    plt.plot(Ns, radix_measurements, label="radix")
    plt.plot(Ns, std_measurements, label="std::sort")
    plt.xlabel("N")
    plt.xscale("log")
    plt.ylabel("time, s")
    plt.yscale("log")
    plt.title(f"orderliness = {int(100 * orderliness)}%, digits = {digits}")
    plt.legend()
    plt.savefig(f"benchmarks/No{int(100 * orderliness)}d{digits}.png")
    print(f"benchmarks/No{int(100 * orderliness)}d{digits}.png")
    plt.clf()

def get_benchmark_of_DC(orderliness, N):
    ds = []
    radix_measurements = []
    std_measurements = []
    for d in range(1, 10):
        times = get_times(N, orderliness, COUNT_OF_MEASUREMENTS_FACTOR / N, d)
        ds += [d]
        radix_measurements += [times[0]]
        std_measurements += [times[1]]
    plt.plot(ds, radix_measurements, label="radix")
    plt.plot(ds, std_measurements, label="std::sort")
    plt.xlabel("digits count")
    plt.ylabel("time, s")
    plt.title(f"orderliness = {int(100 * orderliness)}%, N = {N}")
    plt.legend()
    plt.savefig(f"benchmarks/N{N}o{int(100 * orderliness)}d.png")
    print(f"benchmarks/N{N}o{int(100 * orderliness)}d.png")
    plt.clf()

def get_benchmark_of_orderliness(N, digits):
    os = []
    radix_measurements = []
    std_measurements = []
    for o in range(0, 100, 5):
        times = get_times(N, o * 0.01, COUNT_OF_MEASUREMENTS_FACTOR / N, digits)
        os += [o]
        radix_measurements += [times[0]]
        std_measurements += [times[1]]
    plt.plot(os, radix_measurements, label="radix")
    plt.plot(os, std_measurements, label="std::sort")
    plt.xlabel("orderliness")
    plt.ylabel("time, s")
    plt.title(f"N = {N}, digits = {digits}")
    plt.legend()
    plt.savefig(f"benchmarks/N{N}od{digits}.png")
    print(f"benchmarks/N{N}od{digits}.png")
    plt.clf()

os.makedirs("benchmarks", exist_ok=True)
get_benchmark_of_N(0, 9)
get_benchmark_of_N(0.5, 9)
get_benchmark_of_N(1, 9)
get_benchmark_of_DC(0.00, 10000)
get_benchmark_of_DC(0.33, 10000)
get_benchmark_of_DC(0.66, 10000)
get_benchmark_of_DC(0.33, 100000)
get_benchmark_of_DC(0.33, 1000000)
get_benchmark_of_orderliness(100000, 3)
get_benchmark_of_orderliness(100000, 7)
