#ifndef MONGO_ADAPTER_HPP
#define MONGO_ADAPTER_HPP

#include "adapter.hpp"
#include <memory>
#include <utility>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

namespace adapters {
    //Cout_Adapter inherits from loggable.hpp
    class Mongo_Adapter : public Adapter{
        public:
            Mongo_Adapter();
            // Pass by const ref - protects original objects the parameters are the senor or actuator
            void write_robot( const robots::Robots& robot) override;
            void read_robot( const robots::Robots& robot) override;
            void delete_robot( const robots::Robots& robot) override;
            
        private:
            mongocxx::instance mongo_instance_ {};
            mongocxx::uri uri_ {"mongodb://localhost:27017"};
            mongocxx::client client_ {uri_};
            mongocxx::v_noabi::database db_ {client_["mydb"]};

    };
}

#endif