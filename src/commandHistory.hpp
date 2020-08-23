#ifndef COMMANDHISTORY_HPP
#define COMMANDHISTORY_HPP

#include "command.hpp"
#include <stack>

class CommandHistory {
    std::stack<Command*> commands;
public:
    CommandHistory();
    void push(Command* command);
    Command* pop();
    int size() const;
};

#endif
