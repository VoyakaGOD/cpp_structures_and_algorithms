#include <sleek_graph.h>
#include <iostream>
#include <sstream>

int main()
{
    SleekGraph graph;
    std::string input;
    std::string cmd;
    
    while(true)
    {
        try
        {
            std::getline(std::cin, input);
            std::istringstream args(input);
            args >> cmd;
            if(cmd == "NODE")
            {
                std::string label;
                args >> label;
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
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
