// implementation of graph in case, that the nodes are connected by single unidirectional edges
// N - count of nodes, E - count of edges:
// addNode = O(1)
// addEdge = O(N)
// removeNode = O(N + E)
// removeEdge = O(N)
// traverseReversePostOrder = O(?)
// getShortestPathsFrom = O(N^2 + E)
// edges uses iterators(anchors) of SmartLists for fast deletion
// it works because this iterators uses shared pointers
// and nodes are removed accurately one by one with saving remaining structure

#ifndef SLEEK_GRAPH
#define SLEEK_GRAPH

#include <smart_list.h>
#include <stdexcept>
#include <string>

class UnknownGraphNodesException : public std::runtime_error 
{
public:
    explicit UnknownGraphNodesException(const std::string &label) :
        std::runtime_error("Unknown node " + label) {}
    explicit UnknownGraphNodesException(const std::string &label1, const std::string &label2) :
        std::runtime_error("Unknown nodes " + label1 + " " + label2) {}
};

#define WeightType size_t

//template <typename WeightType = size_t>
class SleekGraph
{
public:
    using label_t = const std::string;
    using loop_t = std::pair<label_t, label_t>;

    struct Path
    {
        WeightType length;
        SmartList<label_t> nodes;

        Path(WeightType length) : length(length) {}
    };

private:
    struct Edge;

    struct Node
    {
        label_t label;
        SmartList<Edge *> incoming_edges;
        SmartList<Edge *> outcoming_edges;

        WeightType auxiliary_value;
        Node *auxiliary_node;
        bool is_marked;

        Node(label_t &label) : label(label) {}
    };

    struct Edge
    {
        Node *from;
        Node *to;
        WeightType weight;
        SmartListIterator<Edge *> from_anchor;
        SmartListIterator<Edge *> to_anchor;
        SmartListIterator<Edge> main_anchor;

        Edge(Node *from, Node *to, WeightType weight) : from(from), to(to), weight(weight) {}
    };

private:
    SmartList<Node> nodes;
    SmartList<Edge> edges;

    SmartListIterator<Node> getNodeIt(label_t &label)
    {
        return nodes.find([&label](const Node &node) { return node.label == label; });
    }

    Node *getNode(label_t &label)
    {
        SmartListIterator<Node> it = getNodeIt(label);
        if(it != nodes.end())
            return &nodes.get(it);
        return nullptr;
    }

    void removeEdgeByPointer(Edge *edge_ptr)
    {
        edge_ptr->from->outcoming_edges.erase(edge_ptr->from_anchor);
        edge_ptr->to->outcoming_edges.erase(edge_ptr->to_anchor);
        edges.erase(edge_ptr->main_anchor);
    }

public:
    SleekGraph() {}

    void addNode(label_t &label) { nodes.pushBack(Node(label)); }

    void addEdge(label_t &from, label_t &to, WeightType weight)
    {
        Node *from_ptr = getNode(from);
        Node *to_ptr = getNode(to);

        if((!from_ptr) && (!to_ptr))
            throw UnknownGraphNodesException(from, to);
        if(!from_ptr)
            throw UnknownGraphNodesException(from);
        if(!to_ptr)
            throw UnknownGraphNodesException(to);

        edges.pushBack(Edge(from_ptr, to_ptr, weight));
        from_ptr->outcoming_edges.pushBack(&edges.getBack());
        to_ptr->incoming_edges.pushBack(&edges.getBack());
        edges.getBack().from_anchor = from_ptr->outcoming_edges.getIteratorToLast();
        edges.getBack().to_anchor = to_ptr->incoming_edges.getIteratorToLast();
        edges.getBack().main_anchor = edges.getIteratorToLast();
    }

