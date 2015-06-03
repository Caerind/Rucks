#include "Settings.hpp"

Settings::Settings()
{
    if (!loadFromFile("Assets/Data/server.properties"))
    {
        createDefault();
        saveToFile("Assets/Data/server.properties");
    }
}

bool Settings::loadFromFile(std::string const& name)
{
    std::ifstream file(name);
    if (!file)
    {
        return false;
    }

    std::string line;
    while (std::getline(file,line))
    {
        if(line.size() > 0 && line[0] != '#')
        {
            size_t index = 0;
            while(std::isspace(line[index]))
                index++;
            const size_t beginKeyString = index;
            while(!std::isspace(line[index]) && line[index] != '=')
                index++;
            const std::string key = line.substr(beginKeyString, index - beginKeyString);
            while(std::isspace(line[index]) || line[index] == '=')
                index++;
            const std::string value = line.substr(index, line.size() - index);

            mSettings[key] = value;
        }
    }

    file.close();
    return true;
}

bool Settings::saveToFile(std::string const& name)
{
    std::ofstream file(name);
    if (!file)
    {
        return false;
    }

    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        file << itr->first << "=" << itr->second << std::endl;
    }

    file.close();
    return true;
}

void Settings::createDefault()
{
    mSettings["logfile"] = "Assets/Log/server.log";
    mSettings["maxplayers"] = ah::to_string(10);
    mSettings["port"] = ah::to_string(4567);
    mSettings["timeout"] = ah::to_string(3.f);
    mSettings["update"] = ah::to_string(1.f/60.f);
}

std::string Settings::getString(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return itr->second;
        }
    }
    return "";
}

int Settings::getInt(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            int a;
            if (ah::from_string(itr->second,a))
                return a;
        }
    }
    return 0;
}

float Settings::getFloat(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            float a;
            if (ah::from_string(itr->second,a))
                return a;
        }
    }
    return 0.f;
}

bool Settings::getBool(std::string const& id)
{
    for (auto itr = mSettings.begin(); itr != mSettings.end(); itr++)
    {
        if (itr->first == id)
        {
            return (itr->second == "true") ? true : false;
        }
    }
    return false;
}

void Settings::set(std::string const& id, std::string const& value)
{
    mSettings[id] = value;
}

void Settings::set(std::string const& id, int value)
{
    mSettings[id] = ah::to_string(value);
}

void Settings::set(std::string const& id, float value)
{
    mSettings[id] = ah::to_string(value);
}

void Settings::set(std::string const& id, bool value)
{
    mSettings[id] = (value) ? "true" : "false";
}
