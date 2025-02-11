from random import randint, choice
from sys import argv
import string
import sys
import os

sys.path.append(os.path.abspath('../../'))
from tests_lib import test

test(argv[1], "visit google.com\nback 2\nback 1\nforward 1\nshow", 
     "homepage\ngoogle.com\nhomepage\nhomepage\ngoogle.com")