    void removeNode(label_t &label)
    {
        SmartListIterator<Node> node_it = getNodeIt(label);
        if(node_it == nodes.end())
            throw UnknownGraphNodesException(label);

        for(Edge *edge_ptr : node_it->incoming_edges)
            removeEdgeByPointer(edge_ptr);
        for(Edge *edge_ptr : node_it->outcoming_edges)
            removeEdgeByPointer(edge_ptr);

        nodes.erase(node_it);
    }

    void removeEdge(label_t &from, label_t &to)
    {
        Node *from_ptr = getNode(from);
        Node *to_ptr = getNode(to);

        if((!from_ptr) && (!to_ptr))
            throw UnknownGraphNodesException(from, to);
        if(!from_ptr)
            throw UnknownGraphNodesException(from);
        if(!to_ptr)
            throw UnknownGraphNodesException(to);

        SmartListIterator<Edge *> edge_it;
        if(from_ptr->outcoming_edges.getSize() < to_ptr->incoming_edges.getSize())
        {
            edge_it = from_ptr->outcoming_edges.find([&to](Edge *edge) { 
                return edge->to->label == to; 
            });
        }
        else
        {
            edge_it = to_ptr->incoming_edges.find([&from](Edge *edge) { 
                return edge->from->label == from; 
            });
        }
        
        if(edge_it == from_ptr->outcoming_edges.end())
            return;

        removeEdgeByPointer(*edge_it);
    }

    SmartList<label_t> traverseReversePostOrder(label_t origin, SmartList<loop_t> *loops = nullptr)
    {
        SmartList<label_t> result;
        SmartList<Node*> visited;
        SmartList<Node*> stack;

        Node *start_node = getNode(origin);
        if(!start_node)
            throw UnknownGraphNodesException(origin);

        stack.pushBack(start_node);
        while(stack.getSize() != 0)
        {
            Node *current = stack.popBack();
            visited.pushBack(current);
            result.pushBack(current->label);

            for (Edge *edge : current->outcoming_edges)
            {
                bool already_visited = false;
                for(Node *visited_node : visited)
                {
                    if(visited_node == edge->to)
                    {
                        already_visited = true;
                        break;
                    }
                }
                if(already_visited)
                {
                    if(loops && (edge->to = start_node))
                        loops->pushBack(loop_t(current->label, origin));
                    continue;
                }
                stack.pushBack(edge->to);
            }
        }

        return result;
    }

    SmartList<Path> getShortestPathsFrom(label_t &label, WeightType infinity)
    {
        SmartListIterator<Node> node_it = getNodeIt(label);
        if(node_it == nodes.end())
            throw UnknownGraphNodesException(label);
        Node *start = static_cast<Node *>(node_it);

        for(auto &node : nodes)
        {
            node.auxiliary_value = infinity;
            node.auxiliary_node = nullptr;
            node.is_marked = false;
        }
        start->auxiliary_value = 0;

        for(size_t i = 0; i < nodes.getSize(); i++)
        {
            WeightType min_weight = infinity;
            Node *min_node = nullptr;
            for(auto &node : nodes)
            {
                if((!node.is_marked) && (node.auxiliary_value < min_weight))
                {
                    min_node = &node;
                    min_weight = node.auxiliary_value;
                }
            }

            min_node->is_marked = true;
            for(auto &edge : min_node->outcoming_edges)
            {
                Node *next_node = edge->to;
                if(next_node->auxiliary_value > (min_node->auxiliary_value + edge->weight))
                {
                    next_node->auxiliary_value = min_node->auxiliary_value + edge->weight;
                    next_node->auxiliary_node = min_node;
                }
            }
        }

        start->auxiliary_node = nullptr;
        SmartList<Path> result;
        for(auto &node : nodes)
        {
            if(!node.auxiliary_node)
                continue;

            Node *node_ptr = &node;
            Path path(node.auxiliary_value);
            do
            {
                path.nodes.pushFront(node_ptr->label);
                node_ptr = node_ptr->auxiliary_node;
            }
            while(node_ptr != start);
            result.pushBack(path);
        }
        return result;
    }
};

#endif //SLEEK_GRAPH
