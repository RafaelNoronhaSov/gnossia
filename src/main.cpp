#include <iostream>
#include <fstream>
#include <string>
#include "../include/CLI11/CLI11.hpp"

struct Note {
    std::string title;
    std::string description;
};

void createNote(const std::string& title, bool edit = false) {
    std::ofstream file(title + ".txt");
    if (!file) {
        std::cerr << "Erro ao criar a nota.\n";
        return;
    }
    file << "Título: " << title << "\nDescrição: \n";
    file.close();
    std::cout << "Nota criada: " << title << "\n";

    if (edit) {
        std::string command = "vim \"" + title + ".txt\"";
        system(command.c_str());
    }
}

void editNote(const std::string& title) {
    std::string command = "vim " + title + ".txt";
    system(command.c_str());
}

void deleteNote(const std::string& title) {
    if (remove((title + ".txt").c_str()) != 0) {
        std::cerr << "Erro ao deletar a nota.\n";
    } else {
        std::string command = "rm \"" + title + ".txt\"";
    }
}

int main(int argc, char** argv) {
    CLI::App app{"Bem-vindo ao Gnossia"};
    argv = app.ensure_utf8(argv);

    std::string newTitle;
    std::string existingTitle;
    bool editFlag = false;
    bool deleteFlag = false;

    app.add_option("-n", newTitle, "Cria uma nova nota");

    app.add_flag("-e, --edit", editFlag, "Edita a nota após criar");
    app.add_flag("-d, --delete", deleteFlag, "Deleta a nota");

    app.add_option("title", existingTitle, "Nota a editar ou deletar")->take_last();

    CLI11_PARSE(app, argc, argv);

    if (!newTitle.empty()) {
        createNote(newTitle, editFlag);
    } else if (!existingTitle.empty()) {
        if (deleteFlag) {
            deleteNote(existingTitle);
        } else {
            editNote(existingTitle);
        }
    } else {
        std::cerr << "Nenhuma ação realizada. Use --help para mais informações.\n";
    }

    return 0;
}
