#ifndef URL_H
#define URL_H

#include <string>
class Url
{
private:
public:
    std::string value;
    explicit Url(std::string value_);
    bool operator==(const Url& other) const;

    std::string toStdString()
    {
        return value;
    }


};
#endif
