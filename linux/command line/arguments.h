#include <string>
#include <vector>
#include <iostream>
#define vector std::vector
#define string std::string
#define cout std::cout
#define _ver_ "Revamp 1.0"

string help_string = "Usage: revamp [OPTIONS]... [arg1]... [arg2]\n\
A utility to move file or folders from arg1 to arg2 without requiring to change the links and references.\n\
\n\
-nd                          do not delete the destination file/folder\n\
-f,                          do not prompt before overwriting\n\
-i,                          prompt before overwrite (default)\n\
-no,                         do not overwrite an existing file\n\n\
If more than one of -i, -f, -no is specified, only the final option is accepted.\n\n\
-t,                          move file/folder at arg1 into arg2(arg2 must be a directory).\n\
\n\
\n\
-h                            display this help.\n\
-version                      output version information\n\n\
If no options are provided, the revamp command line is opened.";

struct args
{
    bool keep_file = false, overwrite = true, prompt_overwrite = true;
    bool move_into = false;
    string source, destination;
} * p_ar;

void handle_args(int narg, char *arg[])
{
    vector<string> arr;
    for (int i = 1; i < narg; i++)
        arr.push_back(string(arg[i]));
    int i = 0;
    while (i < arr.size())
    {
        if (arr[i] == "-nd")
            p_ar->keep_file = true;
        else if (arr[i] == "-f")
            p_ar->prompt_overwrite = false;
        else if (arr[i] == "-no")
            p_ar->overwrite = false;
        else if (arr[i] == "-i")
            p_ar->prompt_overwrite = true;
        else if (arr[i] == "-t")
            p_ar->move_into = true;
        else if (arr[i] == "-h")
        {
            cout << help_string;
            return;
        }
        else if (arr[i] == "-version")
        {
            cout << _ver_ << "\n";
            return;
        }
        else if (arr[i].at(0) == '-')
        {
            cout << "inavlid option \'" << arr[i] << "\'\n";
            cout << "Try \'revamp -h\' for help on revamp.\n";
            return;
        }
        else
        {
            try
            {
                p_ar->source = arr[i];
                p_ar->destination = arr.at(i + 1);
            }
            catch (std::out_of_range err)
            {
                cout << "missing operand addresses\n";
                cout << "Try \'revamp -h\' for help on revamp.\n";
            }
        }
    }
}
