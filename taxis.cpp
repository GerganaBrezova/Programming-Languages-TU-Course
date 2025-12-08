#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

int readInt(const string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX)
{
    string input;
    int value;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        bool valid = true;

        if (input.empty())
            valid = false;

        for (int i = 0; i < input.size(); i++)
        {
            if (!isdigit(input[i]))
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            cout << "Invalid integer! Digits only.\n";
            continue;
        }

        try
        {
            value = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid number format!\n";
            continue;
        }

        if (value < minVal || value > maxVal)
        {
            cout << "Number must be between " << minVal << " and " << maxVal << ".\n";
            continue;
        }

        return value;
    }
}

double readDouble(const string &prompt, double minVal = 0)
{
    string input;
    double value;

    while (true)
    {
        cout << prompt;
        getline(cin, input);

        // Validate format (optional decimal point, no plus sign)
        bool valid = true;
        bool decimalPointUsed = false;

        for (int i = 0; i < input.size(); i++)
        {
            char c = input[i];

            if (i == 0 && c == '-')
            {
                valid = false;
                break;
            } // no negative
            if (isdigit(c))
                continue;

            if (c == '.' && !decimalPointUsed)
            {
                decimalPointUsed = true;
                continue;
            }

            valid = false;
            break;
        }

        if (!valid || input.empty())
        {
            cout << "Invalid number! Positive values only.\n";
            continue;
        }

        try
        {
            value = stod(input);
        }
        catch (...)
        {
            cout << "Invalid number format.\n";
            continue;
        }

        if (value < minVal)
        {
            cout << "Invalid number! Must be >= " << minVal << ".\n";
            continue;
        }

        return value;
    }
}

string readString(const string &prompt)
{
    string s;
    while (true)
    {
        cout << prompt;

        getline(cin, s);

        if (s.empty())
        {
            cout << "Invalid text! Cannot be empty.\n";
            continue;
        }

        bool hasLetter = false;
        bool valid = true;

        for (char c : s)
        {
            if (isalpha(c))
                hasLetter = true;
            if (!isalnum(c) && c != '-' && c != ' ')
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            cout << "Invalid text! Only letters, numbers, spaces and hyphens are allowed.\n";
            continue;
        }

        if (!hasLetter)
        {
            cout << "Invalid text! Must contain at least one letter.\n";
            continue;
        }

        return s;
    }
}

class Route
{
private:
    vector<string> stops;
    double lengthKm;
    int dailyRuns;

public:
    Route() : lengthKm(0), dailyRuns(0) {}

    Route(vector<string> stops, double lengthKm, int dailyRuns)
        : stops(stops), lengthKm(lengthKm), dailyRuns(dailyRuns) {}

    vector<string> getStops() const { return stops; }
    double getLengthKm() const { return lengthKm; }
    int getDailyRuns() const { return dailyRuns; }

    void setStops(const vector<string> &s) { stops = s; }
    void setLengthKm(double l) { lengthKm = l; }
    void setDailyRuns(int d) { dailyRuns = d; }

    friend ostream &operator<<(ostream &out, const Route &r)
    {
        out << "Route: length " << r.lengthKm << " km, runs per day: " << r.dailyRuns << "\nStops:";
        for (const auto &s : r.stops)
            out << " " << s;
        out << "\n";
        return out;
    }
};

class Taxi
{
private:
    string brand;
    string model;
    int year;
    int seats;
    double capacity;
    double fuelConsumption;

public:
    Taxi() : year(0), seats(0), capacity(0), fuelConsumption(0) {}

    Taxi(string brand, string model, int year, int seats, double capacity, double fuelConsumption)
        : brand(brand), model(model), year(year), seats(seats), capacity(capacity), fuelConsumption(fuelConsumption) {}

    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    int getSeats() const { return seats; }
    double getCapacity() const { return capacity; }
    double getFuelConsumption() const { return fuelConsumption; }

    void setBrand(const string &b) { brand = b; }
    void setModel(const string &m) { model = m; }
    void setYear(int y) { year = y; }
    void setSeats(int s) { seats = s; }
    void setCapacity(double c) { capacity = c; }
    void setFuelConsumption(double f) { fuelConsumption = f; }

