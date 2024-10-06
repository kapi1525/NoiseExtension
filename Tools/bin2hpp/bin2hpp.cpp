#include <cstdio>
#include <cstdlib>



// bin2hpp <binary file path> <output file> <char array name> <variable with array length name>

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
    const char* array_name = get_arg(argc, argv);
    const char* array_size_name = get_arg(argc, argv);

    FILE *in, *out;
    unsigned int bytes = 0;

    in = std::fopen(in_path, "rb");
    out = std::fopen(out_path, "wb");

    if(!in || !out) {
        perror("fopen failed");
        return -1;
    }

    std::fprintf(out, "unsigned char %s[] = {\n", array_name);

    for(;;) {
        int c = fgetc(in);

        if(c != EOF) {
            std::fprintf(out, "    %u,\n", c);
            bytes++;
        } else {
            std::fprintf(out, "};\n");
            std::fprintf(out, "unsigned int %s = %u;", array_size_name, bytes);
            break;
        }
    }

    std::fclose(in);
    std::fclose(out);

    return 0;
}
