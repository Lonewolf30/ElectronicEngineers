#include "Configuration.h"

Configuration::Configuration(const char* fileName)
{
	this->configurationFileName = fileName;

	configurations = map<string, string>();

	char* buffer;
	size_t size;

	_dupenv_s(&buffer, &size,"appdata");
	string data = buffer;
	data += "\\Electronic Engineering Simulator\\";
	dataFolder = data + "Settings\\";

	configurationChanged = false;
}

void Configuration::LoadConfigurations()
{
	int createdFolder = system(("mkdir \"" + dataFolder + "\"").c_str());
	if (createdFolder == 0)
	{
		configurationChanged = true;
		return;
	}

	fstream file(dataFolder + configurationFileName + ".conf", fstream::in);
	string fileContents;
	while (file >> fileContents)
	{
		uint32_t equalPos = fileContents.find('=');
		string key = fileContents.substr(0, equalPos);
		string value = fileContents.substr(++equalPos, fileContents.length() - equalPos);
		configurations.insert(pair<string, string>(key, value));
	}

	file.close();
}

bool Configuration::HasConfigurationChanged()
{
	return configurationChanged;
}

void Configuration::SaveConfigurations()
{
	ofstream file(dataFolder + configurationFileName + ".conf", fstream::out);
	string fileContents;
	for (pair<string, string> items : configurations)
	{
		fileContents = fileContents.append(items.first).append("=").append(items.second).append("\n");
	}

	file << fileContents;
	file.close();
}

string Configuration::GetConfiguration(const string& configName, string defaultValue)
{
	auto value = configurations.find(configName);
	if (value != configurations.end())
		return configurations[configName];

	configurationChanged = true;
	configurations.insert(pair<string, string>(configName, defaultValue));
	return defaultValue;
}

void Configuration::SetConfiguration(const string& configName, const string& configValue)
{
	configurationChanged = true;
	auto value = configurations.find(configName);
	if (value == configurations.end())
	{
		configurations.insert(pair<string, string>(configName, configValue));
		return;
	}

	configurations[configName] = configValue;
}
