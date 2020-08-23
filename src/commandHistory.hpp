#ifndef COMMANDHISTORY_HPP
#define COMMANDHISTORY_HPP

#include "command.hpp"
#include <stack>
#include <memory>

class CommandHistory {
    std::stack<std::shared_ptr<Command>> commands;
public:
    CommandHistory();
    void push(std::shared_ptr<Command> command);
    std::shared_ptr<Command> pop();
    int size() const;
};

#endif
