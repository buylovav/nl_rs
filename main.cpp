#include "rewriter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: -a|-s rewriter [file1.xml ... fileN.xml]\n"
                      "a means All, s means Scheme"  ;
        return 0;
    }

    int fileInd(2);
    //std::cout << "\'"<< argv[1] << "\' " << argc << std::endl;
    USAGE usage(USAGE::SCHEME);//default
    if (std::string(argv[1])=="-a")
        usage = USAGE::ALL;
    else if (std::string(argv[1])=="-s")
        usage = USAGE::SCHEME;
    else
        fileInd--;

    std::list<std::string> files;

    for (int i=fileInd; i<argc; i++)
    {        
        files.push_back(argv[i]);
        //std::cout << argv[i] << std::endl;
    }

    Rewriter rewriter(usage);
    rewriter.process(files);

    return 0;
}