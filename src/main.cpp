#include <iostream>
#include "cli11/CLI11.hpp"

int main(int argc, char** argv) {
    CLI::App app{"Welcome to Gnossia"};
    argv = app.ensure_utf8(argv);

    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");

    CLI11_PARSE(app, argc, argv);
    return 0;
}
