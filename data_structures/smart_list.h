// Implementation of double linked list via smart pointers

#ifndef SMART_LIST
#define SMART_LIST

#include <memory>
#include <cassert>

template <typename T>
struct SmartListNode
{
public:
    T value;
    std::shared_ptr<SmartListNode<T>> next;
    std::weak_ptr<SmartListNode<T>> prev;

public:
    SmartListNode(T value) : value(value), next(nullptr) {}
};

template <typename T, typename SizeType = uint64_t>
class SmartList
{
protected:
    SizeType size;
    std::shared_ptr<SmartListNode<T>> head;
    std::shared_ptr<SmartListNode<T>> tail;

public:
    SmartList() : size(0), head(nullptr), tail(nullptr) {}
    
    SizeType getSize() const { return size; }

    T &getFront() { return head->value; }

    T &getBack() { return tail->value; }

    T &get(SizeType index)
    {
        assert(index < size);
        assert(index >= 0);

        SmartListNode<T> *node = head.get();
        while((index--) > 0)
            node = node->next.get();

        return node->value;
    }

    T& operator[](SizeType index) { return get(index); }

    T pop(SizeType index)
    {
        assert(size > 0);

        if(index == 0) 
            return popFront();

        if(index == (size - 1))
            return popBack();

        std::shared_ptr<SmartListNode<T>> node = head;
        while((index--) > 0)
            node = node->next;

        std::shared_ptr<SmartListNode<T>> prev = node->prev.lock();
        if(prev)
            prev->next = node->next;
        if(node->next)
            node->next->prev = node->prev;

        size--;
        return node->value;
    }

    void pushFront(T value) 
    {
        std::shared_ptr<SmartListNode<T>> new_node = std::make_shared<SmartListNode<T>>(value);
        new_node->next = head;
        if(size == 0)
            tail = new_node;
        else
            head->prev = new_node;
        head = new_node;
        size++;
    }

    void pushBack(T value)
    {
        std::shared_ptr<SmartListNode<T>> new_node = std::make_shared<SmartListNode<T>>(value);
        new_node->prev = tail;
        if(size == 0)
            head = new_node;
        else
            tail->next = new_node;
        tail = new_node;
        size++;
    }

    T popFront()
    {
        assert(size > 0);

        std::shared_ptr<SmartListNode<T>> lost_node = head;
        head = head->next;
        if(!head)
            tail = nullptr;
        size--;
        return lost_node->value;
    }

    T popBack()
    {
        assert(size > 0);

        std::shared_ptr<SmartListNode<T>> lost_node = tail;
        tail = tail->prev.lock();
        if(tail)
            tail->next = nullptr;
        else
            head = nullptr;
        size--;
        return lost_node->value;   
    }
};

#endif //SMART_LIST
