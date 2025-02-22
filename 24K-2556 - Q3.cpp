#include <iostream>
using namespace std;

class User
{
private:
    int Age;
    string liscence_type;
    string contactinformation;
    int UserId;
    string name;

public:
    User(int age, string liscence, string contact, int id, string name)
    {
        this->Age = age;
        this->liscence_type = liscence;
        this->contactinformation = contact;
        this->UserId = id;
        this->name = name;
    }
    void updatedetails(int newage, string newliscence, string newcontact, int newid, string newname)
    {
        Age = newage;
        liscence_type = newliscence;
        contactinformation = newcontact;
        UserId = newid;
        name = newname;
    }
    string getliscencetype()
    {
        return liscence_type;
    }
    void displayuserdetails() const
    {
        cout << "Name: " << name << ", Age: " << Age << ", Contact Information: " << contactinformation << ", UserID: " << UserId << ", License Type: " << liscence_type << endl;
    }
};
class Vehicle
{
private:
    string Model;
    double RentalPrice;
    string EligibilityType;

public:
    Vehicle(string model, double price, string eligibility)
    {
        Model = model;
        RentalPrice = price;
        EligibilityType = eligibility;
    }
    bool isEligible(string userliscensetype)
    {
        return userliscensetype == EligibilityType || (EligibilityType == "Intermediate" && userliscensetype == "Full");
    }
    void diplaydetails() const
    {
        cout << "Model: " << Model << " RentalPrice:$ " << RentalPrice << " License Required: " << EligibilityType << endl;
    }
};
class VehicelRentalSystem
{
private:
    User *Registereduser;
    Vehicle *Vehicles[5];
    int vehicleCount;

public:
    VehicelRentalSystem()
    {
        Registereduser = nullptr;
        vehicleCount = 0;
    }
    void registerUser(int age, string liscence, string contact, int id, string name)
    {
        Registereduser = new User(age, liscence, contact, id, name);
        cout << "User Registered Successfully!" << endl;
    }
    void updateUserDetails(int newage, string newliscence, string newcontact, int newid, string newname)
    {
        if (Registereduser)
        {
            Registereduser->updatedetails(newage, newliscence, newcontact, newid, newname);
            cout << "User Details Updated Successfully!" << endl;
        }
        else
        {
            cout << "User Not Registered!" << endl;
        }
    }
    void addvehicle(string model, double price, string eligibility)
    {
        if (vehicleCount < 5)
        {
            Vehicles[vehicleCount] = new Vehicle(model, price, eligibility);
            vehicleCount++;
            cout << "Vehicle Added: " << model << endl;
        }
        else
        {
            cout << "Vehicle Rental System is Full!" << endl;
        }
    }
    void diplayAvailablevehicle() const
    {
        if (vehicleCount > 0)
        {
            cout << "Available Vehicles:" << endl;
            for (int i = 0; i < vehicleCount; i++)
            {
                Vehicles[i]->diplaydetails();
            }
        }
        else
        {
            cout << "No Vehicles Available!" << endl;
        }
    }
    void rentVehicle(int vehicleindex)
    {
        if (!Registereduser)
        {
            cout << "Please register user First!" << endl;
            return;
        }
        if (vehicleindex < 0 && vehicleindex < vehicleCount)
        {
            cout << "Invalid vehicle selected" << endl;
            return;
        }
        Vehicle *rentedvehicle = Vehicles[vehicleindex];
        if (rentedvehicle->isEligible(Registereduser->getliscencetype()))
        {
            cout << "Vehicle Rented successfully!" << endl;
            rentedvehicle->diplaydetails();
        }
        else
        {
            cout << "Selected Vehicle is not eligible for rental!" << endl;
        }
    }
    ~VehicelRentalSystem()
    {
        delete Registereduser;
        for (int i = 0; i < vehicleCount; i++)
        {
            delete Vehicles[i];
        }
    }
};

int main()
{
    cout << "Talha Mahboob" << " 24K-2556" << endl;
    VehicelRentalSystem rentalSystem;
    rentalSystem.registerUser(25, "Full", "440-456-7273", 25, "Amna");
    rentalSystem.addvehicle("Toyota Corolla", 50.0, "Learner");
    rentalSystem.addvehicle("Honda Civic", 60.0, "Intermediate");
    rentalSystem.addvehicle("Ford Mustang", 100.0, "Full");
    cout << endl;
    rentalSystem.diplayAvailablevehicle();
    cout << endl;
    rentalSystem.rentVehicle(0);
    cout << endl;
    rentalSystem.rentVehicle(2);
    cout << endl;
    rentalSystem.updateUserDetails(25, "Intermediate", "123-456-7822", 56, "Ahmed");
    rentalSystem.rentVehicle(1);
    return 0;
}
