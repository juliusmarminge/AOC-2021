#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

void printVec(const std::vector<std::string> &vec)
{
    std::cout << "[";
    for (auto str : vec)
        std::cout << str << ", ";
    std::cout << "]" << std::endl;
}

// Answer P1: 1131506
//std::bitset<8>("11011011").to_ulong();
int main(int argc, char *argv[])
{
    std::ifstream file;
    std::string line;

    std::vector<std::string> numbers;
    int answer;

    file.open(argv[1]);
    while(getline(file, line) && !line.empty())
        numbers.push_back(line);
    file.close();
    
    int line_len = numbers.at(0).length();

    if (argv[2][0] == '1')
    {
        std::string gamma, epsilon;
        for (int i = 0; i < line_len; i++)
        {
            int ones = 0;
            for (auto str : numbers)
            {
                if (str[i] == '1')
                    ones++;
            }
            gamma.push_back(ones > numbers.size() / 2 ? '1' : '0');
            epsilon.push_back(ones > numbers.size() / 2 ? '0' : '1');
        }
        answer = std::bitset<16>(gamma).to_ulong() * std::bitset<16>(epsilon).to_ulong();
    }

    if (argv[2][0] == '2')
    {
        auto filter_numbers = [](std::vector<std::string> numbers, char bit) -> std::string {

            int current_bit = 0;    // Starting at Most Significant
            while (numbers.size() > 1)
            {
                int ones = 0;
                for (auto str : numbers)
                {
                    if (str[current_bit] == '1')
                        ones++;
                }
                int zeroes = numbers.size() - ones;

                char to_keep;
                if (bit == '1')
                    to_keep = ones >= zeroes ? '1' : '0';
                else
                    to_keep = zeroes <= ones ? '0' : '1';

                for (int i = 0; i < numbers.size(); i++)
                {
                    if (numbers.at(i).at(current_bit) != to_keep)
                    {
                        numbers.erase(numbers.begin() + i);
                        i -= 1;
                    }
                }
                current_bit++;
            }
            return numbers.front();
        };
        std::string o2_generator = filter_numbers(numbers, '1');
        std::string co2_scrubber = filter_numbers(numbers, '0');
        answer = std::bitset<16>(o2_generator).to_ulong() * std::bitset<16>(co2_scrubber).to_ulong();            
    }

    std::cout << answer << std::endl;
}