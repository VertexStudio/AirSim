#include <iostream>
#include <fstream>
#include <cmath>
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

  string config_root = FileSystem::combine(getenv("SIMBOTIC_ROOT"), "Config");
  string settings_root = FileSystem::combine(config_root, "AirSim");
  ofstream settings_file(FileSystem::combine(settings_root, "settings.json"));

  string input;
  int matrix_size = 5;
  int drones;

  cout << "How many drones: ";
  getline(cin, input);

  while (!tryParse(input, drones))
  {
    cout << "Error! Must be a number: ";
    getline(cin, input);
  }

  cout << "How many drones per lines (Default 5): ";
  getline(cin, input);

  if (!input.empty()) {
    while (!tryParse(input, matrix_size))
    {
      cout << "Error! Must be a number: ";
      getline(cin, input);
    }
  }

  const int lines = ceil(
    static_cast<double>(drones)/static_cast<double>(matrix_size)
  );
  
  unsigned short int drone_index = 0;
  for(unsigned short int i = 0; i < lines; i++)
  {
    for(unsigned short int j = 0; j < matrix_size; j++)
    {
      settings["Vehicles"]["Drone" + to_string(i) + to_string(j)] = {
        {"VehicleType", "SimpleFlight"},
        {"X", j * 4},
        {"Y", i * -4},
        {"Z", -2},
      };

      if (drone_index == drones -1) {
        break;
      }
      ++drone_index;
    }
  }
  
  try
  {
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