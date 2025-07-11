#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/Utils.hpp"

#include <fstream>
#include <ranges>
#include <regex>

#include <ImGui/imgui.h>

#include "Mountain/Globals.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

void Utils::AlignImGuiCursor(const float_t objectWidth, const float_t alignment)
{
    const float_t avail = ImGui::GetContentRegionAvail().x;
    const float_t off = avail * alignment - objectWidth / 2.f;

    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}

std::string Utils::HumanizeString(const std::string& str)
{
    // Regex: https://regex101.com/r/3rQ25V/5
    // Matches any uppercase letter that has a lowercase variant,
    // that is not the first character in the string,
    // and that is either preceded or followed by a lowercase letter that has an uppercase variant
    static const std::regex Regex(R"((?:[a-z])([A-Z])|(?:.)([A-Z])(?:[a-z]))");

    // According to https://en.cppreference.com/w/cpp/string/byte/toupper,
    // when using the std::toupper function, to make sure the operation is executed
    // correctly, we should cast the input to unsigned char and the output to char
    const char_t firstCharUpper = static_cast<char_t>(std::toupper(static_cast<uint8_t>(str[0])));

    std::sregex_iterator begin(str.begin(), str.end(), Regex);
    std::sregex_iterator end;

    std::string result = firstCharUpper + str.substr(1);

    // Early return if nothing matches
    if (std::distance(begin, end) == 0)
        return result;

    const std::string::const_iterator& sBegin = str.begin();
    std::string::iterator rBegin = result.begin();
    for (std::sregex_iterator it = begin; it != end; it++)
    {
        const std::smatch& match = *it;
        // Get results for capture groups 1 and 2
        for (int i = 1; i < 3; i++)
        {
            const std::ssub_match& subMatch = match[i];
            if (subMatch.matched)
            {
                result.replace(subMatch.first - sBegin + rBegin, subMatch.second - sBegin + rBegin, ' ' + subMatch.str());
                rBegin++;
            }
        }
    }

    return result;
}

std::string Utils::HumanizeVariableName(const std::string& str)
{
    std::string result = str;

    if (result[0] == 'm' && result[1] == '_')
        result = result.substr(2);

    return result;
    // FIXME - return HumanizeString(result);
}

float_t Utils::NormalizeAngle(float_t angle)
{
    while (angle > Calc::TwoPi)
        angle -= Calc::TwoPi;

    while (angle < 0)
        angle += Calc::TwoPi;

    return angle;
}

Vector3 Utils::NormalizeAngles(const Vector3 angles)
{
    return {NormalizeAngle(angles.x), NormalizeAngle(angles.y), NormalizeAngle(angles.z)};
}

Vector3 Utils::GetQuaternionEulerAngles(const Quaternion& rot)
{
    // Function taken from glm

    const float_t sqw = rot.W() * rot.W();
    const float_t sqx = rot.X() * rot.X();
    const float_t sqy = rot.Y() * rot.Y();
    const float_t sqz = rot.Z() * rot.Z();
    const float_t unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
    const float_t test = rot.X() * rot.W() - rot.Y() * rot.Z();
    Vector3 v;

    if (test > 0.4995f * unit)
    { // singularity at north pole
        v.y = 2.f * std::atan2f(rot.Y(), rot.X());
        v.x = Calc::PiOver2;
        v.z = 0;
        return NormalizeAngles(v);
    }
    if (test < -0.4995f * unit)
    { // singularity at south pole
        v.y = -2.f * std::atan2f(rot.Y(), rot.X());
        v.x = -Calc::PiOver2;
        v.z = 0;
        return NormalizeAngles(v);
    }

    Quaternion q = Quaternion(rot.Z(), rot.X(), rot.Y(), rot.W());
    v.y = std::atan2f(2.f * q.X() * q.W() + 2.f * q.Y() * q.Z(), 1 - 2.f * (q.Z() * q.Z() + q.W() * q.W()));    // Yaw
    v.x = std::asinf(2.f * (q.X() * q.Z() - q.W() * q.Y()));                                                    // Pitch
    v.z = std::atan2f(2.f * q.X() * q.Y() + 2.f * q.Z() * q.W(), 1 - 2.f * (q.Y() * q.Y() + q.Z() * q.Z()));    // Roll
    return NormalizeAngles(v);
}

void Utils::OpenInExplorer(const std::filesystem::path& path) { OpenInExplorer(path, !is_directory(path)); }

void Utils::OpenInExplorer(const std::filesystem::path& path, const bool_t isFile)
{
    std::string command = "explorer ";

    if (isFile)
        command += "/select,";

    command += '"' + absolute(path).string() + '"';

    TerminalCommand(command);
}

void Utils::OpenFile(const std::filesystem::path& filepath) { TerminalCommand("explorer " + ('"' + absolute(filepath).string() + '"')); }

bool_t Utils::StringEqualsIgnoreCase(const std::string_view a, const std::string_view b)
{
    return std::ranges::equal(
        a, b,
        [] (const char_t& aa, const char_t& bb) -> bool_t
        {
            return std::tolower(aa) == std::tolower(bb);
        }
    );
}

bool_t Utils::StringContainsIgnoreCase(const std::string_view a, const std::string_view b)
{
    const std::string left = ToLower(a), right = ToLower(b);
    return left.contains(right);
}

int32_t Utils::TerminalCommand(const std::string& command, const bool_t asynchronous)
{
    return std::system(((asynchronous ? "start /MIN " : "") + command).c_str());  // NOLINT(concurrency-mt-unsafe)
}

void Utils::CreateEmptyFile(const std::filesystem::path& path)
{
    // Creating a std::ofstream is the only necessary thing to do to create an empty file
    std::ofstream{ path };
}

void Utils::SetThreadName(ATTRIBUTE_MAYBE_UNUSED std::thread& thread, ATTRIBUTE_MAYBE_UNUSED const std::wstring& name)
{
#if defined(_DEBUG) && defined(ENVIRONMENT_WINDOWS)
    (void) SetThreadDescription(thread.native_handle(), name.c_str());
    Windows::SilenceError();
#endif
}

std::wstring Utils::NarrowToWide(const std::string_view str)
{
    std::wstring result;
    result.resize(str.size());
    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str.data(), static_cast<int32_t>(str.size()), result.data(), static_cast<int32_t>(result.size()));
    return result;
}

std::string Utils::WideToNarrow(const std::wstring_view str)
{
    std::string result;
    result.resize(str.size());
    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, str.data(), static_cast<int32_t>(str.size()), result.data(), static_cast<int32_t>(result.size()), nullptr, nullptr);
    return result;
}

std::string Utils::ToLower(const std::string_view str)
{
    std::string result;
    result.resize(str.size());
    for (size_t i = 0; i < str.size(); i++)
        result[i] = static_cast<char_t>(std::tolower(str[i]));
    return result;
}

std::string Utils::ToUpper(const std::string_view str)
{
    std::string result;
    result.resize(str.size());
    for (size_t i = 0; i < str.size(); i++)
        result[i] = static_cast<char_t>(std::toupper(str[i]));
    return result;
}

std::pair<float_t, std::string_view> Utils::ByteSizeUnit(int64_t size)
{
    if (size < 1000)
        return { static_cast<float_t>(size), "B" };

    float_t dividedSize = static_cast<float_t>(size) / 1000.f;
    if (dividedSize < 1000)
        return { dividedSize, "KB" };

    dividedSize /= 1000;
    if (dividedSize < 1000)
        return { dividedSize, "MB" };

    dividedSize /= 1000;
    if (dividedSize < 1000)
        return { dividedSize, "GB" };

    dividedSize /= 1000;
    if (dividedSize < 1000)
        return { dividedSize, "TB" };

    return { static_cast<float_t>(size), "?" };
}

std::string Utils::GetBuiltinShadersPath() { return BuiltinShadersPath.empty() ? "shaders_internal/" : BuiltinShadersPath + '/'; }

std::string Utils::GetBuiltinAssetsPath() { return BuiltinAssetsPath.empty() ? "assets_internal/" : BuiltinAssetsPath + '/'; }

std::string Utils::Trim(const std::string_view str, const TrimOptions options)
{
    std::string result{ str.data(), str.length() };

    if (options & TrimOptions::Start)
        result.erase(result.begin(), std::ranges::find_if(result, [](const uint8_t c) { return !std::isspace(c); }));
    if (options & TrimOptions::End)
        result.erase(std::ranges::find_if(std::ranges::reverse_view(result), [](const uint8_t c) { return !std::isspace(c); }).base(), result.end());

    return result;
}

std::string Utils::GetLine(const std::string& str, const size_t lineIndex)
{
    std::istringstream input{ str };
    size_t currentIndex = 0;
    for (std::string line; std::getline(input, line); currentIndex++)
    {
        if (currentIndex == lineIndex)
            return line;
    }

    return "";
}

uint16_t Utils::Concat16(const uint8_t right, const uint8_t left)
{
    return static_cast<uint16_t>(right | left << 8);
}

uint32_t Utils::Concat32(const uint8_t right0, const uint8_t right1, const uint8_t left0, const uint8_t left1)
{
    return right0 | right1 << 8 | left0 << 16 | left1 << 24;
}
