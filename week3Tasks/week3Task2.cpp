#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

// class to handle car data
class CarData {
private:
    float speed, fuel, temp;
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> speedDist{0, 150};
    uniform_real_distribution<> fuelDist{0, 100};
    uniform_real_distribution<> tempDist{70, 120};

public:
    // constructor initializes random number generator and data
    CarData() : gen(rd()), speed(0), fuel(100), temp(90) {}

    // update car data with random values
    void update() {
        speed = speedDist(gen);
        fuel = fuelDist(gen);
        temp = tempDist(gen);
    }

    // Getter functions for car data
    float getSpeed() const { return speed; }
    float getFuel() const { return fuel; }
    float getTemp() const { return temp; }
};

// for displaying the car data on screen
class Display {
private:
    CarData& data;  // Reference to CarData object
    mutex mtx;

public:
    Display(CarData& carData) : data(carData) {}

    // display car data with warnings if necessary
    void show() {
        lock_guard<mutex> lock(mtx);  // lock to prevent race conditions
        cout << "\rSpeed: " << fixed << setprecision(1) << data.getSpeed() << " km/h"
             << " | Fuel: " << data.getFuel() << "%"
             << " | Temp: " << data.getTemp() << "°C";

        if (data.getFuel() < 10) {  // low fuel warning
            cout << " | WARNING: Low Fuel!";
        }
        if (data.getTemp() > 100) {  // high temperature warning
            cout << " | WARNING: High Temp!";
        }

        cout.flush();
    }
};

// function to continuously update car data
void updateData(CarData& carData) {
    while (true) {
        carData.update();
        this_thread::sleep_for(chrono::seconds(1)); 
    }
}

// Function to continuously display car data
void displayData(Display& display) {
    while (true) {
        display.show();
        this_thread::sleep_for(chrono::seconds(1));  
    }
}

int main() {
    CarData carData;  // create CarData object
    Display display(carData);  // create Display object

    // start threads for updating data and displaying data
    thread updateThread(updateData, ref(carData));
    thread displayThread(displayData, ref(display));

    // join threads to main thread 
    updateThread.join();
    displayThread.join();

    return 0;
}
