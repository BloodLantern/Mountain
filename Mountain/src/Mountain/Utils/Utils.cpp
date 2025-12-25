

#include "Mountain/Utils/Utils.hpp"

#include <fstream>
#include <ranges>
#include <regex>

#include <imgui.h>

#include "Mountain/Globals.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

void Utils::AlignImGuiCursor(const f32 objectWidth, const f32 alignment)
{
    const f32 avail = ImGui::GetContentRegionAvail().x;
    const f32 off = avail * alignment - objectWidth / 2.f;

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
    const c8 firstCharUpper = static_cast<c8>(std::toupper(static_cast<u8>(str[0])));

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

    return HumanizeString(result);
}

f32 Utils::NormalizeAngle(f32 angle)
{
    angle = Calc::Modulo(angle, Calc::TwoPi);

    if (angle < 0.f)
        angle += Calc::TwoPi;

    return angle;
}

Vector3 Utils::NormalizeAngles(const Vector3 angles)
{
    return {NormalizeAngle(angles.x), NormalizeAngle(angles.y), NormalizeAngle(angles.z)};
}

void Utils::OpenInExplorer(const std::filesystem::path& path) { OpenInExplorer(path, !is_directory(path)); }

void Utils::OpenInExplorer(const std::filesystem::path& path, const bool isFile)
{
    std::string command = "explorer ";

    if (isFile)
        command += "/select,";

    command += '"' + absolute(path).string() + '"';

    TerminalCommand(command);
}

void Utils::OpenFile(const std::filesystem::path& filepath) { TerminalCommand("explorer " + ('"' + absolute(filepath).string() + '"')); }

bool Utils::StringEqualsIgnoreCase(const std::string_view a, const std::string_view b)
{
    return std::ranges::equal(
        a, b,
        [] (const c8& aa, const c8& bb) -> bool
        {
            return std::tolower(aa) == std::tolower(bb);
        }
    );
}

bool Utils::StringContainsIgnoreCase(const std::string_view a, const std::string_view b)
{
    const std::string left = ToLower(a), right = ToLower(b);
    return left.contains(right);
}

s32 Utils::TerminalCommand(const std::string& command, const bool asynchronous)
{
    return std::system(((asynchronous ? "start /MIN " : "") + command).c_str());  // NOLINT(concurrency-mt-unsafe)
}

void Utils::CreateEmptyFile(const std::filesystem::path& path)
{
    // Creating a std::ofstream is the only necessary thing to do to create an empty file
    std::ofstream{path};
}

void Utils::SetThreadName(ATTRIBUTE_MAYBE_UNUSED std::thread& thread, ATTRIBUTE_MAYBE_UNUSED const std::string& name)
{
#ifdef PROFILING
    //tracy::SetThreadName(name.c_str());
#endif

#ifdef ENVIRONMENT_WINDOWS
    (void) SetThreadDescription(thread.native_handle(), NarrowToWide(name).c_str());
    Windows::SilenceError();
#endif
}

std::wstring Utils::NarrowToWide(const std::string_view& str)
{
    std::wstring result;
    result.resize(str.size());
#ifdef ENVIRONMENT_WINDOWS
    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str.data(), static_cast<s32>(str.size()), result.data(), static_cast<s32>(result.size()));
#endif
    return result;
}

std::string Utils::WideToNarrow(const std::wstring_view& str)
{
    std::string result;
    result.resize(str.size());
#ifdef ENVIRONMENT_WINDOWS
    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, str.data(), static_cast<s32>(str.size()), result.data(), static_cast<s32>(result.size()), nullptr, nullptr);
#endif
    return result;
}

std::string Utils::ToLower(const std::string_view str)
{
    std::string result;
    result.resize(str.size());
    for (usize i = 0; i < str.size(); i++)
        result[i] = static_cast<c8>(std::tolower(str[i]));
    return result;
}

std::string Utils::ToUpper(const std::string_view str)
{
    std::string result;
    result.resize(str.size());
    for (usize i = 0; i < str.size(); i++)
        result[i] = static_cast<c8>(std::toupper(str[i]));
    return result;
}

std::pair<f32, std::string_view> Utils::ByteSizeUnit(const s64 size)
{
    if (size < 1000)
        return { static_cast<f32>(size), "B" };

    f32 dividedSize = static_cast<f32>(size) / 1000.f;
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

    return { static_cast<f32>(size), "?" };
}

std::string Utils::GetBuiltinShadersPath() { return BuiltinShadersPath.empty() ? "shaders_internal/" : BuiltinShadersPath + '/'; }

std::string Utils::GetBuiltinAssetsPath() { return BuiltinAssetsPath.empty() ? "assets_internal/" : BuiltinAssetsPath + '/'; }

std::string Utils::Trim(const std::string_view str, const TrimOptions options)
{
    std::string result{ str.data(), str.length() };

    if (options & TrimOptions::Start)
        result.erase(result.begin(), std::ranges::find_if(result, [](const u8 c) { return !std::isspace(c); }));
    if (options & TrimOptions::End)
        result.erase(std::ranges::find_if(std::ranges::reverse_view(result), [](const u8 c) { return !std::isspace(c); }).base(), result.end());

    return result;
}

std::string Utils::GetLine(const std::string& str, const usize lineIndex)
{
    std::istringstream input{ str };
    usize currentIndex = 0;
    for (std::string line; std::getline(input, line); currentIndex++)
    {
        if (currentIndex == lineIndex)
            return line;
    }

    return "";
}

u16 Utils::Concat16(const u8 right, const u8 left)
{
    return static_cast<u16>(right | left << 8);
}

u32 Utils::Concat32(const u8 right0, const u8 right1, const u8 left0, const u8 left1)
{
    return right0 | right1 << 8 | left0 << 16 | left1 << 24;
}

std::string Utils::RemoveByteOrderMark(const std::string& text)
{
    // https://en.wikipedia.org/wiki/Byte_order_mark

    constexpr static Array ByteOrderMarks{
        "\xEF" "\xBB" "\xBF",           // UTF-8
        "\xFE" "\xFF",                  // UTF-16 (BE)
        "\xFF" "\xFE",                  // UTF-16 (LE)
        "\x00" "\x00" "\xFE" "\xFF",    // UTF-32 (BE)
        "\x00" "\x00" "\xFF" "\xFE",    // UTF-32 (LE)
        "\x2B" "\x2F" "\x76",           // UTF-7
        "\xF7" "\x64" "\x4C",           // UTF-1
        "\xDD" "\x73" "\x66" "\x73",    // UTF-EBCDIC
        "\x0E" "\xFE" "\xFF",           // SCSU
        "\xFB" "\xEE" "\x28",           // BOCU-1
        "\x84" "\x31" "\x95" "\x33"     // GB18030
    };

    for (const c8* byteOrderMark : ByteOrderMarks)
    {
        if (text.starts_with(byteOrderMark))
            return text.substr(std::strlen(byteOrderMark));
    }

    return text;
}

List<std::string> Utils::Split(const std::string_view str, const c8 separator)
{
    List<std::string> result;

    usize lastIndex = 0;
    usize currentSize = 0;
    for (usize i = 0; i < str.length(); i++)
    {
        if (str[i] != separator)
        {
            currentSize++;
            continue;
        }

        result.Add(std::string{str.substr(lastIndex, currentSize)});

        lastIndex = i + 1;
        currentSize = 0;
    }

    result.Add(std::string{str.substr(lastIndex, currentSize)});

    return result;
}

Easing::Easer Easing::FromType(const Type type)
{
    switch (type)
    {
        case Type::Linear: return Linear;
        case Type::SineIn: return SineIn;
        case Type::SineOut: return SineOut;
        case Type::SineInOut: return SineInOut;
        case Type::QuadIn: return QuadIn;
        case Type::QuadOut: return QuadOut;
        case Type::QuadInOut: return QuadInOut;
        case Type::CubicIn: return CubicIn;
        case Type::CubicOut: return CubicOut;
        case Type::CubicInOut: return CubicInOut;
        case Type::QuartIn: return QuartIn;
        case Type::QuartOut: return QuartOut;
        case Type::QuartInOut: return QuartInOut;
        case Type::QuintIn: return QuintIn;
        case Type::QuintOut: return QuintOut;
        case Type::QuintInOut: return QuintInOut;
        case Type::ExpoIn: return ExpoIn;
        case Type::ExpoOut: return ExpoOut;
        case Type::ExpoInOut: return ExpoInOut;
        case Type::CircIn: return CircIn;
        case Type::CircOut: return CircOut;
        case Type::CircInOut: return CircInOut;
        case Type::BackIn: return BackIn;
        case Type::BackOut: return BackOut;
        case Type::BackInOut: return BackInOut;
        case Type::ElasticIn: return ElasticIn;
        case Type::ElasticOut: return ElasticOut;
        case Type::ElasticInOut: return ElasticInOut;
        case Type::BounceIn: return BounceIn;
        case Type::BounceOut: return BounceOut;
        case Type::BounceInOut: return BounceInOut;
    }

    THROW(ArgumentOutOfRangeException{"Invalid easing type", "type"});
}

f32 Easing::FromType(const Type type, const f32 t)
{
    return FromType(type)(t);
}
