import matplotlib.pyplot as plt
import csv


def plot() -> None:
    with open(r"./1/1.1/benchmark.csv") as file:
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

    plt.axhline(y=0, color="black", linewidth=2)
    plt.axvline(x=0, color="black", linewidth=2)

    plt.plot(range(1, len(benchmarks)+1), Thr_A, label="A")
    plt.plot(range(1, len(benchmarks)+1), Thr_B, label="B")
    plt.plot(range(1, len(benchmarks)+1), Thr_C, label="C")

    plt.xlabel("Number of trials")
    plt.ylabel("Time of execution (in seconds)")

    plt.xticks(range(1, len(benchmarks)+1))
    plt.yticks(range(1, 11))
    plt.grid(True)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot()