#include "Version.hpp"

using namespace Mountain;

Version Version::FromString(const c8* str)
{
    s32 major, minor, patch;
    sscanf_s(str, "%d.%d.%d", &major, &minor, &patch);
    return Version{major, minor, patch};
}

std::string Version::ToString() const
{
    if (m_Patch == -1)
        return std::to_string(m_Major) + "." + std::to_string(m_Minor);

    return std::to_string(m_Major) + "." + std::to_string(m_Minor) + "." + std::to_string(m_Patch);
}
