#include "adapters/mongo_adapter.hpp"
#include "robot.hpp"
#include <memory>
#include <utility>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

adapters::Mongo_Adapter::MongoAdapter(){
    mongo_instance {};
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
}

// Pass by const ref - protects original objects the parameters are the senor or actuator
void adapters::Mongo_Adapter::write_robot(const robots::Robot& robot){

}

void adapters::Mongo_Adapter::read_robot(const robots::Robot& robot){

}