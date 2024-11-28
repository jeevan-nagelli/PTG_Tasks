#include <iostream>
#include <queue>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

enum EventType { TAP, SWIPE };  // define event types

// event class to hold event details like type, position, and timestamp
class Event {
public:
    EventType eventType;
    int x, y;
    std::time_t timestamp;

    Event(EventType type, int x, int y) : eventType(type), x(x), y(y) {
        timestamp = std::time(nullptr);  // capture the current time for the event
    }
};

// eventQueue class to manage and process a queue of events
class EventQueue {
private:
    std::queue<Event> events;  // queue to hold events

public:
    // add event to the queue
    void addEvent(Event event) {
        events.push(event);
    }

    // process all events in the queue
    void processEvents() {
        while (!events.empty()) {
            Event event = events.front();
            events.pop();
            handleEvent(event);  // handle each event
        }
    }

    // handle an individual event, display its details
    void handleEvent(Event event) {
        if (event.eventType == TAP) {
            std::cout << "Tap event at (" << event.x << ", " << event.y << ") at " << std::ctime(&event.timestamp);
        } else if (event.eventType == SWIPE) {
            std::string direction = calculateSwipeDirection(event.x, event.y);
            std::cout << "Swipe event in direction " << direction << " at " << std::ctime(&event.timestamp);
        }
    }

    // calculate the swipe direction based on x and y coordinates
    std::string calculateSwipeDirection(int x, int y) {
        if (std::abs(x) > std::abs(y)) {
            return (x > 0) ? "right" : "left";
        } else {
            return (y > 0) ? "down" : "up";
        }
    }
};

// generate a series of random events and add them to the event queue
void generateRandomEvents(EventQueue &queue, int numEvents) {
    for (int i = 0; i < numEvents; ++i) {
        EventType type = static_cast<EventType>(rand() % 2); // randomly select event type
        int x = rand() % 201 - 100;  // random x between -100 and 100
        int y = rand() % 201 - 100;  // random y between -100 and 100
        Event event(type, x, y);  // create event with random data
        queue.addEvent(event);  // add event to queue
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // seed random number generator
    EventQueue queue;

    generateRandomEvents(queue, 10);  // generate 10 random events
    queue.processEvents();  // process and display events

    return 0;
}
