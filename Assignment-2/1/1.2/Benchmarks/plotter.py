import matplotlib.pyplot as plt
import numpy as np
import csv


def get_benchmarks() -> list[dict[str, float]]:
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

    return benchmarks


def get_process_times(benchmarks: list[dict[str, float]]) -> tuple[list[float], list[float], list[float]]:
    Pr_A = [benchmarks[i]["A"] for i in range(len(benchmarks))]
    Pr_B = [benchmarks[i]["B"] for i in range(len(benchmarks))]
    Pr_C = [benchmarks[i]["C"] for i in range(len(benchmarks))]

    return Pr_A, Pr_B, Pr_C


def set_figure() -> None:
    plt.figure(figsize=(10, 5))
    plt.axhline(y=0, color="black", linewidth=2, zorder=3)
    plt.axvline(x=0, color="black", linewidth=2, zorder=3)


def plot() -> None:
    """Plot the benchmarks for 3 processs on fixed priorities for n trials"""

    Pr_A, Pr_B, Pr_C = get_process_times(get_benchmarks())

    set_figure()

    plt.plot(np.arange(1-0.2, len(benchmarks)+1-0.2, 1), Pr_A, width=0.2, label="Pr-A", color="#971B00", zorder=2)
    plt.plot(np.arange(1, len(benchmarks)+1, 1), Pr_B, width=0.2, label="Pr-B", color="#001787", zorder=2)
    plt.plot(np.arange(1+0.2, len(benchmarks)+1+0.2, 1), Pr_C, width=0.2, label="Pr-C", color="#007B07", zorder=2)

    plt.axhline(y=sum(Pr_A)/len(Pr_A), linestyle="--", color="#FF2E00")
    plt.axhline(y=sum(Pr_B)/len(Pr_B), linestyle="--", color="#002BFF")
    plt.axhline(y=sum(Pr_C)/len(Pr_C), linestyle="--", color="#00FF0F")

    plt.xlabel("Number of Trials")
    plt.xticks(range(1, len(benchmarks)+1))
    plt.ylabel("Time of execution (in seconds)")

    plt.title("Priorities: Pr-A=5, Pr-B=20, Pr-C=30\nNumber of cores = 4")
    plt.grid(True, zorder=0)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot()