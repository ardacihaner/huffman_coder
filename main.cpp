#include "generate_tree.cpp"
#include "file_io.hpp"
#include <string.h>

/**
 * This file contains a parser for command line arguments and the main function
 * 
 */

// This function converts file contents into a string 
string get_file_content(string file_location) {
    vector<string> filevec = readFile(file_location);
    string file_content = "";
    for (string line: filevec) {
        file_content += line + "\n";
    }
    file_content.pop_back();
    return file_content;
}

// The main function
int main(int argc, char* argv[]) {
    BinaryTree main_tree; // The binary tree for main function
    // The binary tree that created from encoding is stored in "treedump" file. 
    bool is_dump_created = does_file_exist("treedump"); 
    if (argc == 1) {
        std::cerr << "Invalid usage!" << std::endl;
        return 1;
    }
    // Listing tree
    else if (strcmp(argv[1], "-l") == 0) {
        if (!is_dump_created) { // If there is no encoded tree, the program quits
            std::cerr << "There is no encoded data!\nQuiting...." << std::endl;
            return 1;
        }
        main_tree = generateTreeFromFile(readFile("treedump")); 
        std::cout << main_tree.printTree() << std::endl;
        return 0;
    } 
    // Printing Huffman encoding of given character
    else if (strcmp(argv[1], "-s") == 0) {
        if (!is_dump_created) { // If there is no encoded tree, the program quits
            std::cerr << "There is no encoded data!\nQuiting...." << std::endl;
            return 1;
        }
        main_tree = generateTreeFromFile(readFile("treedump")); 
        auto char_map = main_tree.getCharMap(); 
        std::cout << char_map.at(argv[2][0]) << std::endl;
        return 0;
    }
    // Taking input file and arguments
    else if (strcmp(argv[1], "-i") == 0) {
        string input_file = argv[2];
        string operation = argv[3];
        // Encoding operation
        if (operation == "-encode") {
            string file_content = get_file_content(input_file); // Getting string to be encoded from the file
            main_tree = generateTree(file_content); // Generating tree from file
            writeFile("treedump", main_tree.getFileDump()); // Storing generated tree into treedump file to use it later
            is_dump_created = true;
            string encoded_data = encode(main_tree, file_content); // Encoding the input with using the generated tree
            auto char_map = main_tree.getCharMap(); // Map that contains chars and their corresponding Huffman encodings
            std::cout << encoded_data << std::endl;
            return 0;
        }
        //  Decoding operation
        else if (operation == "-decode") {
            // Checking if tree exists
            if (!is_dump_created) {
                std::cerr << "There is no encoding data!\nQuiting...." << std::endl;
                return 1; 
            }
            string file_content = get_file_content(input_file);
            main_tree = generateTreeFromFile(readFile("treedump")); // Rebuilding the tree from treedump file
            std::cout << decode(main_tree, get_file_content(input_file)) << std::endl;
            return 0;
        }
    }
}