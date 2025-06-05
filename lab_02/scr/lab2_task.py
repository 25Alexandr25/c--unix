import numpy as np
import time
from random import randint


def expression(x):
    result = x ^ 2 - x ^ 2 + x * 4 - x * 5 + x - x
    return result


def main():
    recalculate = "Y"
    RAND_MAX = 32767
    while recalculate == "Y":
        n = int(input("Enter the number of calculations:"))
        if isinstance(n, int):
            start = time.time()
            for i in range(n):
                x = randint(0, RAND_MAX)
                result = expression(x)
            end = time.time()
        else:
            print("Invalid input type, calculation denied")
            return 0
        seconds = end - start
        print("Time spent for", n, "calculations is", round(seconds, 5), "seconds")
        print("Evaluate again? \n[Y/N]")
        recalculate = input()
        while 1 == 1:
            if recalculate == "Y" or recalculate == "N":
                break
            print("Try again!")
            print("Evaluate again? \n[Y/N]")
            recalculate = input()


main()
