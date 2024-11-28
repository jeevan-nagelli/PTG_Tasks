#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib> 
using namespace std;

struct Control {
    int id;
    string type;
    string state;

    Control(int id, string type, string state) : id(id), type(type), state(state) {}

    void display() const {
        cout << "id-> " << id << " type-> " << type << " state-> " << state << endl;
    }
};

void callingFuntion(vector<Control>& controls) {
    // Using std::copy to create a backup of the control list
    vector<Control> backup;
    copy(controls.begin(), controls.end(), back_inserter(backup));

    cout << "Backup Controls List: " << endl;
    for (const auto& a : backup) {
        a.display();
    }

    // Using std::fill to set all states to "disabled" temporarily.
    Control temp(0, "", "disabled");
    fill(backup.begin(), backup.end(), temp);
    cout << "After std::fill - Backup Controls List (all states set to 'disabled'): " << endl;
    for (const auto& a : backup) {
        a.display();
    }

    // Using std::generate to generate random states ("visible", "invisible", "disabled") for testing
    srand(time(0)); 
    auto generateRandomState = []() -> string {
        int randState = rand() % 3;
        if (randState == 0) return "visible";
        else if (randState == 1) return "invisible";
        else return "disabled";
    };
    
    std::generate(controls.begin(), controls.end(), [&]() {
        Control c = controls[rand() % controls.size()];
        c.state = generateRandomState();
        return c;
    });

    cout << "After std::generate - Random states assigned: " << endl;
    for (const auto& a : controls) {
        a.display();
    }

    // Using std::transform to change the state of all sliders to "invisible"
    std::transform(controls.begin(), controls.end(), controls.begin(), [](Control& control) {
        if (control.type == "slider") {
            control.state = "invisible";
        }
        return control;
    });

    cout << "After std::transform - All sliders set to 'invisible': " << endl;
    for (const auto& a : controls) {
        a.display();
    }

    // Using std::replace to replace "disabled" with "enabled" for testing
    std::replace_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "disabled";
    }, Control(0, "", "enabled"));  

    cout << "After std::replace - 'disabled' replaced with 'enabled': " << endl;
    for (const auto& a : controls) {
        a.display();
    }

    // Using std::remove_if to filter out invisible controls from the list
    controls.erase(std::remove_if(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "invisible";
    }), controls.end());

    cout << "After std::remove_if - Invisible controls removed: " << endl;
    for (const auto& a : controls) {
        a.display();
    }

    // Using std::reverse to reverse the control order
    std::reverse(controls.begin(), controls.end());

    cout << "After std::reverse - Reversed control order: " << endl;
    for (const auto& a : controls) {
        a.display();
    }

    // Using std::partition to group visible controls together
    auto partitionPoint = std::partition(controls.begin(), controls.end(), [](const Control& c) {
        return c.state == "visible";
    });

    cout << "After std::partition - Visible controls grouped at the beginning: " << endl;
    for (const auto& a : controls) {
        a.display();
    }
}

int main() {
    vector<Control> vec = {
        {1, "button", "visible"},
        {2, "button", "invisible"},
        {3, "button", "disabled"},
        {4, "button", "disabled"},
        {5, "button", "invisible"},
        {6, "slider", "visible"},
        {7, "slider", "disabled"},
        {8, "slider", "visible"},
        {9, "slider", "invisible"},
        {10, "slider", "disabled"}
    };

    
    callingFuntion(vec);

    return 0;
}
