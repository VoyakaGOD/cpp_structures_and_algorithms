from sys import argv
import sys
import os

sys.path.append(os.path.abspath('../../'))
from tests_lib import test

print("Test 1:")
test(argv[1], """visit google.com
back 2
back 1
forward 1
show
exit""", 
"""homepage
google.com
homepage
homepage
google.com""")

print("Test 2:")
test(argv[1], """visit google.com
visit linux.org
visit youtube.com
back 1
visit facebook.com
back 1
forward 1
show
exit""", 
"""homepage
google.com
linux.org
youtube.com
linux.org
facebook.com
linux.org
facebook.com""")

print("Test 3:")
test(argv[1], """visit google.com
visit linux.org
forward 1
back 1
back 1
show
exit""", 
"""homepage
google.com
linux.org
linux.org
google.com
homepage""")
