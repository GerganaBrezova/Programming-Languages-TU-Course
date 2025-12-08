# Taxi Management System
C++ Course Assignment – Technical University

This repository contains the solution to a coursework assignment for the C++ programming course at the Technical University.
The project implements a simple console application for managing taxis and routes, storing them, and assigning routes to available taxis.

# Task Description
The goal is to implement a C++ console application that manages:

- A list of taxis
- A list of routes
- Functionality for adding, viewing, and saving data to files
- Functionality for assigning a route to a selected taxi

The application follows an OOP approach with separate classes for data representation and a main class that handles the program logic.

# Project Structure
The project contains the following classes:

- Taxi – represents information about a taxi
- Route – represents information about a route
- Application – handles user interaction and the application menu

# UML Class Diagram

  classDiagram
    class Taxi {
        - string brand
        - string model
        - int year
        - int seats
        - double capacity
        - double fuelConsumption
        + getBrand() string
        + getModel() string
        + getYear() int
        + getSeats() int
        + getCapacity() double
        + getFuelConsumption() double
        + setBrand(string)
        + setModel(string)
        + setYear(int)
        + setSeats(int)
        + setCapacity(double)
        + setFuelConsumption(double)
    }

    class Route {
        - vector<string> stops
        - double lengthKm
        - int dailyRuns
        + getStops() vector<string>
        + getLengthKm() double
        + getDailyRuns() int
        + setStops(vector<string>)
        + setLengthKm(double)
        + setDailyRuns(int)
    }

    class Application {
        - vector<Taxi> taxis
        - vector<Route> routes
        + addTaxi() void
        + addRoute() void
        + assignRoute() void
        + saveTaxisToFile() void
        + saveRoutesToFile() void
        + menu() void
    }

    Application --> Taxi
    Application --> Route


# Class Descriptions

# Class Taxi
This class represents a single taxi and stores:
- Brand
- Model
- Year
- Number of seats
- Load capacity
- Fuel consumption

It provides getter and setter methods and an output operator (operator<<).

# Class Route
A route includes:
- A list of stops
- Route length (in km)
- Number of daily runs

Like the Taxi class, it provides getter/setter methods and an output operator.

# Class Application
The main controller class of the system.
Responsibilities:
- Adding a taxi
- Adding a route
- Assigning a route to a selected taxi
- Saving taxis and routes to files
- Displaying the application menu
- It stores the data in:
  vector<Taxi> taxis;
  vector<Route> routes;

# How to Run the Program

Run the application: ./app
Use the menu to navigate:
- Add a taxi
- Add a route
- Assign a route to a taxi
- Save data to files
- Exit
  
# File Output
The program automatically saves:
- taxis.txt – all entered taxis
- routes.txt – all entered routes

Each record is written on a separate line in a readable format.

# License
This project is provided for educational purposes as part of a university assignment.
