/*
It is implementation browser history. At the beginning the browser is on the "homepage". 
You can go to other pages by executing following commands:
    visit [name]    - visit [name] page
    back [N]        - return back to [N] pages
    forward [N]     - move forward [N] pages
    show            - show browser history
    exit            - to close browser
Example input:
    visit google.com
    back 2
    back 1
    forward 1
    show
Output:
    homepage
    google.com
    homepage
    homepage
    google.com
*/

#include <smart_list.h>
#include <stdexcept>
#include <iostream>
#include <string>

#define MAX_URL_LENGTH 20
#define MAX_STEP 100

class Browser
{
private:
    SmartList<std::string, int> local_history;
    SmartList<std::string, int> history;
    int current_page_index;
    std::string homepage;

public:
    Browser(std::string homepage);
    void visit(std::string url);
    void moveForward(int N);
    void moveBack(int N);
    void showHistory();
};

Browser::Browser(std::string homepage) : current_page_index(0), homepage(homepage)
{
    local_history.pushBack(homepage);
    history.pushBack(homepage);
}

void Browser::visit(std::string url)
{
    if(url.length() > MAX_URL_LENGTH)
        throw std::runtime_error("URL is too long.");
    
    local_history.erase(local_history.begin() + current_page_index + 1, local_history.end());
    local_history.pushBack(url);
    history.pushBack(url);
    current_page_index = local_history.getSize() - 1;
}

void Browser::moveForward(int N)
{
    if(N < 0 || N > MAX_STEP)
        throw std::runtime_error("Incorrect step value.");

    current_page_index = std::min(current_page_index + N, local_history.getSize() - 1);
    history.pushBack(local_history[current_page_index]);
}

void Browser::moveBack(int N)
{
    if(N < 0 || N > MAX_STEP)
        throw std::runtime_error("Incorrect step value.");
    
    current_page_index = std::max(current_page_index - N, 0);
    history.pushBack(local_history[current_page_index]);
}

void Browser::showHistory()
{
    for(auto url : history)
        std::cout << url << std::endl;
}

int main()
{
    Browser browser("homepage");
    std::string input;
    try
    {
        while(true)
        {
            std::getline(std::cin, input);
            size_t space = input.find(' ');
            std::string cmd = input.substr(0, space);
            std::string argv = input.substr(space + 1);
            if(cmd == "exit")
                break;
            else if(cmd == "show")
                browser.showHistory();
            else if(cmd == "visit")
                browser.visit(argv);
            else if(cmd == "back")
                browser.moveBack(std::stoi(argv));
            else if(cmd == "forward")
                browser.moveForward(std::stoi(argv));
            else
                throw std::runtime_error("There is no command [" + cmd + "].");
        }
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