    friend ostream &operator<<(ostream &out, const Taxi &t)
    {
        out << "Brand: " << t.brand << ", Model: " << t.model
            << ", Year: " << t.year
            << ", Seats: " << t.seats
            << ", Load capacity: " << t.capacity
            << ", Consumption: " << t.fuelConsumption << " L/100km\n";
        return out;
    }
};

class Application
{
private:
    vector<Taxi> taxis;
    vector<Route> routes;

public:
    void addTaxi()
    {
        int currentYear = 2025;

        string brand = readString("Enter brand: ");
        string model = readString("Enter model: ");
        int year = readInt("Year: ", 1900, currentYear);
        int seats = readInt("Number of seats: ", 1, 15);
        double capacity = readDouble("Load capacity (kg): ");
        double fuel = readDouble("Fuel consumption (L/100 km): ");

        taxis.emplace_back(brand, model, year, seats, capacity, fuel);
    }

    void addRoute()
    {
        int stopsCount = readInt("Number of stops: ", 1);
        vector<string> stops;
        for (int i = 0; i < stopsCount; i++)
        {
            stops.push_back(readString("Stop " + to_string(i + 1) + ": "));
        }

        double length = readDouble("Length (km): ");
        int runs = readInt("Runs per day: ", 1, 50);

        routes.emplace_back(stops, length, runs);
    }

    void assignRoute()
    {
        if (taxis.empty() || routes.empty())
        {
            cout << "Not enough data!\n";
            return;
        }

        cout << "Select a taxi:\n";
        for (size_t i = 0; i < taxis.size(); i++)
        {
            cout << i << ") " << taxis[i];
        }
        int taxiIndex = readInt("Your choice: ", 0, taxis.size() - 1);

        cout << "Select a route:\n";
        for (size_t i = 0; i < routes.size(); i++)
        {
            cout << i << ") " << routes[i];
        }
        int routeIndex = readInt("Your choice: ", 0, routes.size() - 1);

        double neededFuel = (routes[routeIndex].getLengthKm() * routes[routeIndex].getDailyRuns()) * taxis[taxiIndex].getFuelConsumption() / 100.0;

        cout << "Fuel needed for the day: " << neededFuel << " liters\n";
    }

    void saveTaxisToFile()
    {
        ofstream file("taxis.txt");

        if (!file)
        {
            cout << "Error opening taxis.txt!\n";
            return;
        }

        for (auto &t : taxis)
        {
            file << "Brand: " << t.getBrand() << "\n"
                 << "Model: " << t.getModel() << "\n"
                 << "Year: " << t.getYear() << "\n"
                 << "Seats: " << t.getSeats() << "\n"
                 << "Load capacity: " << t.getCapacity() << "\n"
                 << "Consumption: " << t.getFuelConsumption() << " L/100km\n"
                 << "------------------------\n";
        }

        file.close();
        cout << "Taxis saved.\n";
    }

    void saveRoutesToFile()
    {
        ofstream file("routes.txt");

        if (!file)
        {
            cout << "Error opening routes.txt!\n";
            return;
        }

        for (auto &r : routes)
        {

            file << "Route: length " << r.getLengthKm() << " km\n"
                 << "Runs per day: " << r.getDailyRuns() << "\n"
                 << "Stops: ";

            for (auto &stop : r.getStops())
                file << stop << " ";

            file << "\n------------------------\n";
        }

        file.close();
        cout << "Routes saved.\n";
    }

    void menu()
    {
        while (true)
        {
            cout << "\n1. Add taxi\n"
                 << "2. Add route\n"
                 << "3. Assign route and calculate fuel\n"
                 << "4. Save taxis to file\n"
                 << "5. Save routes to file\n"
                 << "6. Exit\nChoice: ";

            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
            case 1:
                addTaxi();
                break;
            case 2:
                addRoute();
                break;
            case 3:
                assignRoute();
                break;
            case 4:
                saveTaxisToFile();
                break;
            case 5:
                saveRoutesToFile();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
    }
};

int main()
{
    Application app;
    app.menu();
    return 0;
}