#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>
#include <vector>  // For std::vector
#include <utility>  // for std::pair

namespace robots {

class Robots {

public:
    // Constructor
    explicit Robots(int robot_id, std::string robotSize, int waterLevel, 
                    int batteryLevel, std::string errorStatus, std::string taskStatus, 
                    int taskRoom, std::string functionType, int task_percent)
        : robot_id_(robot_id), size_(robotSize), water_level_(waterLevel), battery_level_(batteryLevel),
          error_status_(errorStatus), task_status_(taskStatus), task_room_(taskRoom), 
          function_type_(functionType), task_percent_(task_percent){}

    // Getter functions
    int get_id() const { return robot_id_; }
    std::string get_size() const { return size_; }
    int get_water_level() const { return water_level_; }
    int get_battery_level() const { return battery_level_; }
    std::string get_error_status() const { return error_status_; }
    std::string get_task_status() const { return task_status_; }
    int get_task_room() const { return task_room_; }
    int get_task_percent() const { return task_percent_; }

    // Calculate how long the task takes in seconds
    int get_task_length() const;

    // Function for field engineers to view the robot's status
    void field_engineer_view_status() const;

    // Function to add a robot to a list
    void add_robot(std::vector<robots::Robots>& robot_list);

    // Declaration of the helper function outside the class
    std::string get_function_type() const { return function_type_};
    
    // Add these in the public section of the Robots class
    void update_battery_level(int new_level) { battery_level_ = new_level; }
    void update_water_level(int new_level) { water_level_ = new_level; }
    void update_error_status(std::string status) { error_status_ = status; }
    void update_task_status(std::string status) { task_status_ = status; }
    void update_task_percent(int new_percent) { task_percent_ = new_percent; }


private:
    int robot_id_;
    std::string size_;
    int water_level_;
    int battery_level_;
    std::string error_status_;
    std::string task_status_;
    int task_room_;
    std::string function_type_;
    int task_percent_;
};

}  // namespace robots

#endif // ROBOT_HPP
