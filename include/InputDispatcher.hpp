#pragma once
#include "Command.hpp"

class InputDispatcher
{
public:
    InputDispatcher(ICommandHandler& app)
        :app(app)
    {

    }

    void Dispatch(ICommandHandler* element,const std::vector<Command>& commands)
    {
        if(element == nullptr)
        {
            app.HandleCommands(commands);
            return;
        }

        element->HandleCommands(commands);
    }

private:
    ICommandHandler& app;
};
