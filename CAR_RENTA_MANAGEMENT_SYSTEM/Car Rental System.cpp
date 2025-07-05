#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Function declarations to resolve scope errors
void adminLogin(class Admin& admin);
void customerMenu(class Admin& admin);




// Base class Vehicle
class Vehicle {
protected:
    string brand;
    string model;
    int year;

public:
    // Default constructor
    Vehicle() {}

    // Parameterized constructor
    Vehicle(string& brand, string& model, int year)
        : brand(brand), model(model), year(year) {}

    // Getters
    string getBrand() { return brand; }
    string getModel() { return model; }
    int getYear() { return year; }
};

// Derived class Car
class Car : public Vehicle {
private:
    string powerType;
    int rentalRate;

public:
    // Default constructor
    Car() {}

    // Parameterized constructor
    Car(string& brand, string& model, int year, string& powerType, int rentalRate)
        : Vehicle(brand, model, year), powerType(powerType), rentalRate(rentalRate) {}

    // Getters
    string getPowerType() { return powerType; }
    int getRentalRate() { return rentalRate; }
};

// Admin class
class Admin {
private:
    string username;
    string password;
    static const int MAX_CARS = 1000;
    Car cars[MAX_CARS];
    int carCount;

public:
    // Constructor
    Admin(string& user, string& pass) : username(user), password(pass), carCount(0) {
        initializeCars();
    }

    // Function to authenticate admin login
    bool authenticate(string& usernameAttempt, string& passwordAttempt) {
        return usernameAttempt == username && passwordAttempt == password;
    }

    // Function to initialize cars from a file
    void initializeCars() {
        ifstream carFile("cars.txt");
        if (!carFile) {
            cerr << "Error: Could not open the car file." << endl;
            return;
        }

        string brand, model, powerType;
        int year, rentalRate;

        while (carFile >> brand >> model >> year >> powerType >> rentalRate) {
            cars[carCount++] = Car(brand, model, year, powerType, rentalRate);
        }

        carFile.close();
    }

    // Function to update the car file
    void updateCarFile() {
        ofstream carFile("cars.txt");
        if (!carFile) {
            cerr << "Error: Could not open the car file for writing." << endl;
            return;
        }
;
        for (int i = 0; i < carCount; ++i) {
            Car& car = cars[i];
            carFile << car.getBrand() << " " << car.getModel() << " " << car.getYear() << " "
                    << car.getPowerType() << " " << car.getRentalRate() << endl;
        }

        carFile.close();
    }

