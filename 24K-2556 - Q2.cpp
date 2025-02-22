#include <iostream>
#include <ctime>
using namespace std;
class Ball
{
private:
    int x, y;

public:
    Ball()
    {
        x = 0;
        y = 0;
    }
    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    pair<int, int> getPosition() const
    {
        return {x, y};
    }
};
class Goal
{
private:
    const int goalX = 3;
    const int goalY = 3;

public:
    bool isGoal(int BallX, int BallY) const
    {
        return (BallX == goalX && BallY == goalY);
    }
};

class Robot
{
private:
    string name;
    int hits;

public:
    Robot(string n)
    {
        name = n;
        hits = 0;
    }
    void hitBall(Ball &ball, const string &direction)
    {
        if (direction == "up")
        {
            ball.move(0, 1);
        }
        else if (direction == "down")
        {
            ball.move(0, -1);
        }
        else if (direction == "left")
        {
            ball.move(-1, 0);
        }
        else if (direction == "right")
        {
            ball.move(1, 0);
        }
        hits++;
    }
    int getHits() const
    {
        return hits;
    }
    string getName() const
    {
        return name;
    }
};

class Team
{
private:
    Robot *robot;
    string TeamName;

public:
    Team(string name, string robotName) : TeamName(name)
    {
        robot = new Robot(robotName);
    }

    ~Team()
    {
        delete robot;
    }

    Robot *getRobot() const { return robot; }
    string getTeamName() const { return TeamName; }
};

class Game
{
private:
    Team *Team1;
    Team *Team2;
    Ball ball;
    Goal goal;

public:
    Game(Team *t1, Team *t2) : Team1(t1), Team2(t2) {}
    void play(Team *team)
    {
        Robot *robot = team->getRobot();

        ball = Ball();
        while (!goal.isGoal(ball.getX(), ball.getY()))
        {
            string directions[] = {"up", "down", "left", "right"};
            int randomIndex = rand() % 4;
            string direction = directions[randomIndex];
            robot->hitBall(ball, direction);
        }
        cout << team->getTeamName() << " reached the goal in " << robot->getHits() << " hits!" << endl;
    }

    void declareWinner()
    {
        int hitsTeamOne = Team1->getRobot()->getHits();
        int hitsTeamTwo = Team2->getRobot()->getHits();

        cout << "\nGame Over!" << endl;
        if (hitsTeamOne < hitsTeamTwo)
        {
            cout << Team1->getTeamName() << " wins with " << hitsTeamOne << " hits!" << endl;
        }
        else if (hitsTeamTwo < hitsTeamOne)
        {
            cout << Team2->getTeamName() << " wins with " << hitsTeamTwo << " hits!" << endl;
        }
        else
        {
            cout << "It's a tie with both teams having " << hitsTeamOne << " hits!" << endl;
        }
    }

    void startGame()
    {
        srand(time(0));
        cout << "Starting the game!\n"
             << endl;
        play(Team1);
        play(Team2);
        declareWinner();
    }
};

int main()
{
    cout << "Talha Mahboob" << " 24K-2556" << endl;
    Team teamOne("Team Alpha", "Robot A");
    Team teamTwo("Team Beta", "Robot B");
    Game game(&teamOne, &teamTwo);
    game.startGame();
    return 0;
}
