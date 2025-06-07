#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>

#include "proj.tab.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Support/FileSystem.h"

llvm::LLVMContext context;
llvm::Module *module = nullptr;
llvm::IRBuilder<> *builder = nullptr;
std::map<std::string, llvm::Value*> symbolTable;

extern FILE *yyin;
extern int yyparse();

int main(int argc, char **argv) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    std::string filename(argv[1]);
    if (filename.size() < 3 || filename.substr(filename.size() - 3) != ".ns") {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename.c_str(), "r");
    if (!file) {
        perror(filename.c_str());
        return EXIT_FAILURE;
    }
    yyin = file;

    // Initialize LLVM components.
    module = new llvm::Module("my_module", context);
    builder = new llvm::IRBuilder<>(context);

    // Start parsing - let the bison code handle main function creation
    yyparse();

    std::error_code EC;
    llvm::raw_fd_ostream dest("output.ll", EC);
    if (EC) {
        llvm::errs() << "Could not open file: " << EC.message();
        return EXIT_FAILURE;
    }
    module->print(dest, nullptr);
    dest.flush();

    fclose(file);

    int ret = system("clang output.ll -o out -mconsole >nul 2>&1");
    if (ret != 0) {
        std::cerr << "Failed to execute clang command." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
