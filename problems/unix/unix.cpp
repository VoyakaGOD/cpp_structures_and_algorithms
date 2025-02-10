/* 
Converts input unix path into canonical form:
    /home////////////////////Downloads///// -> /home/Downloads
    /home/./Downloads/Films/../Stories/     -> /home/Downloads/Stories
*/ 

#include "smart_list.h"
#include <stdexcept>
#include <iostream>
#include <string>

#define PATH_MAX 4096
#define PATH_SEPARATOR '/'
#define DOT '.'

std::string getCanonicalForm(std::string raw_string)
{
    if(raw_string.length() > PATH_MAX)
        throw std::runtime_error("Maximum path length is " + std::to_string(PATH_MAX) + ".");
    if(raw_string[0] != PATH_SEPARATOR)
        throw std::runtime_error("Path should begin with <" + std::string(1, PATH_SEPARATOR) + ">.");

    raw_string += PATH_SEPARATOR; // to handle last control sequence
    SmartList<char> stack;
    stack.pushBack(PATH_SEPARATOR); // to avoid checking for emptiness
    int controlSequence = 0; // for <.> and <..>
    for(char c : raw_string)
    {
        if(c != PATH_SEPARATOR)
        {
            stack.pushBack(c);
            if(c == DOT)
                controlSequence++;
            else
                controlSequence = -PATH_MAX;
            continue;
        }

        if(stack.getBack() == PATH_SEPARATOR)
            continue;
        
        // Consider <...>, <....>, etc. as normal names
        if(controlSequence < 1 || controlSequence > 2)
        {
            stack.pushBack(PATH_SEPARATOR);
            controlSequence = 0;
            continue;
        }

        // case: path/.
        if(controlSequence == 1)
            stack.popBack();

        // case: path/tail/..
        else if(controlSequence == 2)
        {
            stack.popBack();
            stack.popBack();
            stack.popBack();
            if(stack.getSize() == 0)
                throw std::runtime_error("Going upper than the root directory is not possible.");
            while(stack.popBack() != PATH_SEPARATOR);
            stack.pushBack(PATH_SEPARATOR);
        }

        controlSequence = 0;
    }

    // Remove extra separator
    if(stack.getBack() == PATH_SEPARATOR && stack.getSize() > 1)
        stack.popBack();

    // Convert char sequence from stack to std::string
    char char_array[PATH_MAX];
    int path_length = stack.getSize();
    for(int i = 0; i < path_length; i++)
        char_array[i] = stack.popFront();
    char_array[path_length] = '\0';
    return std::string(char_array);
}

int main()
{
    std::string input;
    std::cin >> input;
    try
    {
        std::cout << getCanonicalForm(input) << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
}
