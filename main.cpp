#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

vector<int> num;

void input(int x, int i)
{
    int p;
    if (i >= num.size() || num[i] == 0)
    {
        if (i >= num.size())
            num.push_back(x);
        else
            num[i] = x;
        return;
    }
    while (i < num.size() && num[i] != 0)
    {
        p = num[i];
        num[i] = x;
        x = p;
        i++;
    }
    if (i >= num.size())
        num.push_back(x);
    else
        num[i] = x;
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <avg_curv_path> <output_path> <file1.label> [<file2.label> ...]" << endl;
        return 1;
    }

    string avg_curv_path = argv[1];
    string output_path = argv[2];
    vector<string> files(argv + 3, argv + argc);

    //------------读取file
    for (const auto & filename : files)
    {
        ifstream file(filename);
        if (!file)
        {
            std::cout << "无法打开文件: " << filename << std::endl;
            return -1;
        }
        string line;
        getline(file, line);getline(file, line);
        while (getline(file, line))
        {
            istringstream iss(line);//iss读取每一行
            int x;
            iss >> x;//从iss中提取一个词送入word

            int i = 0;

            while (true)
            {
                if (i >= num.size() || num[i] == 0)
                {
                    if (i >= num.size())
                        num.push_back(x);
                    else
                        num[i] = x;
                    break;
                }
                if (num[i] > x)
                {
                    int k = i;
                    input(x, k);
                }
                if (num[i] == x)
                {
                    break;
                }
                i++;
            }
        }
        file.close();
    }

    if (num.empty())
    {
        return 1;
    }

    //-------------读取curv
    ifstream infile(avg_curv_path);
    if (!infile)
    {
        std::cout << "无法打开文件" << avg_curv_path << std::endl;
    }
    string line;
    int i = 0, j = 0;
    ofstream outfile(output_path);
    while (getline(infile, line))
    {
        istringstream iss(line);//iss读取每一行
        long double y;
        iss >> y;//从iss中提取一个词送入word
        if (j < num.size() && num[j] == i)
        {
            outfile << std::fixed << std::setprecision(15) << y << endl;
            j++;
        }
        i++;
    }
    outfile.close();

    return 0;
}