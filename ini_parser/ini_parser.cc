#include "ini_parser.h"


namespace qh
{
    INIParser::INIParser(){}
    INIParser::~INIParser(){}

    bool INIParser::Parse(const std::string& ini_file_path)
    {
        std::ifstream ifs(ini_file_path);
        if (ifs.is_open() == false)
        {
            std::cerr << "can not open file!" << std::endl;
            return false;
        }
        bool success = false;
        std::string section = "";
        while (!ifs.eof())
        {
            std::string line;
            std::getline(ifs, line);
            if (line.back() == '\r')
                line.pop_back();
            if (line.size() > 0)
            {
                if (line.front() == '[' && line.back() == ']')
                {
                    section = line.substr(1, line.size()-2);
                }
                else 
                {
                    size_t pos = line.find('=');
                    if (pos != std::string::npos)
                    {
                        std::string key = line.substr(0, pos);
                        std::string value = line.substr(pos + 1);
                        if (section != "")
                            section_key[section].insert(key);
                        key_value[key] = value;
                        success = true;
                    }
                }
            }
        }
        return success;
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
    {
        if (ini_data == NULL)
            return false;
        std::string str(ini_data, ini_data_len);
        size_t pos = 0;
        bool success = false;
        do
        {
            size_t start = pos;
            pos = str.find(line_seperator, start);
            std::string sub_str;
            if (pos == std::string::npos)
                sub_str = str.substr(start);
            else
                sub_str = str.substr(start, pos-start);
            if (sub_str.size() > 0)
            {
                size_t sep = sub_str.find(key_value_seperator);
                if (sep != std::string::npos)
                {
                    std::string key = sub_str.substr(0, sep);
                    std::string value = sub_str.substr(sep + key_value_seperator.size());
                    key_value[key] = value;
                    success = true;
                }
            }
        } while ((pos != std::string::npos) && (pos += line_seperator.size()));
        return success;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found)
    {
        if (key_value.find(key) != key_value.end())
        {
            if (found)  *found = true;
            return key_value[key];
        }
        else
        {
            if (found) *found = false;
            not_found = "";
            return not_found;
        }
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
        if (section_key.find(section) != section_key.end() && section_key[section].find(key) != section_key[section].end())
        {
            if (found) *found = true;
            return key_value[key];
        }
        else
        {
            if (found) *found = false;
            not_found = "";
            return not_found;
        }
    }
}
