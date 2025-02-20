from sys import argv
import sys
import os
from random import randint, choice, random

sys.path.append(os.path.abspath('../../'))
from tests_lib import apply_tests_range

apply_tests_range(argv[1], 10, lambda: (f"bubble {randint(1, 1000)} {random()}", "V"))
apply_tests_range(argv[1], 10, lambda: (f"shaker {randint(1, 1000)} {random()}", "V"))
apply_tests_range(argv[1], 10, lambda: (f"comb   {randint(1, 1000)} {random()}", "V"))
