module Mountain:Utils_RunLengthEncoding;

import std;
import :Core_Types;

using namespace Mountain;

std::string RunLengthEncoding::Encode(const std::string& str)
{
    std::string letters;

    for (size_t j = 0; j < str.size(); ++j)
    {
        uint8_t count = 1;
        while (str[j] == str[j + 1])
        {
            count++;
            j++;
            if (count == 0xFF)
                break;
        }
        letters += static_cast<char_t>(count);
        letters += str[j];
    }

    return letters;
}

std::string RunLengthEncoding::Decode(const std::string& data)
{
    std::string result;

    for (size_t i = 0; i < data.size(); i += 2)
        result.append(static_cast<uint8_t>(data[i]), data[i + 1]);

    return result;
}
