#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

class Room {
private:
    int room_number_;          // Room number
    double room_size_;         // Room size in square meters
    std::string floor_type_;   // Floor type (e.g., "Carpet", "Tile", "Wood")
    bool is_available_;        // Availability status (true if available)

public:
    // Constructor
    Room(int room_number, double room_size, const std::string& floor_type, bool is_available);

    // Getters
    int getRoomNumber() const;
    double getRoomSize() const;
    std::string getFloorType() const;
    bool isAvailable() const;

    // Setters
    void setRoomNumber(int room_number);
    void setRoomSize(double room_size);
    void setFloorType(const std::string& floor_type);
    void setAvailability(bool is_available);
};

#endif // ROOM_HPP
