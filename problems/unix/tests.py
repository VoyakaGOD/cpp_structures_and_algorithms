from random import randint, choice
from sys import argv
import string
import sys
import os

sys.path.append(os.path.abspath('../../'))
from tests_lib import apply_tests_range

def generate_path():
    path = "/root/"
    rnd = 0
    while rnd != 20:
        rnd = randint(1, 20)
        if rnd == 1:
            path += "./"
        elif rnd == 2:
            path += "../"
        elif rnd >= 3 and rnd <= 6:
            path += "/"
        else:
            path += choice(string.ascii_letters)
    return path, os.path.normpath(path).replace("\\", "/")

apply_tests_range(argv[1], 50, generate_path)
