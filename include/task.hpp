#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>  // For std::vector
#include <utility>  // for std::pair

namespace robots {

class Tasks {

public:
    // Constructor
    explicit Tasks(int task_id, int robot_id, int room_number, std::string errorStatus, std::string taskStatus, 
                    int taskRoom, std::string functionType, int location_x, 
                    int location_y)
        : robot_id_(robot_id), size_(robotSize), water_level_(waterLevel), battery_level_(batteryLevel),
          error_status_(errorStatus), task_status_(taskStatus), task_room_(taskRoom), 
          function_type_(functionType), location_x_(location_x), location_y_(location_y), 
          task_start_time_(start_time), task_end_time_(end_time) {}

    // Getter functions
    int get_id() const { return robot_id_; }
    std::string get_size() const { return size_; }
    int get_water_level() const { return water_level_; }
    int get_battery_level() const { return battery_level_; }
    std::string get_error_status() const { return error_status_; }
    std::string get_task_status() const { return task_status_; }
    int get_task_room() const { return task_room_; }
    int get_location_x() const { return location_x_; }
    int get_location_y() const { return location_y_; }

    // Calculate how long the task takes in seconds
    int get_task_length() const;

    // Function for field engineers to view the robot's status
    void field_engineer_view_status() const;

    // Function to add a robot to a list
    void add_robot(std::vector<robots::Robots>& robot_list);

    // Declaration of the helper function outside the class
    robots::Tasks::robotFunction get_function_type_from_input(const std::string& input);
    
    // Add these in the public section of the Robots class
    void update_battery_level(int new_level) { battery_level_ = new_level; }
    void update_water_level(int new_level) { water_level_ = new_level; }


private:
    int robot_id_;
    std::string size_;
    int water_level_;
    int battery_level_;
    std::string error_status_;
    std::string task_status_;
    int task_room_;
    std::string function_type_;
    int location_x_;
    int location_y_;
};

}  // namespace robots

#endif // ROBOT_HPP