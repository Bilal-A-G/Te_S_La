#include "TSpch.h"
#include "RendererAPI.h"

TESLA::API TESLA::RendererAPI::m_currentAPI;

TESLA::API TESLA::RendererAPI::GetCurrentAPI()
{
    return m_currentAPI;
}
