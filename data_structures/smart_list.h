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

template <typename T>
class SmartListIterator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = void;

private:
    std::shared_ptr<SmartListNode<T>> current;

public:
    SmartListIterator() : current(nullptr) {}
    SmartListIterator(std::shared_ptr<SmartListNode<T>> node) : current(node) {}
    T& operator*() { return current->value; }
    T* operator->() { return &current->value; }
    std::shared_ptr<SmartListNode<T>> getNode() { return current; }

    SmartListIterator& operator++() 
    {
        if(current)
            current = current->next;
        return *this;
    }

    SmartListIterator operator++(int)
    {
        SmartListIterator old(*this);
        ++(*this);
        return old;
    }

    SmartListIterator& operator--()
    {
        if(current)
            current = current->prev.lock();
        return *this;
    }

    SmartListIterator operator--(int)
    {
        SmartListIterator old(*this);
        --(*this);
        return old;
    }

    SmartListIterator operator+(size_t step) const
    {
        std::shared_ptr<SmartListNode<T>> node = current;
        while(node && ((step--) > 0))
            node = node->next;
        return SmartListIterator(node);
    }

    bool operator==(const SmartListIterator& other) const 
    {
        return current == other.current;
    }

    bool operator!=(const SmartListIterator& other) const 
    {
        return current != other.current;
    }

    explicit operator T*()
    {
        return &current->value;
    }
};

template <typename T, typename SizeType = size_t>
class SmartList
{
protected:
    SizeType size;
    std::shared_ptr<SmartListNode<T>> head;
    std::shared_ptr<SmartListNode<T>> tail;

public:
    SmartList() : size(0), head(nullptr), tail(nullptr) {}
    
    SizeType getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

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

    T &get(SmartListIterator<T> it)
    {
        assert(it != end());

        return it.getNode()->value;
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

    SmartListIterator<T> begin()
    {
        return SmartListIterator<T>(head);
    }

    SmartListIterator<T> end()
    {
        return SmartListIterator<T>(nullptr);
    }

    SmartListIterator<T> getIteratorToLast()
    {
        return SmartListIterator<T>(tail);
    }

    void erase(SmartListIterator<T> start, SmartListIterator<T> stop)
    {
        if(start == stop)
            return;

        SmartListIterator<T> it = start;
        while(it != stop)
        {
            assert(it != end());
            size--;
            ++it;
        }

        if(start.getNode() == head)
            head = stop.getNode();

        std::shared_ptr<SmartListNode<T>> last_left_node = start.getNode()->prev.lock();
        if(stop == end())
            tail = last_left_node;

        if(last_left_node)
            last_left_node->next = stop.getNode();
        if(stop != end())
            stop.getNode()->prev = start.getNode()->prev;
    }

    void erase(SmartListIterator<T> item)
    {
        SmartListIterator<T> old = item;
        erase(old, ++item);
    }

    template <typename PredicateType>
    SmartListIterator<T> find(PredicateType predicate)
    {
        SmartListIterator<T> it = begin();
        while(it != end())
        {
            if(predicate(*it))
                break;
            ++it;
        }
        return it;
    }

    template <typename PredicateType>
    bool contains(PredicateType predicate)
    {
        SmartListIterator<T> it = find(predicate);
        return it != end();
    }

    template <typename PredicateType>
    void removeIf(PredicateType predicate)
    {
        SmartListIterator<T> it = begin();
        while(it != end())
        {
            if(predicate(*it))
                erase(it);
            ++it;
        }
    }
};

#endif //SMART_LIST
