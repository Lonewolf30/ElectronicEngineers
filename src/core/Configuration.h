#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

#ifndef ELECTRONICENGINEERS_CONFIGURATION_H
#define ELECTRONICENGINEERS_CONFIGURATION_H

using namespace std;

class Configuration {
public:
	explicit Configuration(const char* fileName);
	void LoadConfigurations();
	bool HasConfigurationChanged();
	void SaveConfigurations();

	string GetConfiguration(const string& configName, string defaultValue);
	void SetConfiguration(const string& configName, const string& configValue);

private:
	string dataFolder;
	string configurationFileName;

	bool configurationChanged;

	map<string, string> configurations;
};


#endif