#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include "robot.hpp"
#include <vector>

class Adapter {
    public:
        virtual ~Adapter() = default;
        // Pass by const ref - protects original objects
        // Robot table information
        virtual void write_robot(const robots::Robots& robot) = 0;
        virtual robots::Robots read_robot(int id) = 0;
        virtual std::vector<robots::Robots> read_all_robots() = 0;
        virtual std::string delete_robot(int id) = 0;
        virtual void delete_all_robots() = 0;
        virtual void update_robot(int id, int water_level, int battery_level) = 0;
        virtual std::vector<int> get_all_ids() = 0;

        // Task table functions
        virtual void write_task(robots::Robots new_task) = 0;
        virtual void write_task(int id, int room) = 0;
        virtual robots::Robots read_ongoing_task(int id) = 0;
        virtual std::vector<robots::Robots> read__all_ongoing_tasks() = 0;
        virtual std::vector<robots::Robots> read_robot_tasks(int id) = 0;
        virtual std::vector<robots::Robots> read_all_tasks() = 0;
        virtual void update_task_status(std::vector<robots::Robots> updates) = 0;
        // virtual std::string cancel_task(int id) = 0;
        virtual void delete_all_tasks() = 0;

        // Error Log stuff
        virtual std::string get_error_log(int id) = 0;

};

#endif // ADAPTER_HPP