import matplotlib.pyplot as plt
import numpy as np
import csv


def get_benchmarks() -> list[dict[str, float]]:
    with open(r"./1/1.2/Benchmarks/benchmark.csv") as file:
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


def plot2() -> None:
    """Plot the benchmarks for 3 processes on variable priorities"""

    benchmarks = get_benchmarks()
    Pr_A, Pr_B, Pr_C = get_process_times(benchmarks)

    A_priorities = [0, 0, 0, 0, 0, 0]
    B_priorities = [90, 50, 10, 40, 99, 10]
    C_priorities = [20, 20, 60, 40, 10, 99]

    set_figure()

    plt.bar(np.arange(1-0.2, len(benchmarks)+1-0.2, 1), Pr_A, width=0.2, label="Pr-A", color="#971B00", zorder=2)
    plt.bar(np.arange(1, len(benchmarks)+1, 1), Pr_B, width=0.2, label="Pr-B", color="#001787", zorder=2)
    plt.bar(np.arange(1+0.2, len(benchmarks)+1+0.2, 1), Pr_C, width=0.2, label="Pr-C", color="#007B07", zorder=2)

    # write A priorities on top of bars
    for i in range(len(A_priorities)):
        plt.text(i+1-0.2, 0.25, A_priorities[i], ha="center", va="bottom", color="white", size=7, zorder=4)

    # write B priorities on top of bars
    for i in range(len(B_priorities)):
        plt.text(i+1, 0.25, B_priorities[i], ha="center", va="bottom", color="white", size=7, zorder=4)

    # write C priorities on top of bars
    for i in range(len(C_priorities)):
        plt.text(i+1+0.2, 0.25, C_priorities[i], ha="center", va="bottom", color="white", size=7, zorder=4)

    plt.xlabel("Number of Trials")
    plt.xticks(range(1, len(benchmarks)+1))
    plt.ylabel("Time of execution (in seconds)")

    plt.title("Number of CPU Cores=2")
    plt.grid(True, zorder=0)
    plt.legend()
    plt.show()


def plot3() -> None:
    """Create 10 plots for 3 processes on variable priorities
    X-AXIS: Process Priority
    Y-AXIS: Time of execution (in seconds)"""

    benchmarks = get_benchmarks()
    Pr_A, Pr_B, Pr_C = get_process_times(benchmarks)

    A_priorities = [0, 0, 0, 0, 0, 0]
    B_priorities = [90, 50, 10, 40, 99, 10]
    C_priorities = [20, 20, 60, 40, 10, 99]

    for i in range(len(benchmarks)):
        set_figure()

        priorities = [A_priorities[i], B_priorities[i], C_priorities[i]]
        arranged = sorted([
            [Pr_A[i], A_priorities[i], "Pr-A", "#971B00"],
            [Pr_B[i], B_priorities[i], "Pr-B", "#001787"],
            [Pr_C[i], C_priorities[i], "Pr-C", "#007B07"],
        ], key=(lambda x: x[0])
        )

        for i, (time, priority, label, color) in enumerate(arranged):
            plt.bar(priority, time, width=0.1*(max(priorities)-min(priorities)), label=label, color=color, zorder=5-i)

        plt.xlabel("Process Priority")

        plt.ylabel("Time of execution (in seconds)")
        plt.ylim(-1, max(Pr_A[i], Pr_B[i], Pr_C[i])+1)

        plt.title("Number of CPU Cores=2")
        plt.grid(True, zorder=0)
        plt.legend()
        plt.show()


if __name__ == "__main__":
    plot3()