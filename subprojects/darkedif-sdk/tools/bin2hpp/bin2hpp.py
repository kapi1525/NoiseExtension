#!/usr/bin/env python3

# bin2hpp <binary file path> <output file> <char array name> <variable with array length name>

import sys



in_path = ""
out_path = ""
array_name = ""
array_size_name = ""

for i in range(len(sys.argv)):
    arg = sys.argv[i]
    if i == 0:
        # first argument is the script name
        continue
    elif i == 1:
        in_path = arg
        continue
    elif i == 2:
        out_path = arg
        continue
    elif i == 3:
        array_name = arg
        continue
    elif i == 4:
        array_size_name = arg
        continue

file_in = open(in_path, "rb")
file_out = open(out_path, "w")

file_out.write("unsigned char {}[]".format(array_name) + " = {\n")
sz = 0

for c in file_in.read():
    file_out.write("    {},\n".format(c))
    sz += 1

file_out.write("};\n")
file_out.write("unsigned int {} = {};".format(array_size_name, sz))

file_in.close()
file_out.close()