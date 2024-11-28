#include <iostream>
#include <vector>
#include <string>

using namespace std;

//class for menu item
class MenuItem {
public:
    string name;  // name for the menu item
    vector<MenuItem> subMenu;  // Sub-menu with gives the user more options

    // Constructor to initialize name
    MenuItem(string name) : name(name) {}

    // Method to add a submenu item
    void addSubMenu(MenuItem item) {
        subMenu.push_back(item);
    }
};

// Class for menu system
class Menu {
private:
    vector<MenuItem> mainMenu;  
    vector<MenuItem*> currentMenu;  // to track of the currently active menu
    vector<vector<MenuItem*>> menuStack;  // Stack to store the history of menus for navigation

public:
    // Constructor to initialize main menu and submenus
    Menu() {
        // to create the 'Settings' menu item and submenus
        MenuItem settings("Settings");
        settings.addSubMenu(MenuItem("Display Settings"));
        settings.addSubMenu(MenuItem("Audio Settings"));

        // to create the 'Media' menu item and submenus
        MenuItem media("Media");
        media.addSubMenu(MenuItem("Radio"));
        media.addSubMenu(MenuItem("Bluetooth Audio"));

        // to add main menu items to vector
        mainMenu.push_back(settings);
        mainMenu.push_back(media);

        // initialize currentMenu with pointers to the main menu items
        currentMenu.push_back(&mainMenu[0]);  // settings
        currentMenu.push_back(&mainMenu[1]);  // media
    }

    // method to display the current menu options
    void displayMenu() {
        cout << "Current Menu Options:\n";
        for (size_t i = 0; i < currentMenu.size(); ++i) {
            cout << i + 1 << ". " << currentMenu[i]->name << "\n";  
        }
    }

    // method to navigate down to a submenu
    void navigateDown(int option) {
        if (option > 0 && option <= currentMenu.size()) {
            menuStack.push_back(currentMenu);  // to save the current menu to the stack 
            currentMenu.clear();  // clear the current menu to prepare for the new menu level

            for (auto& item : currentMenu[option - 1]->subMenu) {
                currentMenu.push_back(&item);  //to add the submenu items as new current menu options
            }
        } else {
            cout << "Invalid option\n";  // Handle invalid option selection
        }
    }

    // method to go back to the previous menu
    void goBack() {
        if (!menuStack.empty()) {
            currentMenu = menuStack.back();  // Restore the previous menu state
            menuStack.pop_back();  // Remove the top of the stack
        } else {
            cout << "Already at the main menu\n";  // if there is no menu to go back just print a message
        }
    }
};

int main() {
    Menu menu;  // Create a Menu object
    int choice;

    while (true) {
        menu.displayMenu();  // Display the current menu options
        cout << "Enter your choice (1 to navigate down, 2 to go up, 3 to exit): ";
        cin >> choice;  // Take user input for menu choice

        switch (choice) {
            case 1: {
                int option;
                cout << "Enter option number to navigate down: ";
                cin >> option;  // Get the submenu option to navigate to
                menu.navigateDown(option);  // Navigate to the selected submenu
                break;
            }
            case 2:
                menu.goBack();  // Go back to the previous menu
                break;
            case 3:
                return 0;  // Exit the program
            default:
                cout << "Invalid choice. Please try again.\n";  // Handle invalid input
                break;
        }
    }

    return 0;
}

