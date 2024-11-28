#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct Control {    
    int id;               // Unique ID   
    string type;          // "button" or "slider"    
    string state;         // "visible", "invisible", "disabled"

    // Overloading operator== to compare only the 'id' field
    bool operator==(const Control& other) const {
        return id == other.id;
    }
}; 
void callerFuntion(vector<Control> controls){
     // Use of std::for_each to print all controls
    cout << "Use of for_each:" << endl;
    for_each(controls.begin(), controls.end(), [](const Control& ctrl) {
        cout << "ID: " << ctrl.id << ", Type: " << ctrl.type << ", State: " << ctrl.state << endl;
    });

    // Use of std::find to find a control with a specific ID (ID = 6)
    cout << "\nUse of std::find:" << endl;
    cout << "enter the targetID: " ;
    int targetID;
    cin >> targetID;
    Control target = {targetID, "", ""};  
    auto it = find(controls.begin(), controls.end(), target);

    if (it != controls.end()) {
        cout << "Found control with ID " << target.id << ": " << it->type << ", " << it->state << endl;
    } else {
        cout << "Control with ID " << target.id << " not found." << endl;
    }

    // Use of std::find_if: to find the first invisible control
    cout << "\nUsing std::find_if:" << endl;
    cout<<"enter the targetState that you want to find: ";
    string targetState;
    cin>>targetState;
    auto it2 = find_if(controls.begin(), controls.end(), [&targetState](const Control& ctrl){ return ctrl.state == targetState; });
    if (it2 != controls.end()) {
        cout << "First invisible control found at ID " << it2->id << ", Type: " << it2->type << ", State: " << it2->state << endl;
    } else {
        cout << "No invisible controls found." << endl;
    }

    // Use of std::adjacent_find: to check for consecutive controls with the same state
    cout << "\nUse of std::adjacent_find:" << endl;
    auto it3 = adjacent_find(controls.begin(), controls.end(), [](const Control& ctrl1, const Control& ctrl2) {
        return ctrl1.state == ctrl2.state;
    });

    if (it3 != controls.end()) {
        cout << "Consecutive controls with the same state found at ID " << it3->id << " and ID " << (it3 + 1)->id << endl;
    } else {
        cout << "No consecutive controls with the same state found." << endl;
    }

    // Using std::count: Count the number of visible controls
    cout << "\nUse of std::count:" << endl;
    cout<<"enter the targetState that you want to find count: ";
    string targetState2;
    cin>>targetState2;
    vector<Control> visibleControls;
    copy_if(controls.begin(), controls.end(), back_inserter(visibleControls), [&targetState2](const Control& ctrl) {
        return ctrl.state == targetState2;
    });

    //using std::count_if: Count sliders that are disabled.
    int disabledSliders = count_if(controls.begin(), controls.end(), [](const Control& ctrl) {
         return ctrl.type == "slider" && ctrl.state == "disabled";
        });
     cout << "Number of disabled sliders: " << disabledSliders << endl;

    //using std::equal: Compare two subranges of controls to check if they are identical.
    bool areEqual = equal(controls.begin(), controls.begin() + 2, controls.begin() + 5); 
    cout << "First two controls are " << (areEqual ? "equal" : "not equal") << " to the next two controls." << endl;
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
callerFuntion(vec);
    return 0;
}
