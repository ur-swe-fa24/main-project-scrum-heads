#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include "robot.hpp"

// The data output interface that all MASC objects need!
class Adapter {
    public:
        virtual ~Adapter() = default;
        // Pass by const ref - protects original objects
        virtual void write_robot(const robots::Robots& robot) = 0;
        virtual void read_robot(int id) = 0;
        virtual void read_all_robots() = 0;
        virtual void delete_robot(int id) = 0;
        virtual void delete_all_robots() = 0;
        virtual void update_robot(int id, int water_level, int battery_level) = 0;
};

#endif // ADAPTER_HPP