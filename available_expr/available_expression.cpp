#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype> // for std::isspace
#include <algorithm>
#include <stack>

// function declare
void trim_leading_whitespace(std::string &line);
void WithEqual(std::string &line, int equalPos);
void NoEqual(std::string &line);
void kill(const std::string e);
void merge(const std::string &e);
void deal_with_expr(std::string &line);

// store all available exprs
std::set<std::string> s;

void trim_leading_whitespace(std::string &line)
{
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch)
                                          { return !std::isspace(ch); }));
}

void NoEqual(std::string &line)
{
    std::string left, right;
    size_t returnPos = line.find("return");
    if (returnPos != std::string::npos)
    {
        // 6 is the legth of "return"
        left = line.substr(returnPos + 6);
        // remove ';' and whitespace
        trim_leading_whitespace(left);
        left.pop_back();

        // kill and no merge
        kill(left);
    }
}

void WithEqual(std::string &line, int equalPos)
{
    std::string left, right;
    // kill left, append right
    left = line.substr(0, equalPos);
    right = line.substr(equalPos + 1);
    trim_leading_whitespace(left);
    trim_leading_whitespace(right);
    right.pop_back();
    left.pop_back();
    kill(left);
    merge(right);
}

void deal_with_expr(std::string &line)
{

    size_t equalPos = line.find('=');
    // if '=' cannot find
    if (equalPos == std::string::npos)
    {
        // if sentens contains 'return'
        NoEqual(line);
    }
    else
    {
        WithEqual(line, equalPos);
    }
}

int main()
{
    // open file
    std::ifstream file("test.txt");
    if (!file)
    {
        std::cerr << "Unable to open file for reading." << std::endl;
        return 1;
    }

    std::string line;
    int count = 1;

    while (std::getline(file, line))
    {
        trim_leading_whitespace(line);

        deal_with_expr(line);

        std::cout << count << ": ";
        for (auto it = s.begin(); it != s.end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << '\n';
        count++;
    }

    file.close();
    return 0;
}

void kill(const std::string e)
{
    for (auto it = s.begin(); it != s.end();)
    {
        if (it->find(e) != std::string::npos)
        {
            // delete expr
            it = s.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void merge(const std::string &e)
{
    s.insert(e);

    // stack to deal with bracket, push index to stack
    std::stack<size_t> bracketStack;
    for (size_t i = 0; i < e.size(); ++i)
    {
        if (e[i] == '(')
        {
            // if we meet '(' push into stack
            bracketStack.push(i);
        }
        else if (e[i] == ')' && !bracketStack.empty())
        {
            // if we meet ')' pop
            size_t startPos = bracketStack.top();
            bracketStack.pop();
            // from start index to 'i - start -1'
            s.insert(e.substr(startPos + 1, i - startPos - 1));
        }
    }
}