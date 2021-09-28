# take a string and an integer from the command line and produce a text file
# with an enumerated list of the string from 1 to n.

import os
import sys

args = sys.argv
if len(args) < 3:
    print("Not enough arguments: Please provide a string and an int")

prepend_string = args[1]
num = int(args[2])
append_string = args[3] if (len(args) >= 4) else ""

list_for_file = ""

for i in range(0, num):
    list_for_file += "{}{}{}{}".format(prepend_string, i, append_string, (", " if i != (num - 1) else ""))
    if (i+1) % 4 == 0:
        list_for_file += "\n"

f = open("numbered_names.txt", "w")
f.write(list_for_file)
f.close()


