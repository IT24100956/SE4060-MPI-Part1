import matplotlib.pyplot as plt

# Replace with your recorded execution times in seconds
processors =
time_ex2 = [0.038, 0.020, 0.011, 0.007]
time_ex3 = [0.280, 0.145, 0.076, 0.042]

speedup_ex2 = [time_ex2[0] / t for t in time_ex2]
speedup_ex3 = [time_ex3[0] / t for t in time_ex3]
ideal_speedup = processors

# Graph 1: Time vs Number of Processors
plt.figure(figsize=(8, 5))
plt.plot(processors, time_ex2, marker='o', label='Ex 2 (Summation)')
plt.plot(processors, time_ex3, marker='s', label='Ex 3 (Monte Carlo Pi)')
plt.xlabel('Number of Processors')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs Number of Processors')
plt.grid(True)
plt.legend()
plt.savefig('time_vs_processors.png')
plt.close()

# Graph 2: Speedup vs Number of Processors
plt.figure(figsize=(8, 5))
plt.plot(processors, speedup_ex2, marker='o', label='Ex 2 Speedup')
plt.plot(processors, speedup_ex3, marker='s', label='Ex 3 Speedup')
plt.plot(processors, ideal_speedup, '--', color='gray', label='Ideal Linear Speedup')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup (T1 / Tp)')
plt.title('Speedup vs Number of Processors')
plt.grid(True)
plt.legend()
plt.savefig('speedup_vs_processors.png')
plt.close()

print("Graphs successfully generated: time_vs_processors.png, speedup_vs_processors.png")
