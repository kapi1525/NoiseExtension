#!/usr/bin/env python3

# jsonminify <input> <output>

import sys



in_path = ""
out_path = ""

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


file_in = open(in_path, "rb")
file_out = open(out_path, "w")

# remove all whitespace thats outside strings
inside_string = False
escape_sequence = False
inside_comment = False

i = -1
for c in file_in.read():
    i += 1
    # Remove utf-8 BOM. sdk doesnt expect it to be there.
    if ((i == 0 and c == 0xEF) or (i == 1 and c == 0xBB) or (i == 2 and c == 0xBF)):
        continue

    c = chr(c)

    # Remove comments
    if not inside_string and c == '/':
        inside_comment = True

    if inside_comment:
        if c == "\n":
            inside_comment = False
        continue


    # Remove whitespace outside strings
    if not inside_string and c.isspace():
        continue

    if c == '"':
        if not inside_string:
            inside_string = True
        elif inside_string and not escape_sequence:
            inside_string = False

    escape_sequence = False
    if c == '\\':
        escape_sequence = True

    file_out.write(c)

file_in.close()
file_out.close()