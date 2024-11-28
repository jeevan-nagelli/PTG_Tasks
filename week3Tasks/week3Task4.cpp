#include <iostream>
#include <string>
#include <map>

using namespace std;

// class to represent a theme with background color, font color, font size, and icon style
class Theme {
public:
    string backgroundColor;
    string fontColor;
    string fontSize;
    string iconStyle;

    // constructor with arguments to initialize theme properties
    Theme(string bgColor, string fontColor, string fontSize, string iconStyle) 
        : backgroundColor(bgColor), fontColor(fontColor), fontSize(fontSize), iconStyle(iconStyle) {}

    // default constructor initializes with default values
    Theme() 
        : backgroundColor("White"), fontColor("Black"), fontSize("12"), iconStyle("Default") {}

    // function to apply the theme (print theme details)
    void apply() {
        cout << "Applying Theme: \n";
        cout << "Background Color: " << backgroundColor << endl;
        cout << "Font Color: " << fontColor << endl;
        cout << "Font Size: " << fontSize << endl;
        cout << "Icon Style: " << iconStyle << endl;
    }
};

int main() {
    map<string, Theme> themes;  // map to store themes by name

    // adding predefined themes to the map
    themes["Classic"] = Theme("White", "Black", "12", "Default");
    themes["Sport"] = Theme("Red", "White", "14", "Bold");
    themes["Eco"] = Theme("Green", "Black", "12", "Simple");

    // prompt user to choose a theme
    string themeChoice;
    cout << "Choose a theme: Classic, Sport, or Eco: ";
    cin >> themeChoice;

    // check if the chosen theme exists in the map and apply it
    if (themes.find(themeChoice) != themes.end()) {
        cout << themeChoice << " Theme: \n";
        themes[themeChoice].apply();
    } else {
        cout << "Invalid theme choice!" << endl;  // handle invalid input
    }

    return 0;
}
