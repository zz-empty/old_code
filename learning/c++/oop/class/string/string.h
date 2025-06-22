#ifndef __STRING_H__
#define __STRING_H__

class String
{
public:
    String();
    String(const char *pstr);
    ~String();
    String(const String &rhs);
    String & operator=(const String &rhs);

    void print();
private:
    char *_pstr;
};

#endif
