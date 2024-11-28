#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <list>

using namespace std;

// Singleton Pattern

class HMISystem {
private:
    static shared_ptr<HMISystem> instance;
    string currentMode;  // e.g., "Day" or "Night"

    // Private constructor to prevent direct instantiation
    HMISystem() : currentMode("Day") {}

public:
    // Getter for the instance of HMISystem
    static shared_ptr<HMISystem> getInstance() {
        if (!instance) {
            instance = shared_ptr<HMISystem>(new HMISystem());  // Using new to instantiate
        }
        return instance;
    }

    // Set the current mode (e.g., Day or Night)
    void setMode(const string& mode) {
        currentMode = mode;
    }

    // Get the current mode (e.g., Day or Night)
    string getMode() const {
        return currentMode;
    }

    // Display the current system mode
    void displayState() const {
        cout << "Current Mode: " << currentMode << endl;
    }
};

// Initialize the static member
shared_ptr<HMISystem> HMISystem::instance = nullptr;


//  Factory Pattern

// Base class for all controls
class Control {
public:
    virtual void render() = 0;  // Abstract method to render control
    virtual ~Control() = default;
};

// Concrete Control classes

// Button control
class Button : public Control {
public:
    void render() override {
        cout << "Rendering a Button" << endl;
    }
};

// Slider control
class Slider : public Control {
public:
    void render() override {
        cout << "Rendering a Slider" << endl;
    }
};

// Knob control
class Knob : public Control {
public:
    void render() override {
        cout << "Rendering a Knob" << endl;
    }
};

// Control Factory to create controls based on type
class ControlFactory {
public:
    // Create control based on type string
    static shared_ptr<Control> createControl(const string& type) {
        if (type == "Button") {
            return make_shared<Button>();
        } else if (type == "Slider") {
            return make_shared<Slider>();
        } else if (type == "Knob") {
            return make_shared<Knob>();
        } else {
            return nullptr;
        }
    }
};


// Observer Pattern 

class Observer {
public:
    virtual void update(const string& mode) = 0;  // Abstract method for mode update
    virtual ~Observer() = default;
};

// Concrete observer class representing a widget
class Widget : public Observer {
private:
    string name;
public:
    // Constructor to set widget name
    Widget(const string& name) : name(name) {}

    // Update method called when system mode changes
    void update(const string& mode) override {
        cout << name << " widget updated to " << mode << " mode." << endl;
    }
};

// Subject class to manage observers and notify them
class HMISystemWithObservers {
private:
    list<shared_ptr<Observer>> observers;  // List of observers
    string currentMode;  // Current system mode

public:
    // Add an observer to the list
    void addObserver(shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    // Remove an observer from the list
    void removeObserver(shared_ptr<Observer> observer) {
        observers.remove(observer);
    }

    // Set the current mode and notify observers
    void setMode(const string& mode) {
        currentMode = mode;
        notifyObservers();
    }

    // Notify all observers of the mode change
    void notifyObservers() {
        for (auto& observer : observers) {
            observer->update(currentMode);
        }
    }

    // Get the current mode
    string getMode() const {
        return currentMode;
    }
};


//  Strategy Pattern 

class RenderingStrategy {
public:
    virtual void render() = 0;  // Abstract method for rendering
    virtual ~RenderingStrategy() = default;
};

// Concrete Strategy for 2D rendering
class Rendering2D : public RenderingStrategy {
public:
    void render() override {
        cout << "Rendering in 2D mode." << endl;
    }
};

// Concrete Strategy for 3D rendering
class Rendering3D : public RenderingStrategy {
public:
    void render() override {
        cout << "Rendering in 3D mode." << endl;
    }
};

// Context class that uses the strategy
class HMIContext {
private:
    shared_ptr<RenderingStrategy> strategy;

public:
    // Set the rendering strategy
    void setStrategy(shared_ptr<RenderingStrategy> newStrategy) {
        strategy = newStrategy;
    }

    // Perform rendering based on the current strategy
    void render() {
        if (strategy) {
            strategy->render();
        } else {
            cout << "No rendering strategy set!" << endl;
        }
    }
};


// ---------------------------- Main Application ----------------------------

int main() {
    // Singleton usage: Access the single instance of HMISystem
    auto hmiSystem = HMISystem::getInstance();
    hmiSystem->displayState();  
    hmiSystem->setMode("Night"); 
    hmiSystem->displayState();  

    // Factory pattern usage: Create controls and render them
    auto button = ControlFactory::createControl("Button");
    button->render();  

    auto slider = ControlFactory::createControl("Slider");
    slider->render();  // Render a slider

    // Observer pattern usage: Register widgets to observe mode changes
    auto hmiWithObservers = make_shared<HMISystemWithObservers>();
    auto widget1 = make_shared<Widget>("Widget 1");
    auto widget2 = make_shared<Widget>("Widget 2");
    
    hmiWithObservers->addObserver(widget1);
    hmiWithObservers->addObserver(widget2);

    hmiWithObservers->setMode("Night");  // Change the mode and notify observers

    // Strategy pattern usage: Set rendering strategy and render
    HMIContext context;
    auto render2D = make_shared<Rendering2D>();
    auto render3D = make_shared<Rendering3D>();

    context.setStrategy(render2D);  
    context.render();  

    context.setStrategy(render3D); 
    context.render();  
    return 0;
}
