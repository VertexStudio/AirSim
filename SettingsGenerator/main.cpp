#include <iostream>
#include <fstream>
#include "common/common_utils/FileSystem.hpp"
#include "common/common_utils/json.hpp"

using namespace std;
using namespace common_utils;
using json = nlohmann::json;

bool tryParse(std::string& input, int& output);

int main()
{
  json settings = {
    {"SettingsVersion", 1.2},
    {"SimMode", "Multirotor"},
    {"Vehicles", nullptr}
  };
  
  try
  {
    string config_root = FileSystem::combine(getenv("SIMBOTIC_ROOT"), "Config");
    string settings_root = FileSystem::combine(config_root, "AirSim");
    ofstream settings_file(FileSystem::combine(settings_root, "settings.json"));

    cout << "How many drones: ";
    string input;
    int drones;
    getline(cin, input);

    while (!tryParse(input, drones))
    {
        cout << "Error! Must be a number: ";
        getline(cin, input);
    }

    for(unsigned short int i = 0; i < drones; i++)
    {
      settings["Vehicles"]["Drone" + to_string(i)] = {
        {"VehicleType", "SimpleFlight"},
        {"X", i * 4},
        {"Y", 0},
        {"Z", -2},
      };
    }

    settings_file << settings.dump(1);
    
    cout << "settings.json successfully created!" << endl;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  return 0;
}

bool tryParse(std::string& input, int& output) {
    try{
        output = std::stoi(input);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}