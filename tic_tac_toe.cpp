#include <iostream>

#include <map>

#include <functional>

#include <conio.h>

#include <time.h>

#include <vector>

class _Tic_tac_toe
{
protected:
    std::map<char, char> _playboard = {
        {'1', '1'},{'2', '2'},{'3', '3'},
        {'4', '4'},{'5', '5'},{'6', '6'},
        {'7', '7'},{'8', '8'},{'9', '9'},
    };
    int count_board = 1;
    char symbol;
    char symbol1;
    char key;

public:
    void Welcome()
    {
        std::cout << "===Tic tac toe===\n";

        std::cout << "Progessing...0%\n";

        std::cout << "Progessing...50%\n";

        std::cout << "Progessing...100%\n\n";
    }
    void _Selected_Symbol()
    {
        int count_handle = 0;
        std::cout << "\n1 for x\n";

        std::cout << "2 for 0\n";

        std::cout << "Selected your symbol... \n";

        key = _getch();

        switch (key)
        {
        case '1':
            symbol = 'x';
            symbol1 = '0';
            break;
        case '2':
            symbol = '0';
            symbol1 = 'x';
            break;
        default:
            std::cout << "Invalid choice!\n";
            _Selected_Symbol();
            ++count_handle;

            break;
        };
    }
};
class Playboard : public _Tic_tac_toe
{
public:
    void _board()
    {
        for (auto &&entry : _playboard)
        {
            std::cout << entry.second << ' ';
            if (count_board == 3)
            {
                std::cout << '\n';
                count_board = 0;
            }

            count_board++;
        }
    }
};

class Player : public Playboard
{
private:
    void Player_Move()
    {
        std::cout << "Enter your move... \n\n";
        key = _getch();
        if (key == _playboard.find(key)->first)
        {
            _playboard.find(key)->second = symbol;
            _board();
        }
        else if(key == _playboard.find(key)->second && _playboard.find(key)->second == symbol)
        {
            std::cout << "Invalid move\n";
            Player_Move();
        }
    }
    protected:
    bool win_user = false;
    bool Player_Win()
    {
        char temp;
       for (auto &&entry : _playboard)
        {
            temp = entry.first;
            if (_playboard.find(temp + 0)->second == symbol && _playboard.find(temp + 1)->second == symbol && _playboard.find(temp + 2)->second == symbol)
            {
                return true;
            }
            if (_playboard.find(temp + 0)->second == symbol && _playboard.find(temp + 3)->second == symbol && _playboard.find(temp + 6)->second == symbol)
            {
                return true;
            }
            if (_playboard.find(temp + 0)->second == symbol && _playboard.find(temp + 4)->second == symbol && _playboard.find(temp + 8)->second == symbol)
            {
                return true;
            }
            if (_playboard.find(temp + 2)->second == symbol && _playboard.find(temp + 4)->second == symbol && _playboard.find(temp + 6)->second == symbol)
            {
                return true;
            }
            
        }

        return false;
    }

public:
    void Player_Handle()
    {

        Player_Move();
    }
};

class Comp : public Player
{
    private:
    int random;
    std::map<char,char> empty_pos;
    /*
    std::map<char, char> _playboard = {
        {'1', '1'},{'2', '2'},{'3', '3'},
        {'4', '4'},{'5', '5'},{'6', '6'},
        {'7', '7'},{'8', '8'},{'9', '9'},
    };
    */
    void Rand_Move()
    {
        srand(time(nullptr));

        random = rand() % (57 - 49 + 1) + 49;

        std::cout << "Computer random... \n\n";
         if (static_cast<char>(random) == _playboard.find(static_cast<char>(random))->second)
        {
            _playboard.find(static_cast<char>(random))->second = symbol1;
            _board();
        }
    }
    protected:
    bool win_comp = false;
    bool Comp_Win()
   {
    char temp;
    for (auto &&entry : _playboard)
    {
        temp = entry.first;

         if (_playboard.find(temp + 0)->second == symbol1 && _playboard.find(temp + 1)->second == symbol1 && _playboard.find(temp + 2)->second == symbol1)
            {
                return true;
            }
            if (_playboard.find(temp + 0)->second == symbol1 && _playboard.find(temp + 3)->second == symbol1 && _playboard.find(temp + 6)->second == symbol1)
            {
                return true;
            }
            if (_playboard.find(temp + 0)->second == symbol1 && _playboard.find(temp + 4)->second == symbol1 && _playboard.find(temp + 8)->second == symbol1)
            {
                return true;
            }
            if (_playboard.find(temp + 2)->second == symbol1 && _playboard.find(temp + 4)->second == symbol1 && _playboard.find(temp + 6)->second == symbol1)
            {
                return true;
            }
    }
        return false;
   }

    public:
    void Comp_Handle()
    {
        Rand_Move();
    }
};

class Play_Handle : public Comp
{
    private:
    bool GameState = true;
    int Count_State = 0;
    int Tie_Count = 0;
    void Playing_Handle()
    {
        while (GameState)
        {
            if (Count_State == 1)
            {
                Player_Handle();
                win_user = Player_Win();
                if (win_user == true)
                {
                    std::cout << "Player win!\n";
                    break;
                }
                
                ++Tie_Count;
                Count_State = 1;
            }
            if (Count_State == 2)
            {
                Comp_Handle();

                win_comp = Comp_Win();

                if (win_comp == true)
                {
                    std::cout << "Computer win!\n";
                    break;
                }
                
                ++Tie_Count;
                Count_State = 0;
            }
            if (win_comp == false && win_user == false && Tie_Count == 9)
            {
                std::cout << "Tie!\n";
                break;
            }
            
            ++Count_State;
        }
        
    }
    public:
    void Playing()
    {
        Playing_Handle();
    }
};

int main(int argc, char const *argv[])
{
    Play_Handle _game;

    _game.Welcome();

    _game._Selected_Symbol();

    _game._board();

    _game.Playing();

    return 0;
}
