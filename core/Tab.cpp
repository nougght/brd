#include "Tab.h"


Tab::Tab(TabId id, Url url) : _id(id), _url(url)
{
}

TabId Tab::getId()
{
    return _id;
}

bool Tab::canGoBack()
{
    return _history.canGoBack();
}

bool Tab::canGoForward()
{
    return _history.canGoForward();
}

void Tab::visitUrl(Url url)
{
    if(url == _url) return;

    _history.addUrl(url);
    _url = _history.currentItem()->url;
}

void Tab::goBack()
{
    if (_history.canGoBack())
    {
        _history.goBack();
        _url = _history.currentItem()->url;
    }
}

void Tab::goForward()
{
    if (_history.canGoForward())
    {
        _history.goForward();
        _url = _history.currentItem()->url;
    }
}

void Tab::changeTitle(std::string &title)
{
    _history.changeCurrentTitle(title);
    _title = title;
}


void Tab::changeUrl(Url url)
{
    _history.changeCurrentUrl(url);
    _url = url;
}
