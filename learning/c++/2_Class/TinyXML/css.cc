#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::regex_replace;

using namespace tinyxml2;

namespace wd
{

struct Record
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    void parseRss();
    void dump(const string &filename);
private:
    vector<Record> _dict;
};

void RssReader::parseRss()
{
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");
    if (doc.ErrorID())
    {
        cout << "open file error" << doc.ErrorID() << endl;
        return;
    }

    XMLElement *itemNode = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while (itemNode) {
        XMLElement *titleNode = itemNode->FirstChildElement("title");
        XMLElement *linkNode = itemNode->FirstChildElement("link");
        XMLElement *descriptionNode = itemNode->FirstChildElement("description");
        XMLElement *contentNode = itemNode->FirstChildElement("content:encoded");

        string title = titleNode->GetText();
        string link = linkNode->GetText();
        string description = descriptionNode->GetText();
        string content = contentNode->GetText();

        regex reg("<[^>]+>");

        description = regex_replace(description, reg, "");
        content = regex_replace(content, reg, "");

        cout << "title = " << title << endl;
        cout << "link = " << link << endl;
        cout << "description = " << description << endl;
        cout << "content = " << content << endl;

        _dict.push_back({title, link, description, content});
        
        itemNode = itemNode->NextSiblingElement();
    }
}

void RssReader::dump(const string &filename)
{
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "open " << filename << " error!" << endl;
        return;
    }

    for (size_t idx = 0; idx != _dict.size(); ++idx) {
        ofs << "<doc>" << endl
            << "<docid>" << idx + 1 << "</docid>" << endl
            << "<title>" << _dict[idx].title << "</title>" << endl
            << "<link>" << _dict[idx].link << "</link>" << endl
            << "<description>" << _dict[idx].description << "</description>" << endl
            << "<content>" << _dict[idx].content << "</content>" << endl
            << "</doc>" << endl;
    }

    ofs.close();
}

};


void test0()
{
    using namespace wd;

    RssReader rss;
    rss.parseRss();
    rss.dump("css.txt");
}

int main()
{
    test0();
    return 0;
}
