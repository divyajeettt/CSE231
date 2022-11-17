import matplotlib.pyplot as plt
import csv


def plot() -> None:
    with open(r"./1/1.1/Benchmarks/benchmark.csv") as file:
        reader = csv.reader(file, delimiter="\t")
        data = list(reader)

    benchmarks = []
    for i in range(len(data)):
        benchmarks.append({
            data[i][0]: float(data[i][1]),
            data[i][2]: float(data[i][3]),
            data[i][4]: float(data[i][5]),
        })
        del data[i][-1]

    # print(benchmarks)

    Thr_A = [benchmarks[i]["A"] for i in range(len(benchmarks))]
    Thr_B = [benchmarks[i]["B"] for i in range(len(benchmarks))]
    Thr_C = [benchmarks[i]["C"] for i in range(len(benchmarks))]

    plt.figure(figsize=(10, 5))

    plt.axhline(y=0, color="black", linewidth=2)
    plt.axvline(x=0, color="black", linewidth=2)

    plt.plot(range(1, len(benchmarks)+1), Thr_A, marker=".", label="Thr-A", color="#971B00")
    plt.plot(range(1, len(benchmarks)+1), Thr_B, marker=".", label="Thr-B", color="#001787")
    plt.plot(range(1, len(benchmarks)+1), Thr_C, marker=".", label="Thr-C", color="#007B07")

    plt.axhline(y=sum(Thr_A)/len(Thr_A), linestyle="--", color="#FF2E00")
    plt.axhline(y=sum(Thr_B)/len(Thr_B), linestyle="--", color="#002BFF")
    plt.axhline(y=sum(Thr_C)/len(Thr_C), linestyle="--", color="#00FF0F")

    plt.xlabel("Number of trials")
    plt.xticks(range(1, len(benchmarks)+1))
    plt.ylabel("Time of execution (in seconds)")
    plt.yticks(range(1, 11))

    plt.title("Benchmark with priorities: A=0, B=1, C=1")
    plt.grid(True)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot()