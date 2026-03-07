import numpy as np
import matplotlib
import matplotlib.pyplot as plt

latencies_unpinned = np.fromfile("./cpu_work_unpinned.bin", dtype=np.uint64)
latencies_unpinned.sort()

print("Unpinned:")
print("p50:", np.percentile(latencies_unpinned, 50))
print("p99:", np.percentile(latencies_unpinned, 99))
print("p99.9:", np.percentile(latencies_unpinned, 99.9))
print("Max:", latencies_unpinned[-1] )
print("")

latencies_pinned = np.fromfile("./cpu_work_pinned.bin", dtype=np.uint64)
latencies_pinned.sort()

print("Pinned:")
print("p50:", np.percentile(latencies_pinned, 50))
print("p99:", np.percentile(latencies_pinned, 99))
print("p99.9:", np.percentile(latencies_pinned, 99.9))
print("Max:", latencies_pinned[-1] )

# Plot
lat_unique_unpinned, counts_unpinned = np.unique(latencies_unpinned, return_counts=True)

plt.subplot(2, 1, 1)
plt.plot(lat_unique_unpinned, counts_unpinned)
plt.title("Unpinned")
plt.yscale("log")
plt.xlabel("Latency")
plt.ylabel("Count")
plt.xlim(0, np.percentile(lat_unique_unpinned, 99.9))

lat_unique_pinned, counts_pinned = np.unique(latencies_pinned, return_counts=True)

plt.subplot(2, 1, 2)
plt.plot(lat_unique_pinned, counts_pinned)
plt.title("Pinned")
plt.yscale("log")
plt.xlabel("Latency")
plt.ylabel("Count")
plt.xlim(0, np.percentile(lat_unique_pinned, 99.9))

plt.show()