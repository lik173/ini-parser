#include <iostream>
#include <fstream>
#include <string>
#include <map>

//-----------------
#define FILENAME "settings.ini"
//-----------------

/*
This is a simple ini parser.

Look at the end. You will find 'cout << "Something: " << ini_data["section.variable"];', where
section is '[section]' and variable is 'variable = value'

Example ini file:

    ; This is a comment
    [database]
    name = my_database
    user = admin
    password = secret
    [server]
    address = localhost
    port = 8080


*/





using namespace std;

map<string, string> parse_ini_file(const string& file_path) {
    map<string, string> ini_data;
    ifstream ini_file(file_path);
    if (ini_file.is_open()) {
        string line;
        string current_section;
        while (getline(ini_file, line)) {
            // Check for section header
            if (line.size() > 2 && line.front() == '[' && line.back() == ']') {
                current_section = line.substr(1, line.size() - 2);
                continue;
            }
            // Check for key-value pair
            size_t eq_pos = line.find('=');
            if (eq_pos != string::npos) {
                string key = line.substr(0, eq_pos);
                string value = line.substr(eq_pos + 1);
                // Strip leading/trailing whitespace from key and value
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                // Add key-value pair to map
                string full_key = current_section.empty() ? key : current_section + "." + key;
                ini_data[full_key] = value;
            }
        }
        ini_file.close();
    }
    return ini_data;
}

int main() {
    // Parse INI file
    map<string, string> ini_data = parse_ini_file(FILENAME);
    // Print some values
    cout << "Database name: " << ini_data["database.name"] << endl;
    cout << "Server address: " << ini_data["server.address"] << endl;
    cout << "Server port: " << ini_data["server.port"] << endl;
    return 0;
}