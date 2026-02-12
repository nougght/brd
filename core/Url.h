#ifndef URL_H
#define URL_H

#include <string>
class Url
{
private:
    std::string _url;
public:
    explicit Url(std::string url) : _url(url)
    {
    }


};
#endif