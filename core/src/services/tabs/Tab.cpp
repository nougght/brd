#include <core/Tab.h>

Tab::Tab(TabId id, Url url) : _id(id), _url(url)
{
}

TabId Tab::getId()
{
    return _id;
}

Url Tab::getUrl()
{
    return _url;
}

std::string Tab::getTitle()
{
    return _title;
}

bool Tab::isLoading()
{
    return _isLoading;
}

TabInfo Tab::toTabInfo()
{
    return {_id, _url, _title, _isLoading};
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
    if (url == _url)
        return;

    _history.addUrl(url);
    _url = _history.currentItem()->url;
}

void Tab::setLoading(bool isLoading)
{
    _isLoading = isLoading;
    loadingChanged.invoke(_isLoading);
}

void Tab::goBack()
{
    if (!canGoBack())
        return;
    _history.goBack();

    _url = _history.currentItem()->url;
    _title = _history.currentItem()->title;

    navigationCompleted.invoke(NavigationCompletedArgs{NavigationType::BackForward, toTabInfo()});
}

// void Tab::goBack()
// {
//     // сохраняем
//     bool lastCanGoBack = canGoBack();
//     bool lastCanGoForward = canGoForward();

//     if (lastCanGoBack)
//     {
//         _history.goBack();
//         _url = _history.currentItem()->url;
//         _title = _history.currentItem()->title;
//         wentBack.invoke(toTabInfo());
//         if(canGoBack() != lastCanGoBack)
//         {
//             canGoBackChanged.invoke(canGoBack());
//         }
//         if(canGoForward() != lastCanGoForward)
//         {
//             canGoForwardChanged.invoke();
//         }
//     }
// }

void Tab::goForward()
{
    if (!canGoForward())
        return;

    _history.goForward();
    _url = _history.currentItem()->url;
    _title = _history.currentItem()->title;

    navigationCompleted.invoke(NavigationCompletedArgs{NavigationType::BackForward, toTabInfo()});
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
