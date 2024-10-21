#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>  // For std::vector
#include <utility>  // for std::pair

namespace robots {

class Robots {

public:
    enum class robotFunction { SCRUB, SHAMPOO, VACUUM };

    // Time start and end struct
    struct Start_Time {
        int start_hour;
        int start_minute;
        int start_second;
    };

    struct End_Time {
        int end_hour;
        int end_minute;
        int end_second;
    };

    // Constructor
    explicit Robots(int16_t robot_id, std::string robotSize, int16_t waterLevel, 
                    int16_t batteryLevel, std::string errorStatus, std::string taskStatus, 
                    int16_t taskRoom, robotFunction functionType, int16_t location_x, 
                    int16_t location_y, Start_Time start_time = {}, End_Time end_time = {})
        : robot_id_(robot_id), size_(robotSize), water_level_(waterLevel), battery_level_(batteryLevel),
          error_status_(errorStatus), task_status_(taskStatus), task_room_(taskRoom), 
          function_type_(functionType), location_x_(location_x), location_y_(location_y), 
          task_start_time_(start_time), task_end_time_(end_time) {}

    // Getter functions
    int16_t get_id() const { return robot_id_; }
    std::string get_size() const { return size_; }
    int16_t get_water_level() const { return water_level_; }
    int16_t get_battery_level() const { return battery_level_; }
    std::string get_error_status() const { return error_status_; }
    std::string get_task_status() const { return task_status_; }
    int16_t get_task_room() const { return task_room_; }

    // Function to return the function type as a string
    std::string get_function_type() const {
        switch (function_type_) {
            case robotFunction::SCRUB: return "scrub";
            case robotFunction::SHAMPOO: return "shampoo";
            case robotFunction::VACUUM: return "vacuum";
            default: return "unknown";
        }
    }

    int16_t get_location_x() const { return location_x_; }
    int16_t get_location_y() const { return location_y_; }

    // Get start and end times
    std::pair<Start_Time, End_Time> get_start_and_end_time() const {
        return std::make_pair(task_start_time_, task_end_time_);
    }

    // Calculate how long the task takes in seconds
    int get_task_length() const;

    // Function for field engineers to view the robot's status
    void field_engineer_view_status() const;

    // Function to add a robot to a list
    void add_robot(std::vector<robots::Robots>& robot_list);
    // Declaration of the helper function outside the class
    robots::Robots::robotFunction get_function_type_from_input(const std::string& input);


private:
    int16_t robot_id_;
    std::string size_;
    int16_t water_level_;
    int16_t battery_level_;
    std::string error_status_;
    std::string task_status_;
    int16_t task_room_;
    robotFunction function_type_;
    int16_t location_x_;
    int16_t location_y_;
    Start_Time task_start_time_;
    End_Time task_end_time_;
};

}  // namespace robots

#endif // ROBOT_HPP
