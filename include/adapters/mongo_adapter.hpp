#ifndef MONGO_ADAPTER_HPP
#define MONGO_ADAPTER_HPP

#include "adapter.hpp"
#include <memory>
#include <utility>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <vector>

namespace adapters {
    //Mongo_Adapter inherits from adapter.hpp
    class Mongo_Adapter : public Adapter{
        public:
            Mongo_Adapter();
            // Pass by const ref - protects original objects the parameters are the senor or actuator
            void write_robot( const robots::Robots& robot) override;
            robots::Robots read_robot(int id) override;
            void read_all_robots() override;
            std::string delete_robot(int id) override;
            void delete_all_robots() override;
            void update_robot(int id, int water_level, int battery_level) override;
            std::vector<int> get_all_ids() override;
            
        private:
        // Database is created here so that db_ can be accessed throughout the class
            mongocxx::instance mongo_instance_ {};
            mongocxx::uri uri_ {"mongodb://localhost:27017"};
            mongocxx::client client_ {uri_};
            mongocxx::v_noabi::database db_ {client_["mydb"]};
    };
}

#endif