#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char *argv[]) 
{
    std::ifstream file;
    std::string line;
    file.open(argv[1]);

    int answer = 0;

    if (argv[2][0] == '1')
    {
        int prev = -1, curr;
        while(getline(file,line) && !line.empty())
        {
            curr = std::stoi(line);
            if (prev > 0 && curr > prev) answer++;
            prev = curr;
        }
    }

/*    a=-1     b=-1    c=-1   d=-1
199   a=199    b=-1    c=-1   d=-1   
200   a=200    b=199   c=-1   d=-1 
208   a=208    b=200   c=199  d=-1          <-- first
210   a=210    b=208   c=200  d=199
200   a=200    b=210   c=208  d=200
207
240
269
260
263
*/
    if (argv[2][0] == '2')
    {
        int a = -1, b = -1, c = -1, d = -1;
        int prev = -1, curr;
        while (getline(file, line) && !line.empty())
        {
            a = std::stoi(line);
            curr = a + b + c;
            if (a > 0 && b > 0 && c > 0 && d > 0 && curr > prev) answer++;
            prev = curr;
            d = c;
            c = b;
            b = a;
        }
    }

    file.close();

    std::cout << answer << std::endl;

}

