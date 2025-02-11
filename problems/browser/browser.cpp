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

#include "smart_list.h"
#include <stdexcept>
#include <iostream>
#include <string>

#define MAX_URL_LENGTH 20

class Browser
{
private:
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
    history.pushBack(homepage);
}

void Browser::visit(std::string url)
{
    if(url.length() > MAX_URL_LENGTH)
        throw std::runtime_error("URL is too long.");
    
    //history.removeTail();
    history.pushBack(url);
}

void Browser::moveForward(int N)
{
    current_page_index = std::min(current_page_index + N, history.getSize() - 1);
    history.pushBack(history[current_page_index]);
}

void Browser::moveBack(int N)
{
    current_page_index = std::max(current_page_index - N, 0);
    history.pushBack(history[current_page_index]);
}

void Browser::showHistory()
{
    for(auto url : history)
        std::cout << url << std::endl;
}

int main()
{
    Browser browser("homepage");
    browser.visit("google.com");
    browser.moveBack(100);
    browser.moveBack(100);
    browser.moveForward(1);
    browser.visit("youtube.com");
    browser.showHistory();
}
