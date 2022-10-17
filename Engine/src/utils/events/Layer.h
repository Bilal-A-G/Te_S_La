#pragma once
#include "../../core/Core.h"
#include "Event.h"

namespace TESLA
{
    class TS_DLL Layer
    {
    public:
        Layer(const std::string& name = "Layer")
            :m_name(name){}

        virtual ~Layer(){}

        virtual void OnAttach(){}
        virtual void OnDetach(){}
        virtual void OnUpdate(){}

        virtual void DispatchEvent(TESLA::EventFunction function, TESLA::Event* event) = 0;
        const std::string& GetName(){return m_name;}
        
    private:
        const std::string& m_name;
    };
}
