#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>

#define BOARD_SIZE 5
#define BOARDS_CAP 128
#define CROSSED -1

struct Board
{
    int data[BOARD_SIZE][BOARD_SIZE];
};
Board boards[BOARDS_CAP];
int boards_size = 0;

std::string ReadFile(char filename[])
{
    std::string data;
    std::ifstream file;
    std::string line;
    file.open(filename);
    while (std::getline(file, line))
    {
        data.append(line);
        data.push_back('\n');
    }
    file.close();
    return data;
}

std::vector<int> ParseNums(std::string data)
{
    std::vector<int> nums;
    int pos1 = 0, pos2 = 0;
    while((pos2 = data.find(',', pos1)) != std::string::npos)
    {
        nums.push_back(std::stoi(data.substr(pos1, pos2-pos1)));
        pos1 = pos2 + 1;

    }
    nums.push_back(std::stoi(data.substr(pos1)));
    return nums;
}

void ParseBoards(std::string data)
{
    std::stringstream ss;
    ss << data;
    int num, i = 0, j = 0;
    Board *board = &boards[boards_size];
    while (ss >> num)
    {
        if (j >= BOARD_SIZE)
        {
            i++;
            j = 0;
        }
        if (i >= BOARD_SIZE)
        {
            //printf("\n");
            board = &boards[++boards_size];
            i = 0;
            j = 0;
        }
        //printf("board[%d][%d] = %*d\n", i, j, 2, num);
        board->data[i][j] = num;
        j++;
    }
    boards_size++;
}

void MarkBoard(Board *board, int num)
{
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
            if(board->data[i][j] == num)
                board->data[i][j] = CROSSED;
}

bool CheckWin(Board *board)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        int j = 0;
        while (j < BOARD_SIZE && board->data[i][j] == CROSSED) j++;
        if (j >= BOARD_SIZE) return true;
        j = 0;
        while (j < BOARD_SIZE && board->data[j][i] == CROSSED) j++;
        if (j >= BOARD_SIZE) return true;
    }
    return false;
}

int SumUnmarked(Board *board)
{
    int sum = 0;
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
            if(board->data[i][j] != CROSSED)
                sum += board->data[i][j];
    return sum;
}

void PrintBoard(Board *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board->data[i][j] == CROSSED)
                printf("(%*d) ", 2, board->data[i][j]);
            else
                printf(" %*d  ", 2, board->data[i][j]);
        }    
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string data = ReadFile(argv[1]);
    int pos = data.find('\n');
    std::vector<int> nums = ParseNums(data.substr(0, pos));
    ParseBoards(data.substr(pos+2));

    if (argv[2][0] == '1')
    {
        for (auto num : nums) 
            for (int i = 0; i < boards_size; i++)
            {
                Board *board = &boards[i];
                MarkBoard(board, num);
                if(CheckWin(board))
                {
                    printf("num=%d, sum=%d, part1: %d\n", num, SumUnmarked(board), num * SumUnmarked(board));
                    return 0;
                }
            }
    }
    
    if (argv[2][0] == '2')
    {
        int board_wins = 0;
        for (auto num : nums) 
        {
            for (int i = 0; i < boards_size; i++)
            {
                Board *board = &boards[i];
                if (!CheckWin(board))
                {
                    MarkBoard(board, num);
                    if(CheckWin(board))
                        board_wins++;
                    if (board_wins == boards_size)
                    {
                        printf("num=%d, sum=%d, part2: %d\n", num, SumUnmarked(board), num * SumUnmarked(board));
                        return 0;
                    }
                }   
            }
        }
    }

    return 0;
}