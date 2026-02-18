#ifndef URL_H
#define URL_H

#include <string>
class Url
{
private:
    std::string _value;
public:
    explicit Url(std::string value) : _value(value)
    {
    }

    std::string toStdString()
    {
        return _value;
    }

};
#endif