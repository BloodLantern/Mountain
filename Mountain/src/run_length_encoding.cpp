#include "run_length_encoding.hpp"

std::string mountain::RunLengthEncoding::Encode(const std::string& str)
{
    std::string letters;

    for (size_t j = 0; j < str.size(); ++j)
    {
        unsigned char count = 1;
        while (str[j] == str[j + 1])
        {
            count++;
            j++;
            if (count == 0xFF)
                break;
        }
        letters += count;
        letters += str[j];
    }

    return letters;
}

std::string mountain::RunLengthEncoding::Decode(const std::string& data)
{
    std::string result;

    for (size_t i = 0; i < data.size(); i += 2)
        result.append((unsigned char) data[i], data[i + 1]);

    return result;
}
