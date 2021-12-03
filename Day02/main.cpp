#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    std::ifstream file;
    std::string line;
    int answer;

    file.open(argv[1]);
    if (argv[2][0] == '1')
    {
        int n, x = 0, y = 0;
        while(getline(file, line) && !line.empty())
        {
            int pos = line.find(' ', 0);
            std::string dir = line.substr(0, pos);
            n = std::stoi(line.substr(pos));
            if (dir == "forward") x += n;
            else if (dir == "up") y -= n;
            else if (dir == "down") y += n;
        }
        answer = x * y;
    }

    else if (argv[2][0] == '2')
    {
        int n, x = 0, y = 0, aim = 0;
        while(getline(file, line) && !line.empty())
        {
            int pos = line.find(' ', 0);
            std::string dir = line.substr(0, pos);
            n = std::stoi(line.substr(pos));
            if (dir == "forward")
            {
                x += n;
                y += aim * n;
            }
            else if (dir == "up") aim -= n;
            else if (dir == "down") aim += n;
        }
        answer = x * y;
    }

    file.close();

    std::cout << answer << std::endl;
}