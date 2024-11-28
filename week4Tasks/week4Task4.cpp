#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct Control {
    int id;
    string type;

    Control(int id, string type) : id(id), type(type) {}

    void display() const {
        cout << "id-> " << id << " type-> " << type << endl;
    }

    // Needed for set operations to compare `Control` objects by `id`
    bool operator<(const Control& other) const {
        return id < other.id;
    }
};

// Function to compare `Control` objects by `id`
bool compareById(const Control& a, const Control& b) {
    return a.id < b.id;
}

void callerFunction(vector<Control> controls1, vector<Control> controls2) {
    // Sorting using sort() (does not preserve relative order for equal elements)
    sort(controls1.begin(), controls1.end(), compareById);

    // Stable sort preserves relative order of equal elements
    stable_sort(controls2.begin(), controls2.end(), compareById);

    // Display sorted results
    cout << "Sorting the controls by their ID using sort (controls1):\n";
    for (const auto& control : controls1) {
        control.display();
    }

    cout << "\nStable sort to maintain relative order (controls2):\n";
    for (const auto& control : controls2) {
        control.display();
    }

    // Binary Search: Lower Bound and Upper Bound
    int search_id = 3;
    
    auto lb = lower_bound(controls1.begin(), controls1.end(), Control(search_id, ""), compareById);
    auto ub = upper_bound(controls2.begin(), controls2.end(), Control(search_id, ""), compareById);

    if (lb != controls1.end() && lb->id == search_id) {
        cout << "\nLower Bound (First control with ID " << search_id << "): " << lb->type << endl;
    } else {
        cout << "\nNo control found with ID " << search_id << " using lower_bound." << endl;
    }

    if (ub != controls2.begin()) {
        cout << "Upper Bound (First control with ID > " << search_id << "): " << (ub - 1)->type << endl;
    } else {
        cout << "No control found with ID > " << search_id << " using upper_bound." << endl;
    }

    // Merge two sorted lists of controls
    vector<Control> mergedControls;
    merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), back_inserter(mergedControls));

    cout << "\nMerged Controls:\n";
    for (const auto& control : mergedControls) {
        control.display();
    }

    // Merging segments using std::inplace_merge
    vector<Control> controls = {{1, "Slider"}, {3, "Button"}, {2, "Knob"}, {3, "Label"}, {4, "Display"}, {6, "Button"}, {8, "Toggle"}};
    sort(controls.begin(), controls.end(), compareById);  // Ensure the list is sorted
    inplace_merge(controls.begin(), controls.begin() + 3, controls.end());  // Merge the two sorted segments
    
    cout << "\nInplace Merged Controls:\n";
    for (const auto& control : controls) {
        cout << "ID: " << control.id << ", Type: " << control.type << endl;
    }

    // Set Operations - Set Union
    vector<Control> unionControls;
    set_union(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
              back_inserter(unionControls));

    cout << "\nUnion of Controls:\n";
    for (const auto& control : unionControls) {
        cout << "ID: " << control.id << ", Type: " << control.type << endl;
    }

    // Set Operations - Set Intersection
    vector<Control> intersectionControls;
    set_intersection(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(),
                     back_inserter(intersectionControls));

    cout << "\nIntersection of Controls:\n";
    for (const auto& control : intersectionControls) {
        cout << "ID: " << control.id << ", Type: " << control.type << endl;
    }
}

int main() {
    vector<Control> vec1 = {
        {1, "Slider"},
        {3, "Button"},
        {5, "Checkbox"},
        {7, "Dial"},
        {9, "Switch"}
    };

    vector<Control> vec2 = {
        {2, "Knob"},
        {3, "Label"},
        {4, "Display"},
        {6, "Button"},
        {8, "Toggle"}
    };

    // Calling the function to perform sorting, merging, and set operations
    callerFunction(vec1, vec2);

    return 0;
}