    // Function to add a new car
    void addNewCar() {
        system("cls");  // Clear the screen before adding a new car
        if (carCount >= MAX_CARS) {
            cout << "Cannot add more cars. Maximum limit reached." << endl;
            return;
        }

        string brand, model, powerType;
        int year, rentalRate;

        cout << "========================= ADD CAR =========================" << endl;
        cout << "Please enter the following details to add a new car:" << endl;
        cout << "-----------------------------------------------------------" << endl;

        cout << "Brand: ";
        cin.ignore();
        getline(cin, brand);

        cout << "Model: ";
        getline(cin, model);

        cout << "Year: ";
        cin >> year;

        cout << "Power Type (Electric/Combustion): ";
        cin >> powerType;

        cout << "Rental Rate: ";
        cin >> rentalRate;

        cars[carCount++] = Car(brand, model, year, powerType, rentalRate);
        updateCarFile();

        cout << "\nCar added successfully!" << endl;

        char choice;
        cout << "Do you want to add another car? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            addNewCar();
        }
    }

    void showCars() {
        system("cls");  // Clear the screen before showing the list of cars
        if (carCount == 0) {
            cout << "No cars in the database." << endl;
        } else {
            cout << "======================================================" << endl;
            cout << "|                   List of Cars                      |" << endl;
            cout << "======================================================" << endl;
            cout << "| ID | Brand        | Model        | Year | Rental Rate|" << endl;
            cout << "------------------------------------------------------" << endl;
            for (int i = 0; i < carCount; ++i) {
                Car& car = cars[i];
                cout << "| " << setw(2) << i + 1 << " | " << setw(12) << car.getBrand() << " | " << setw(12) << car.getModel()
                     << " | " << setw(4) << car.getYear() << " | $" << setw(10) << car.getRentalRate() << " |" << endl;
            }
            cout << "======================================================" << endl;
        }
        system("pause"); // Pause the screen to allow the user to see the list
    }
    

    // Function to remove a car
    void removeCar() {
        char choice;
        do {
            system("cls");  // Clear the screen before removing a car

            if (carCount == 0) {
                cout << "No cars in the database." << endl;
                return;
            }

            cout << "======================================================" << endl;
            cout << "|                   Remove Car                        |" << endl;
            cout << "======================================================" << endl;
            cout << "| ID | Brand        | Model        | Year | Rental Rate|" << endl;
            cout << "------------------------------------------------------" << endl;
            for (int i = 0; i < carCount; ++i) {
                Car& car = cars[i];
                cout << "| " << setw(2) << i + 1 << " | " << setw(12) << car.getBrand() << " | " << setw(12) << car.getModel() << " | " << setw(4) << car.getYear() << " | $" << setw(10) << car.getRentalRate() << " |" << endl;
            }
            cout << "------------------------------------------------------" << endl;

            cout << "Enter the number of the car you want to remove (1-" << carCount << "): ";
            int index;
            cin >> index;

            if (index < 1 || index > carCount) {
                cout << "Invalid car number." << endl;
            } else {
                for (int i = index - 1; i < carCount - 1; ++i) {
                    cars[i] = cars[i + 1];
                }
                --carCount;
                cout << "Car removed successfully!" << endl;
                updateCarFile(); // Update the file after removing the car
            }

            if (carCount == 0) {
                cout << "No cars left to delete." << endl;
                break;
            }

            cout << "Do you want to remove another car? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');
    }

    // Getters for cars and car count
    Car* getCars() { return cars; }
    int getCarCount() { return carCount; }

    // Admin menu function
    void adminMenu() {
        int adminChoice;
        do {
            system("cls");  // Clear the screen before showing the admin menu
            cout << "======================================================" << endl;
            cout << "|                      Admin Menu                     |" << endl;
            cout << "======================================================" << endl;
            cout << "| 1. Add New Car                                      |" << endl;
            cout << "| 2. Show Cars                                        |" << endl;
            cout << "| 3. Remove Car                                       |" << endl;
            cout << "| 4. Return to Main Menu                              |" << endl;
            cout << "------------------------------------------------------" << endl;
            cout << "Enter your choice: ";
            while (!(cin >> adminChoice) || adminChoice < 1 || adminChoice > 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid choice: ";
            }

            switch (adminChoice) {
                case 1:
                    addNewCar();
                    break;
                case 2:
                    showCars();
                    break;
                case 3:
                    removeCar();
                    break;
                case 4:
                    return; // Return to the main menu
                default:
                    cout << "Invalid choice." << endl;
            }
        } while (true);
    }
};

// Customer class
class Customer {
public:
    // Function to rent a car
    static void rentCar(Admin& admin) {
        system("cls");  // Clear the screen before renting a car
        int carChoice;
        do {
            admin.showCars();  // Show available cars
            cout << "Enter the car ID to rent (0 to go back): ";
            while (!(cin >> carChoice) || carChoice < 0 || carChoice >
                        admin.getCarCount()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter a valid car ID: ";
            }
            if (carChoice == 0) return;  // Return to the main menu if 0 is entered

            // Get the selected car
            Car* selectedCar = admin.getCars() + carChoice - 1; // Ensure the selectedCar is not const
            system("cls");  // Clear the screen before showing the invoice
            cout << "======================================================" << endl;
            cout << "|             Car Rental - Customer Invoice           |" << endl;
            cout << "======================================================" << endl;
            cout << "Car details: " << endl;
            cout << "Brand: " << selectedCar->getBrand() << endl;
            cout << "Model: " << selectedCar->getModel() << endl;
            cout << "Year: " << selectedCar->getYear() << endl;
            cout << "Rental Rate: $" << selectedCar->getRentalRate() << " per day" << endl;

            // Collect customer information
            string customerName;
            string customerCNIC;
            int customerAge;
            int rentalDays;

            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, customerName);

            cout << "Enter your age: ";
            while (!(cin >> customerAge) || customerAge < 0 || customerAge > 150) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid age: ";
            }

            cout << "Enter your CNIC: ";
            cin.ignore();
            getline(cin, customerCNIC);

