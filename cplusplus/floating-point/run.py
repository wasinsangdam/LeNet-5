#!/usr/bin/env python3

import os
import random as rd
import time

def run() :
    input_arg = '--input=../../data/input/input_'

    for i in range(10) :
        random_number = rd.randrange(0, 10000)
        os.system('clear')
        os.system('./main ' + input_arg + str(random_number) + '.data')
        time.sleep(1)

if __name__ == "__main__" :
    run()
