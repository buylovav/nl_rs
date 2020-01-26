#include "rewriter.h"
#include <thread>
#include <future>
#include <iostream>

Rewriter::Rewriter()
{}

Rewriter::~Rewriter()
{}

void Rewriter::plant(NamedTree&& tree)
{
    std::lock_guard<std::mutex> lock(_mutex);
    //std::cout << "planted: " << tree.first << std::endl;
    _forest.emplace_back(std::move(tree));
}

std::pair<bool, NamedTree> Rewriter::uproot(bool finished)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_forest.empty())
        return std::make_pair(finished, NamedTree("", Tree()));
    NamedTree tree = std::move(_forest.front());
    //std::cout<<"uprooted: " << tree.first << std::endl;
    _forest.pop_front();
    return std::make_pair(finished, std::move(tree));
}

void Rewriter::process(const std::list<std::string>& files)
{
    _finished = false;
    std::thread th(&Rewriter::write, this);

    for (auto& file : files)
    {        
        auto f = std::async(std::launch::async,&Rewriter::read, this, std::cref(file));
        f.get();
    }
    _finished = true;

    th.join();
}

void Rewriter::write()
{
    auto stop(false);
    do 
    {
        auto tree = uproot(_finished);
        if (!tree.second.tree.empty())
        {            
            boost::property_tree::write_json(tree.second.name+".json", tree.second.tree);
            std::cout << "  " << tree.second.name+".json" << " is written" <<std::endl;
        }
        else if (tree.first)//finished and empty
        {
            break;
        }        
    }while (true);
}

void Rewriter::read(const std::string& file)
{
    Tree tree;
    try
    {
        boost::property_tree::read_xml(file, tree, boost::property_tree::xml_parser::trim_whitespace);
    }catch(boost::property_tree::xml_parser::xml_parser_error& e)
    {
        std::string error (std::string("Cannot open a file \"")+e.what()+"\"\n");
        std::cout << error;
    }
    std::string name = file.substr(0, file.rfind('.'));
    plant(NamedTree(name, std::move(tree)));
}