            cout << "Enter number of rental days: ";
            while (!(cin >> rentalDays) || rentalDays <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number of days: ";
            }

            // Calculate total rental amount
            int totalAmount = rentalDays * selectedCar->getRentalRate();

            // Display the invoice
            cout << "======================================================" << endl;
            cout << "|                   Customer Invoice                   |" << endl;
            cout << "======================================================" << endl;
            cout << "| Customer Name: " << setw(26) << left << customerName << "|" << endl;
            cout << "| Customer Age: " << setw(27) << left << customerAge << "|" << endl;
            cout << "| Customer CNIC: " << setw(25) << left << customerCNIC << "|" << endl;
            cout << "| Car Model: " << setw(30) << left << selectedCar->getModel() << "|" << endl;
            cout << "| Car No.: " << setw(32) << left << selectedCar->getBrand() << "|" << endl;
            cout << "| Number of Days: " << setw(27) << left << rentalDays << "|" << endl;
            cout << "| Rental Amount: " << setw(28) << left << "$" << totalAmount << "|" << endl;
            cout << "======================================================" << endl;

            // Ask if the customer wants to rent another car
            char choice;
            cout << "Do you want to rent another car? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                continue;  // Continue renting another car if 'y' is chosen
            } else {
                return;  // Return to the main menu
            }
        } while (true);
    }
};

void showMainMenu() {
    std::string username = "admin";
    std::string password = "password";
    Admin admin(username, password); // Changed the password to match the length
    int mainChoice;
    do {
        system("cls");  // Clear the screen before showing the main menu
        cout << "======================================================" << endl;
        cout << "|                     Main Menu                       |" << endl;
        cout << "======================================================" << endl;
        cout << "| 1. Admin Login                                      |" << endl;
        cout << "| 2. Customer Menu                                    |" << endl;
        cout << "| 3. Exit                                             |" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> mainChoice) || mainChoice < 1 || mainChoice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (mainChoice) {
            case 1:
                adminLogin(admin);
                break;
            case 2:
                customerMenu(admin);
                break;
            case 3:
                cout << "Exiting the program. Thank you!" << endl;
                exit(0); // Terminate the program
            default:
                cout << "Invalid choice." << endl;
        }
    } while (true);
}


/// Function to handle admin login
void adminLogin(Admin& admin) {
    string usernameAttempt, passwordAttempt;

    cout << "======================================================" << endl;
    cout << "|                   Admin Login                       |" << endl;
    cout << "======================================================" << endl;

    bool loginSuccess = false;
    int attempts = 3;
    while (attempts > 0) {
        system("cls");  // Clear the screen before showing the admin login screen
        cout << "======================================================" << endl;
        cout << "|                   Admin Login                       |" << endl;
        cout << "======================================================" << endl;

        cout << "Enter username: ";
        cin >> usernameAttempt;
        cout << "Enter password: ";
        cin >> passwordAttempt;

        if (admin.authenticate(usernameAttempt, passwordAttempt)) {
            loginSuccess = true;
            break;
        } else {
            system("cls");  // Clear the screen before showing the admin login screen
            cout << "======================================================" << endl;
            cout << "|                   Admin Login                       |" << endl;
            cout << "======================================================" << endl;
            cout << "Invalid username or password. " << attempts << " attempts remaining." << endl;
            cout << "Please try again." << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            --attempts;
        }
    }

    if (loginSuccess) {
        admin.adminMenu(); // Enter the admin menu upon successful login
    } else {
        system("cls");
        cout << "You have exhausted all login attempts. Exiting the program." << endl;
    }
}

// Function to handle customer menu
void customerMenu(Admin& admin) {
    int customerChoice;
    do {
        system("cls");  // Clear the screen before showing the customer menu
        cout << "======================================================" << endl;
        cout << "|                  Customer Menu                      |" << endl;
        cout << "======================================================" << endl;
        cout << "| 1. Rent a Car                                       |" << endl;
        cout << "| 2. Return to Main Menu                              |" << endl;
        cout << "------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> customerChoice) || customerChoice < 1 || customerChoice > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (customerChoice) {
            case 1:
                Customer::rentCar(admin);
                break;
            case 2:
                return; // Return to the main menu
            default:
                cout << "Invalid choice." << endl;
        }
    } while (true);
}

// Main function
int main() {
    showMainMenu();
    return 0;
}
