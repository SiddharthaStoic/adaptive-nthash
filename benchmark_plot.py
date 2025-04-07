import subprocess
import time
import matplotlib.pyplot as plt

iterations = 1000
adaptive_times = []
normal_times = []

print("Running adaptive_benchmark.exe...")
for _ in range(iterations):
    start = time.perf_counter()
    subprocess.run(["./build/adaptive_benchmark.exe"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    end = time.perf_counter()
    adaptive_times.append(end - start)

print("Running normal_benchmark.exe...")
for _ in range(iterations):
    start = time.perf_counter()
    subprocess.run(["./build/normal_benchmark.exe"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    end = time.perf_counter()
    normal_times.append(end - start)

plt.figure(figsize=(12, 6))
plt.plot(adaptive_times, label='Adaptive Hash', alpha=0.7)
plt.plot(normal_times, label='Normal ntHash', alpha=0.7)
plt.xlabel('Iteration')
plt.ylabel('Time (s)')
plt.title('ntHash vs Adaptive Hashing Benchmark (1000 runs)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("benchmark_comparison.png", dpi=300)
plt.show()