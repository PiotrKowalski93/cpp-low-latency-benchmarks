import numpy as np
import matplotlib
import matplotlib.pyplot as plt

latencies_unpinned = np.fromfile("./cpu_work_unpinned.bin", dtype=np.uint64)
latencies_unpinned.sort()
# print(latencies_unpinned)

print("Unpinned:")
print("p50:", np.percentile(latencies_unpinned, 50))
print("p99:", np.percentile(latencies_unpinned, 99))
print("p99.9:", np.percentile(latencies_unpinned, 99.9))
print("")

latencies_pinned = np.fromfile("./cpu_work_pinned.bin", dtype=np.uint64)
latencies_pinned.sort()
# print(latencies_pinned)

print("Pinned:")
print("p50:", np.percentile(latencies_pinned, 50))
print("p99:", np.percentile(latencies_pinned, 99))
print("p99.9:", np.percentile(latencies_pinned, 99.9))

# Plot
plt.subplot(2, 1, 1)
plt.hist(latencies_unpinned, bins=200)
plt.title("Unpinned")
plt.yscale("log")
plt.xlabel("Latency")
plt.ylabel("Count")

plt.subplot(2, 1, 2)
plt.hist(latencies_pinned, bins=200)
plt.title("Pinned")
plt.yscale("log")
plt.xlabel("Latency")
plt.ylabel("Count")

plt.show()