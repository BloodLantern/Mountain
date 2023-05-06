#include "run_length_encoding.hpp"

std::string mountain::RunLengthEncoding::Encode(const std::string& str)
{
    std::string letters;

    for (unsigned int j = 0; j < str.size(); ++j)
    {
        unsigned int count = 1;
        while (str[j] == str[j + 1])
        {
            count++;
            j++;
        }
        letters += std::to_string(count);
        letters.push_back(str[j]);
    }

    return letters;
}

std::string mountain::RunLengthEncoding::Decode(const std::string& data)
{
    std::string result;

    for (size_t i = 0; i < data.size(); i += 2)
        for (unsigned char repeat = 0; repeat < data[i]; repeat++)
            result += data[i + 1];

    return result;
}
