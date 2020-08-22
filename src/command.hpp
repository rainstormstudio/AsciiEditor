#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

#endif
