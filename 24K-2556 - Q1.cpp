#include <iostream>
#include <string>
using namespace std;

class Skill
{
private:
    int skillID;
    string skillName;
    string description;

public:
    Skill()
    {
        skillID = 0;
        skillName = "";
        description = "";
    }
    Skill(int id, string name, string desc)
        : skillID(id), skillName(name), description(desc) {}

    int getSkillID()
    {
        return skillID;
    }

    void showSkillDetails()
    {
        cout << "Skill ID: " << skillID << ", Name: " << skillName
             << ", Description: " << description << endl;
    }

    void updateSkillDescription(string newDescription)
    {
        description = newDescription;
    }
};

class Sport
{
private:
    int sportID;
    string sportName;
    string description;
    Skill requiredskills[5];
    int skillCount;

public:
    Sport()
    {
        sportID = 0;
        sportName = "";
        description = "";
        skillCount = 0;
    }
    Sport(int id, string name, string desc)
        : sportID(id), sportName(name), description(desc), skillCount(0) {}
    int getSportID()
    {
        return sportID;
    }
    void removeSkill(int skillID)
    {
        bool removed = false;
        for (int i = 0; i < skillCount; i++)
        {
            if (requiredskills[i].getSkillID() == skillID)
            {
                removed = true;
                for (int j = i; j < skillCount - 1; j++)
                {
                    requiredskills[j] = requiredskills[j + 1];
                }
                skillCount--;
                cout << "Skill removed successfully" << endl;
                break;
            }
        }
        if (!removed)
        {
            cout << "Skill not found" << endl;
        }
    }
    void addSkill(Skill s)
    {
        if (skillCount < 5)
        {
            requiredskills[skillCount++] = s;
        }
        else
        {
            cout << "Maximum skill limit reached." << endl;
        }
    }
};

class Mentor;

class Student
{
private:
    int studentID;
    string name;
    int age;
    Sport sportinterest[3];

public:
    Mentor *mentorAssigned;
    Student(int id, string name, int a)
        : studentID(id), name(name), age(a), mentorAssigned(nullptr) {}
    string getname()
    {
        return name;
    }

    void registerForMentorship(Mentor *mentor);

    void viewMentorDetails(Mentor mentor);
    void updateSportInterest(Sport s)
    {
        for (int i = 0; i < 3; i++)
        {
            if (sportinterest[i].getSportID() == s.getSportID())
            {
                cout << "Sport interest already registered." << endl;
                return;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (sportinterest[i].getSportID() == 0)
            {
                sportinterest[i] = s;
                cout << "Sport interest registered successfully." << endl;
                return;
            }
        }
        cout << "Maximum sport interest reached." << endl;
    }
};

class Mentor
{
private:
    int mentorId;
    string name;
    Sport sportExpertise[5];
    int maxLearners;
    int learnerCount;
    Student *learnersAssigned[3];

public:
    Mentor(int id, string name, int max)
        : mentorId(id), name(name), maxLearners(max), learnerCount(0) {}
    string getMentorName()
    {
        return name;
    }

    int getMentorId()
    {
        return mentorId;
    }

    void assignLearner(Student *s)
    {
        if (learnerCount < maxLearners)
        {
            learnersAssigned[learnerCount++] = s;
            s->mentorAssigned = this;
            cout << "Learner assigned successfully" << endl;
        }
        else
        {
            cout << "Maximum learners reached" << endl;
        }
    }
    void removeLearner(Student *s)
    {
        bool removed = false;
        for (int i = 0; i < learnerCount; i++)
        {
            if (learnersAssigned[i] == s)
            {
                removed = true;
                for (int j = i; j < learnerCount - 1; j++)
                {
                    learnersAssigned[j] = learnersAssigned[j + 1];
                }
                learnersAssigned[--learnerCount] = nullptr;
                s->mentorAssigned = nullptr;
                cout << "Learner named " << s->getname() << " removed successful" << endl;
                break;
            }
        }
        if (!removed)
        {
            cout << "Learner not found" << endl;
        }
    }
    void viewAssignedLearners()
    {
        cout << "Assigned learners: " << endl;
        for (int i = 0; i < learnerCount; i++)
        {
            cout << learnersAssigned[i]->getname() << endl;
        }
        cout << endl;
    }
};

void Student::registerForMentorship(Mentor *mentor)
{
    if (mentorAssigned == nullptr)
    {
        mentor->assignLearner(this);
    }
    else
    {
        cout << "Mentorship already assigned" << endl;
    }
}

void Student::viewMentorDetails(Mentor mentor)
{
    cout << "Mentor Name: " << mentor.getMentorName() << endl;
    cout << "Mentor ID: " << mentor.getMentorId() << endl;
}

int main()
{
    cout << "Talha Mahboob" << " 24K-2556" << endl;
    Skill s1(1, "Basketball", "Plays basketball with a racket");
    Skill s2(2, "Football", "Plays football with a ball");
    Sport basketball(1, "Basketball", "A sport played on a court with a hoop");
    basketball.addSkill(s1);
    Mentor mentor1(1, "Zainab", 5);
    Student student1(1, "Shaheer", 18);
    Student student2(2, "Ayaan", 6);
    student1.updateSportInterest(basketball);
    student2.updateSportInterest(basketball);
    student1.registerForMentorship(&mentor1);
    student2.registerForMentorship(&mentor1);
    student1.viewMentorDetails(mentor1);
    student2.viewMentorDetails(mentor1);
    mentor1.viewAssignedLearners();
    mentor1.removeLearner(&student1);
    mentor1.viewAssignedLearners();
    return 0;
}
