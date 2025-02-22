#include <iostream>
#include <string>
using namespace std;
class TransportationCard
{
private:
    int cardID;
    bool isActive;
    bool isPaid;
    class Student *student;
    static const float semesterFee;

public:
    TransportationCard(int id, class Student *s)
    {
        cardID = id;
        student = s;
        isActive = false;
        isPaid = false;
    }
    static float getSemesterFee()
    {
        return semesterFee;
    }
    void paySemesterFee()
    {
        isPaid = true;
        activate();
    }

    void activate()
    {
        if (isPaid)
        {
            isActive = true;
        }
    }

    bool checkActive()
    {
        return isActive;
    }

    class Student *getStudent()
    {
        return student;
    }
};

const float TransportationCard::semesterFee = 5000.0;

class BusStop
{
private:
    int stopID;
    string name;
    string location;

public:
    BusStop(int id, string n, string loc)
    {
        stopID = id;
        name = n;
        location = loc;
    }
    string getName()
    {
        return name;
    }
    int getStopID()
    {
        return stopID;
    }
};

class Student
{
private:
    int studentID;
    string name;
    TransportationCard *transportationCard;
    BusStop *pickupStop;
    BusStop *dropoffStop;

public:
    Student(int id, string n)
    {
        studentID = id;
        name = n;
        transportationCard = nullptr;
        pickupStop = nullptr;
        dropoffStop = nullptr;
    }
    void registerTransportation()
    {
        transportationCard = new TransportationCard(studentID, this);
    }

    void assignStops(BusStop *pickup, BusStop *dropoff)
    {
        pickupStop = pickup;
        dropoffStop = dropoff;
    }

    int getStudentID()
    {
        return studentID;
    }

    TransportationCard *getTransportationCard()
    {
        return transportationCard;
    }
    ~Student()
    {
        delete transportationCard;
    }
};

class Route
{
private:
    int routeID;
    BusStop **stops;
    int numStops;
    int maxStops;

public:
    Route(int id, int max)
    {
        routeID = id;
        maxStops = max;
        stops = new BusStop *[maxStops];
        numStops = 0;
    }

    ~Route()
    {
        delete[] stops;
    }

    void addStop(BusStop *stop)
    {
        if (numStops < maxStops)
        {
            stops[numStops] = stop;
            numStops++;
        }
    }

    void removeStop(int stopID)
    {
        for (int i = 0; i < numStops; i++)
        {
            if (stops[i]->getStopID() == stopID)
            {
                for (int j = i; j < numStops - 1; j++)
                {
                    stops[j] = stops[j + 1];
                }
                numStops--;
                break;
            }
        }
    }

    void displayRoute()
    {
        for (int i = 0; i < numStops; i++)
        {
            cout << stops[i]->getName() << endl;
        }
    }

    BusStop *getFirstStop()
    {
        if (numStops > 0)
        {
            return stops[0];
        }
        return nullptr;
    }

    BusStop *getNextStop(BusStop *currentStop)
    {
        for (int i = 0; i < numStops - 1; i++)
        {
            if (stops[i]->getStopID() == currentStop->getStopID())
            {
                return stops[i + 1];
            }
        }
        return nullptr;
    }
};

class Bus
{
private:
    int busID;
    Route *currentRoute;
    BusStop *currentStop;
    Student **studentsOnBoard;
    int numStudents;
    int capacity;

public:
    Bus(int id, int cap)
    {
        busID = id;
        capacity = cap;
        studentsOnBoard = new Student *[capacity];
        numStudents = 0;
        currentRoute = nullptr;
        currentStop = nullptr;
    }

    ~Bus()
    {
        delete[] studentsOnBoard;
    }

    void startRoute(Route *route)
    {
        currentRoute = route;
        currentStop = route->getFirstStop();
    }

    void moveToNextStop()
    {
        if (currentRoute && currentStop)
        {
            currentStop = currentRoute->getNextStop(currentStop);
        }
    }

    void attendance(TransportationCard *card)
    {
        if (card->checkActive())
        {
            Student *student = card->getStudent();
            if (numStudents < capacity)
            {
                studentsOnBoard[numStudents] = student;
                numStudents++;
            }
        }
    }

    BusStop *getCurrentStop()
    {
        return currentStop;
    }

    int getBusID()
    {
        return busID;
    }
};

class Attendance
{
private:
    int attendanceID;
    Student *student;
    Bus *bus;
    string timestamp;

public:
    Attendance(int id, Student *s, Bus *b, string time)
    {
        attendanceID = id;
        student = s;
        bus = b;
        timestamp = time;
    }

    void recordAttendance()
    {
        cout << "Attendance recorded for " << student->getStudentID() << " at " << timestamp << endl;
    }

    string getAttendanceDetails()
    {
        return "Student ID: " + to_string(student->getStudentID()) + ", Bus ID: " + to_string(bus->getBusID()) + ", Time: " + timestamp;
    }
};

int main()
{
    cout << "Talha Mahboob, ID : 24K-2556" << endl;
    BusStop nazimabad(5, "Nazimabad", "Nazimabad Petrol Pump");
    BusStop gulshan(1, "National Stadium", "Mashriq cneter");
    BusStop johar(2, "Gulzar hijri", "Main University Road");
    BusStop nipa(3, "Nipa", "Nipa Chowrangi");
    BusStop safoora(4, "Safoora", "Scheme 33");
    BusStop fastnu(6, "Fast NU", "FAST NUCES Karachi Campus");
    BusStop malir(7, "Malir", "Cp5");

    Route route1(105, 7);
    route1.addStop(&nazimabad);
    route1.addStop(&gulshan);
    route1.addStop(&nipa);
    route1.addStop(&johar);
    route1.addStop(&safoora);
    route1.addStop(&malir);
    route1.addStop(&fastnu);

    Student talha(1, "Talha");
    talha.registerTransportation();
    talha.assignStops(&gulshan, &fastnu);
    talha.getTransportationCard()->paySemesterFee();

    Bus bus1(501, 10);
    bus1.startRoute(&route1);
    bus1.attendance(talha.getTransportationCard());

    while (bus1.getCurrentStop() != nullptr)
    {
        cout << "Bus is at: " << bus1.getCurrentStop()->getName() << endl;
        bus1.moveToNextStop();
    }
    return 0;
}
