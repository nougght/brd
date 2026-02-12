#include "Tab.h"


Tab::Tab(TabId id, Url url) : _id(id), _currentUrl(url)
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
    _history.addUrl(url);
    _currentUrl = _history.currentItem()->url;
}

void Tab::goBack()
{
    if (_history.canGoBack())
    {
        _history.goBack();
        _currentUrl = _history.currentItem()->url;
    }
}

void Tab::goForward()
{
    if (_history.canGoForward())
    {
        _history.goForward();
        _currentUrl = _history.currentItem()->url;
    }
}

void Tab::onTitleChanged(std::string &title)
{
    _history.updateCurrentTitle(title);
    _title = title;
}
