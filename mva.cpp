#include <iostream>
#include <string.h>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

string replaceString(string s, string what, string with)
{
    int index;
    while ((index = s.find(what)) != string::npos)
        s.replace(index, what.length(), with);

    return s;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("usage: mva src-dir dst-dir");
        return 1;
    }

    string _to = string(argv[2]) + "/";
    _to = replaceString(_to, "//", "/");

    for (auto& p : fs::directory_iterator(argv[1]))
    {
        try
        {
            if (fs::is_directory(p))
                continue;

            auto path = p.path();
            auto name = path.filename();
            auto to_name = _to + name.string();

            fs::rename(path, to_name);

            cout << path << " -> \"" << to_name << "\"" << endl;
        }
        catch (const std::exception& e)
        {
            cerr << e.what() << endl;
        }
    }

    return 0;
}