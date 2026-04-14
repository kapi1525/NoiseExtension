#include <cstdio>
#include <cstdlib>
#include <cctype>



// jsonminify <input> <output>

const char* get_arg(int &argc, char const **&argv) {
    if(argc <= 0) {
        std::fprintf(stderr, "Expected an argument.\n\n");
        std::exit(-1);
    }

    const char* ret = *argv;

    argc--;
    argv = argv + 1;
    return ret;
}

int main(int argc, char const *argv[]) {
    (void)get_arg(argc, argv);      // First is the program name

    // Its only a build tool so asume all arguments are fine
    const char* in_path = get_arg(argc, argv);
    const char* out_path = get_arg(argc, argv);

    FILE *in, *out;

    in = std::fopen(in_path, "rb");
    out = std::fopen(out_path, "wb");

    if(!in || !out) {
        std::perror("fopen failed");
        return -1;
    }

    // remove all whitespace thats outside strings
    bool inside_string = false;
    bool escape_sequence = false;
    bool inside_comment = false;

    for(int i = 0;;i++) {
        int c = std::fgetc(in);

        // Remove utf-8 BOM. sdk doesnt expect it to be there.
        if((i == 0 && c == 0xEF) || (i == 1 && c == 0xBB) || (i == 2 && c == 0xBF)) {
            continue;
        }

        if(c == EOF) {
            break;
        }

        // Remove comments
        if(!inside_string && c == '/') {
            inside_comment = true;
        }

        if(inside_comment) {
            if(c == '\n') {
                inside_comment = false;
            }
            continue;
        }

        // Remove whitespace outside strings
        if(!inside_string && std::isspace(c)) {
            continue;
        }

        if(c == '"') {
            if(!inside_string) {
                inside_string = true;
            } else if(inside_string && !escape_sequence) {
                inside_string = false;
            }
        }

        escape_sequence = false;
        if(c == '\\') {
            escape_sequence = true;
        }

        std::fputc(c, out);
    }

    std::fclose(in);
    std::fclose(out);

    return 0;
}
