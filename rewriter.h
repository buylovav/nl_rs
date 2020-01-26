#ifndef _H_REWRITER
#define _H_REWRITER

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <deque>
#include <list>
#include <mutex>
#include <atomic>

using Tree = boost::property_tree::ptree;

struct NamedTree{
    std::string name;
    Tree tree;
    NamedTree(std::string name, Tree&& tree)
        : name(name)
        , tree(std::move(tree))
        {}
};

class Rewriter {
    std::mutex _mutex;
    std::atomic_bool _finished;
    std::deque<NamedTree> _forest;

    void plant(NamedTree&& tree);
    std::pair<bool, NamedTree> uproot(bool finished);
    
    void write();
    void read(const std::string& file);
public:
    Rewriter();
    ~Rewriter();
    void process(const std::list<std::string>& list);
};

#endif /*_H_REWRITER*/