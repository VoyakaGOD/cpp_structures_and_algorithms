#include <sleek_graph.h>
#include <iostream>
#include <sstream>

class UnknownCommandException : public std::runtime_error
{
public:
    explicit UnknownCommandException(const std::string &command) :
        std::runtime_error("Unknown command[" + command + "]") {}
};

int main()
{
    SleekGraph graph;
    std::string input;
    
    while(true)
    {
        try
        {
            std::getline(std::cin, input);
            std::istringstream args(input);
            std::string cmd;
            args >> cmd;
            if(cmd == "NODE")
            {
                std::string label;
                args >> label;
                if(label.length() == 0)
                    throw std::runtime_error("Enter node name");
                graph.addNode(label);
            }
            else if(cmd == "EDGE")
            {
                std::string from;
                std::string to;
                size_t weight = 0;
                args >> from;
                args >> to;
                args >> weight;
                graph.addEdge(from, to, weight);
            }
            else if(cmd == "REMOVE")
            {
                args >> cmd;
                if(cmd == "NODE")
                {
                    std::string label;
                    args >> label;
                    graph.removeNode(label);
                }
                else if(cmd == "EDGE")
                {
                    std::string from;
                    std::string to;
                    args >> from;
                    args >> to;
                    graph.removeEdge(from, to);
                }
                else
                {
                    throw UnknownCommandException(cmd);
                }
            }
            else if(cmd == "RPO_NUMBERING")
            {
                std::string label;
                args >> label;
                SmartList<SleekGraph::loop_t> loops;
                SmartList<SleekGraph::label_t> rpo = graph.traverseReversePostOrder(label, &loops);
                for(const auto &loop : loops)
                    std::cout << "Found loop " << loop.first << "->" << loop.second << std::endl;
                std::cout << rpo.popFront();
                for(const auto &label : rpo)
                    std::cout << ' ' << label;
                std::cout << std::endl;
            }
            else if(cmd == "DIJKSTRA")
            {
                std::string label;
                std::string extra;
                args >> label;
                args >> extra;
                SmartList<SleekGraph::Path> paths = graph.getShortestPathsFrom(label, static_cast<size_t>(-1ll));
                bool show_nodes = false;
                if(extra == "NODES")
                    show_nodes = true;
                else if(extra != "")
                    throw UnknownCommandException(extra);
                for(auto &path : paths)
                {
                    std::cout << path.nodes.getBack() << ' ';
                    std::cout << path.length;
                    if(show_nodes)
                    {
                        std::cout << " :: " << label;
                        for(auto &node : path.nodes)
                            std::cout << "->" << node;
                    }
                    std::cout << std::endl;
                }
            }
            else if(cmd == "MAXFLOW")
            {
                std::string source;
                std::string sink;
                args >> source;
                args >> sink;
                std::cout << graph.getMaxFlow(source, sink) << std::endl;
            }
            else if(cmd == "q")
            {
                break;
            }
            else
            {
                throw UnknownCommandException(cmd);
            }
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
