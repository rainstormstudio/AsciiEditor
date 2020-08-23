#include "commandHistory.hpp"

CommandHistory::CommandHistory() {
    commands = std::stack<std::shared_ptr<Command>>();
}

void CommandHistory::push(std::shared_ptr<Command> command) {
    commands.emplace(command);
}

std::shared_ptr<Command> CommandHistory::pop() {
    if (commands.empty()) {
        return nullptr;
    }
    std::shared_ptr<Command> command = commands.top();
    commands.pop();
    return command;
}

int CommandHistory::size() const { return commands.size(); }
