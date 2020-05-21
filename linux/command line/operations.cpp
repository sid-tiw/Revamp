#include <string>
#include <sys/stat.h>
#include <filesystem>
#include "operations.h"

namespace flst = std::filesystem;

bool is_directory(std::string name)
{
    struct stat te;
    if (stat(name.c_str(), &te) == 0)
        if (te.st_mode && S_IFDIR)
            return true;
    return false;
}

bool copyFile(args *p_ar)
{
    cout << p_ar->source << " " << p_ar->destination << "\n";
    string source = p_ar->source;
    string dest = p_ar->destination;
    fstream src(source, fstream::in | fstream::out);
    fstream temp(dest, fstream::in);
    if (!p_ar->overwrite && temp.is_open())
    {
        cout << "destination already exists. Aborting!\n";
        return true;
    }
    if (p_ar->prompt_overwrite)
    {
        char choice;
        cout << "destination already exists. Do you want to overwrite?(Y/n):";
        cin >> choice;
        if (choice == 'N' || choice == 'n')
        {
            cout << "Aborting!!\n";
            return true;
        }
        else if (choice == 'Y' || choice == 'y')
            ;
        else
            cout << "Bad input. Considering it as an yes.\n";
    }
    temp.close();
    fstream dst(dest, fstream::out);
    if (!src.is_open())
    {
        cout << "cannot locate \'" << source << "\': No such file or directory"
             << "\n";
        return false;
    }
    if (!dst.is_open() && !is_directory(dest))
    {
        cout << "cannot locate \'" << dest << "\': No such file or directory"
             << "\n";
        return false;
    }
    while (!src.eof())
    {
        char ch;
        src >> ch;
        dst << ch;
    }
    if (!p_ar->keep_file)
        remove(source.c_str());
    return true;
}

pair<string, string> split(string str)
{
    if (str.at(0) != '.' && str.at(0) != '/')
        str.insert(0, "./");
    if (str.at(str.size() - 1) == '/')
        str.erase(str.size() - 1);
    pair<string, string> val = make_pair("sid", "sid");
    int i;
    for (i = str.size() - 1; i >= 0; i--)
        if (str.at(i) == '/')
            break;
    if (i == 0 && str.at(0) != '/')
        i--;
    val.second = str.substr(i + 1, str.size() - i - 1);
    val.first = str.substr(0, i);
    return val;
}

void parse(char *str, string st)
{
    int i, c;
    for (i = 0, c = 0; i < st.size(); i++)
    {
        if (st.at(0) == '.' && st.at(1) == '/')
        {
            if (i != 0 && i != 1)
            {
                str[c] = st.at(i);
                c++;
            }
        }
        else
        {
            str[c] = st.at(i);
            c++;
        }
    }
    str[c] = '\0';
}

bool copyEntity(args *p_ar)
{
    string source = p_ar->source;
    string dest = p_ar->destination;
    if (p_ar->move_into)
        dest += '/' + split(source).second;
    p_ar->move_into = false;
    p_ar->destination = dest;
    struct stat s;
    if (stat(source.c_str(), &s) == 0)
    {
        if (s.st_mode & S_IFDIR)
        {
            if (!p_ar->overwrite)
            {
                cout << "destination folder already exists. Aborting!\n";
                return true;
            }
            if (p_ar->prompt_overwrite)
            {
                char choice;
                cout << "destination folder already exists. Do you want to overwrite?(Y/n):";
                cin >> choice;
                if (choice == 'N' || choice == 'n')
                {
                    cout << "Aborting!!\n";
                    return true;
                }
                else if (choice == 'Y' || choice == 'y')
                    ;
                else
                    cout << "Bad input. Considering it as an yes.\n";
            }
            flst::remove_all(dest);
            string command = "mkdir " + dest;
            system(command.c_str());
            for (auto &it : flst::directory_iterator(source))
            {
                string tempAdd = it.path();
                cout << tempAdd << "\n";
                args tptr;
                tptr = *p_ar;
                tptr.move_into = true;
                tptr.source = tempAdd;
                tptr.destination = dest;
                copyEntity(&tptr);
            }
            if (!p_ar->keep_file)
                flst::remove_all(source);
            return true;
        }
        else if (s.st_mode & S_IFREG)
            copyFile(p_ar);
        else
            return false;
    }
    return false;
}
