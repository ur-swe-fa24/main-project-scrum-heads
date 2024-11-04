#include "DataManager.h"

DataManager::DataManager() : client{mongocxx::uri{}} {
    // Connection to MongoDB is initialized here
}

DataManager::~DataManager() {
    // Cleanup resources if needed
}

void DataManager::receiveDataFromGUI(const wxString& data) {
    // Convert data from GUI and run simulation
    auto jsonStr = std::string(data.mb_str());
    auto simulationResults = runSimulation(jsonStr);
    storeSimulationResults(simulationResults);
}

wxString DataManager::sendDataToGUI() {
    // Fetch simulation results and send them back to the GUI
    auto results = retrieveSimulationResults();
    return wxString(results);
}

std::string DataManager::runSimulation(const std::string& data) {
    // Assume Simulation::simulate takes JSON string and returns JSON string
    return simulation.simulate(data);
}

void DataManager::storeSimulationResults(const std::string& results) {
    // Store results in MongoDB
    auto collection = client["database_name"]["simulation_results"];
    auto document = convertToDocument(results);
    collection.insert_one(document.view());
}

std::string DataManager::retrieveSimulationResults() {
    // Retrieve results from MongoDB
    auto collection = client["database_name"]["simulation_results"];
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        return convertToJson(doc);  // Assuming we are interested in the latest document
    }
    return "{}";  // Return empty JSON if no results
}

bsoncxx::document::value DataManager::convertToDocument(const std::string& json) {
    return bsoncxx::from_json(json);
}

std::string DataManager::convertToJson(const bsoncxx::document::value& doc) {
    return bsoncxx::to_json(doc);
}