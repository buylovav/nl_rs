#include "rewriter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: rewriter [file1.xml ... fileN.xml]\n";
        return 0;
    }

    std::list<std::string> files;

    for (int i=1; i<argc; i++)
    {        
        files.push_back(argv[i]);
    }

    Rewriter rewriter;
    rewriter.process(files);

    return 0;
}