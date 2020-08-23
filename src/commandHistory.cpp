#include "commandHistory.hpp"

CommandHistory::CommandHistory() {
    commands = std::stack<Command*>();
}

void CommandHistory::push(Command* command) {
    commands.emplace(command);
}

Command* CommandHistory::pop() {
    if (commands.empty()) {
        return nullptr;
    }
    Command* command = commands.top();
    commands.pop();
    return command;
}

int CommandHistory::size() const { return commands.size(); }
