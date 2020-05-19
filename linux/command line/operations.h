#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

// Main operations are written here.
// Copy, Delete, Search e.t.c
#include "arguments.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>

using namespace std;

bool copyFile(struct args *p_ar)
{
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
            cout << "Aborting!!";
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
    if (!dst.is_open())
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
}

bool is_directory(string name)
{
    struct stat te;
    if (stat(name.c_str(), &te) == 0)
        if (te.st_mode && S_IFDIR)
            return true;
    return false;
}

namespace flst = filesystem;

bool copyEntity(struct args *p_ar)
{
    string source = p_ar->source;
    string dest = p_ar->destination;
    string nLoc = dest;
    if (p_ar->move_into)
    {
        int i;
        for (i = source.size() - 1; i >= 0; i--)
            if (source.at(i) == '/')
                break;
        if (i == 0 && source.at(0) != '/')
            i--;
        nLoc += '/' + source.substr(i + 1, source.size() - i - 1);
    }
    dest = nLoc;
    p_ar->move_into = false;
    struct stat s;
    if (stat(source.c_str(), &s) == 0)
    {
        if (s.st_mode & S_IFDIR)
        {
            string command = "mkdir " + dest;
            system(command.c_str());
            for (auto &it : flst::directory_iterator(source))
            {
                string tempAdd = it.path();
                struct args *tptr;
                *tptr = *p_ar;
                tptr->move_into = true;
                tptr->source = tempAdd;
                tptr->destination = dest;
                copyEntity(tptr);
            }
        }
        else if (s.st_mode & S_IFREG)
            copyFile(p_ar);
        else
            return false;
    }
    else
        return false;
}

#endif