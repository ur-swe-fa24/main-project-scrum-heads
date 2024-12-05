#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

class Room {
private:
    int room_number_;            // Room number
    std::string room_size_;      // Room size in a string format (e.g., "small")
    std::string floor_type_;     // Floor type (e.g., "Carpet", "Tile", "Wood")
    std::string availability_;   // Availability status (e.g., "Available", "Not Available")

public:
    // Constructor
    Room(int room_number, const std::string& room_size, const std::string& floor_type, const std::string& availability)
        : room_number_(room_number), room_size_(room_size), floor_type_(floor_type), availability_(availability) {}

    // Getters
    int getRoomNumber() const { return room_number_; }
    std::string getRoomSize() const { return room_size_; }
    std::string getFloorType() const { return floor_type_; }
    std::string getAvailability() const { return availability_; }

    // Setters
    void setRoomNumber(int room_number) { room_number_ = room_number; }
    void setRoomSize(const std::string& room_size) { room_size_ = room_size; }
    void setFloorType(const std::string& floor_type) { floor_type_ = floor_type; }
    void setAvailability(const std::string& availability) { availability_ = availability; }
};

#endif // ROOM_HPP
