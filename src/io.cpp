#include "io.hpp"

#include <fstream>
#include <stdexcept>

using namespace std;

static string trim(const string& s) {
    const string spaces = " \t\r\n";

    size_t start = s.find_first_not_of(spaces);
    if (start == string::npos) {
        return "";
    }

    size_t end = s.find_last_not_of(spaces);
    return s.substr(start, end - start + 1);
}

map<string, mpz_class> read_values(const string& path) {
    map<string, mpz_class> values;

    ifstream file(path);
    if (!file) {
        throw runtime_error("cannot open file: " + path);
    }

    string line;
    while (getline(file, line)) {
        if (trim(line).empty()) {
            continue;
        }

        size_t eq = line.find('=');
        if (eq == string::npos) {
            throw runtime_error("no '=' in line: " + line);
        }

        string name = trim(line.substr(0, eq));
        string number = trim(line.substr(eq + 1));

        values[name] = mpz_class(number, 0);
    }

    return values;
}

BroadcastData read_broadcast(const string& path) {
    BroadcastData data;
    map<string, mpz_class> values = read_values(path);

    for (int i = 1; ; i++) {
        string c_key = "C" + to_string(i);
        string n_key = "N" + to_string(i);

        if (values.count(c_key) == 0 || values.count(n_key) == 0) {
            break;
        }

        data.c.push_back(values[c_key]);
        data.n.push_back(values[n_key]);
    }

    if (data.c.empty()) {
        throw runtime_error("no C/N pairs in file: " + path);
    }

    return data;
}

MitmData read_mitm(const string& path) {
    MitmData data;
    map<string, mpz_class> values = read_values(path);

    return data;
}