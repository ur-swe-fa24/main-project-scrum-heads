#ifndef MONGO_ADAPTER_HPP
#define MONGO_ADAPTER_HPP

#include "adapter.hpp"
#include <memory>
#include <utility>
#include <mongocxx/instance.hpp>

namespace loggable {
    //Cout_Adapter inherits from loggable.hpp
    class Mongo_Adapter : public Adapter{
        public:
            MongoAdapter() override;
            // Pass by const ref - protects original objects the parameters are the senor or actuator
            void write_robot( const robots::Robot& robot) override;
            void read_robot( const robots::Robot& robot) override;
            
        private:
            mongocxx::instance db {};

    };
}

#endif