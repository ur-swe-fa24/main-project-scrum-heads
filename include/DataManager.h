#pragma once

#include <wx/wx.h>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <bsoncxx/json.hpp>
#include "Simulation.hpp"  // Assume this is simulation class header

class DataManager {
public:
    DataManager();
    ~DataManager();

    void receiveDataFromGUI(const wxString& data);
    wxString sendDataToGUI();

private:
    mongocxx::instance instance{}; // MongoDB driver instance
    mongocxx::client client;       // MongoDB client
    Simulation simulation;         // Simulation object

    // Database interaction
    void storeSimulationResults(const std::string& results);
    std::string retrieveSimulationResults();

    // Simulation interaction
    std::string runSimulation(const std::string& data);

    // Utility functions
    bsoncxx::document::value convertToDocument(const std::string& json);
    std::string convertToJson(const bsoncxx::document::value& doc);
};