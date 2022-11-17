import matplotlib.pyplot as plt
import csv


def plot() -> None:
    with open(r"./1/1.1/benchmark.csv") as file:
        reader = csv.reader(file)
        data = list(reader)

    print(data)

if __name__ == "__main__":
    plot()