import pandas as pd

# Load the benchmark data
df = pd.read_csv("benchmark_times.csv")

# Compute averages
avg_adaptive = df["Adaptive_Hash_Time"].mean()
avg_normal = df["Normal_ntHash_Time"].mean()

# Compute percentage speedup
speedup = ((avg_normal - avg_adaptive) / avg_normal) * 100

print(f"Average Adaptive Hash Time: {avg_adaptive:.6f} s")
print(f"Average Normal ntHash Time: {avg_normal:.6f} s")
print(f"Percentage Speedup: {speedup:.2f}%")