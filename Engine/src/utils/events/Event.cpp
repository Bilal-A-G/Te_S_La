#include "TSpch.h"
#include "Event.h"

std::vector<void(*)(TESLA::Event*)> TESLA::EventListener::subscribers;
std::vector<TESLA::EventCategory> TESLA::EventListener::listenerTypes;

void TESLA::EventListener::Invoke(Event* event)
{
    for(int i = 0; i < listenerTypes.size(); i++)
    {
        if(listenerTypes[i] == event->GetCategory() && !event->GetHandled())
        {
            subscribers[i](event);
            event->Handle();
        }
    }
}

void TESLA::EventListener::Subscribe(void (* EventFunc)(TESLA::Event*), const TESLA::EventCategory& type)
{
    subscribers.push_back(EventFunc);
    listenerTypes.push_back(type);
}

