#!/usr/bin/env python3

# defexportsgen <output .def> <input source files...>

import sys



out_def_filepath = ""

export_hint_str = "#pragma comment(linker, \"/EXPORT:\" __FUNCTION__ \"=\" __FUNCDNAME__)"
export_hint_str_len = len(export_hint_str)


fun_names = []


for i in range(len(sys.argv)):
    arg = sys.argv[i]
    if i == 0:
        # first argument is the script name
        continue
    elif i == 1:
        out_def_filepath = arg
        continue
    print(arg, flush=True)



    with open(arg, "r") as pp:
        pp_contents = pp.read()
        index = 0
        while (index := pp_contents.find(export_hint_str, index)) != -1:
            # Parse out the function name
            # 0 - look for '{'
            # 1 - look for ')'
            # 2 - look for '('
            # 3 - get the function name
            parser_state = 0
            fun_name = ""

            i = index
            while parser_state != 4:
                i -= 1
                c = pp_contents[i]
                if parser_state == 0:
                    if c.isspace():
                        continue
                    elif c == '{':
                        parser_state = 1
                    else:
                        print("Was looking for '{', got '{}' instead.".format(c))
                elif parser_state == 1:
                    if c.isspace():
                        continue
                    elif c == ')':
                        parser_state = 2
                    else:
                        print("Was looking for ')', got '{}' instead.".format(c))
                elif parser_state == 2:
                    if c == '(':
                        parser_state = 3
                elif parser_state == 3:
                    space = c.isspace()
                    if space and len(fun_name) == 0:
                        continue
                    elif space:
                        parser_state = 4
                    else:
                        fun_name = c + fun_name
                else:
                    pass

            index += export_hint_str_len
            fun_names += [fun_name]


with open(out_def_filepath, "w") as def_file:
    def_file.write("EXPORTS\n")
    for fun in fun_names:
        def_file.write("\t{}\n".format(fun))

print("Created export definitions file.")