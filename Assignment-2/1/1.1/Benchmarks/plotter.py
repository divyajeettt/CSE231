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


def get_thread_times(benchmarks: list[dict[str, float]]) -> tuple[list[float], list[float], list[float]]:
    Thr_A = [benchmarks[i]["A"] for i in range(len(benchmarks))]
    Thr_B = [benchmarks[i]["B"] for i in range(len(benchmarks))]
    Thr_C = [benchmarks[i]["C"] for i in range(len(benchmarks))]

    return Thr_A, Thr_B, Thr_C


def set_figure() -> None:
    plt.figure(figsize=(10, 5))
    plt.axhline(y=0, color="black", linewidth=2, zorder=3)
    plt.axvline(x=0, color="black", linewidth=2, zorder=3)


def plot1() -> None:
    """Plot the benchmarks for 3 threads on fixed priorities for n trials"""

    Thr_A, Thr_B, Thr_C = get_thread_times(get_benchmarks())

    set_figure()

    plt.bar(np.arange(1-0.2, len(benchmarks)+1-0.2, 1), Thr_A, width=0.2, label="Thr-A", color="#971B00", zorder=2)
    plt.bar(np.arange(1, len(benchmarks)+1, 1), Thr_B, width=0.2, label="Thr-B", color="#001787", zorder=2)
    plt.bar(np.arange(1+0.2, len(benchmarks)+1+0.2, 1), Thr_C, width=0.2, label="Thr-C", color="#007B07", zorder=2)

    plt.axhline(y=sum(Thr_A)/len(Thr_A), linestyle="--", color="#FF2E00")
    plt.axhline(y=sum(Thr_B)/len(Thr_B), linestyle="--", color="#002BFF")
    plt.axhline(y=sum(Thr_C)/len(Thr_C), linestyle="--", color="#00FF0F")

    plt.xlabel("Number of Trials")
    plt.xticks(range(1, len(benchmarks)+1))
    plt.ylabel("Time of execution (in seconds)")
    plt.yticks(range(1, 5))
    plt.ylim(-1, 5)

    plt.title("Number of CPU Cores=4")
    plt.grid(True, zorder=0)
    plt.legend()
    plt.show()


def plot2() -> None:
    """Plot the benchmarks for 3 threads on variable priorities"""

    Thr_A, Thr_B, Thr_C = get_thread_times(get_benchmarks())

    A_priorities = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    B_priorities = [1, 10, 10, 80, 60, 40, 40, 40, 80, 99]
    C_priorities = [1, 1, 20, 40, 40, 40, 60, 80, 80, 80]

    set_figure()

    plt.bar(np.arange(1-0.2, len(benchmarks)+1-0.2, 1), Thr_A, width=0.2, label="Thr-A", color="#971B00", zorder=2)
    plt.bar(np.arange(1, len(benchmarks)+1, 1), Thr_B, width=0.2, label="Thr-B", color="#001787", zorder=2)
    plt.bar(np.arange(1+0.2, len(benchmarks)+1+0.2, 1), Thr_C, width=0.2, label="Thr-C", color="#007B07", zorder=2)

    # write A priorities on top of bars
    for i in range(len(A_priorities)):
        plt.text(i+1-0.2, 0.25, A_priorities[i], ha="center", va="bottom", color="white", size=7, zorder=4)

    # write B priorities on top of bars
    for i in range(len(B_priorities)):
        plt.text(i+1, 0.25, B_priorities[i], ha="ce   nter", va="bottom", color="white", size=7, zorder=4)

    # write C priorities on top of bars
    for i in range(len(C_priorities)):
        plt.text(i+1+0.2, 0.25, C_priorities[i], ha="center", va="bottom", color="white", size=7, zorder=4)

    plt.xlabel("Number of Trials")
    plt.xticks(range(1, len(benchmarks)+1))
    plt.ylabel("Time of execution (in seconds)")
    plt.yticks(range(1, 5))
    plt.ylim(-1, 5)

    plt.title("Number of CPU Cores=4")
    plt.grid(True, zorder=0)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot()