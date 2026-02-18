#ifndef EVENT_H
#define EVENT_H

#include "HandlerId.h"
#include <unordered_map>
#include <functional>

template <typename T>
class Event;

template <typename T>
class Subscription
{
private:
    Event<T> *_event;
    HandlerId _handlerId;
public:
    Subscription(Event<T>& event, HandlerId id)
        : _event(&event), _handlerId(id)
    {}
    // запрет копирования
    Subscription(Subscription& other) = delete;

    // конструктор копирования
    Subscription(Subscription &&other) : _event(other._event), _handlerId(other._handlerId)
    {
        other._event = nullptr;
    }

    ~Subscription()
    {
        if (_event != nullptr)
        {
            _event->unsubscribe(_handlerId);
        }
    }
};



template <typename T>
class Event
{
    // тип обработчика события
    using Handler = std::function<void(T&)>;
private:
    unsigned int _nextHandlerId = 0;
    std::unordered_map<HandlerId, Handler> _handlers;
public:
    Subscription<T> subscribe(Handler h)
    {
        // сохраняем копию фукнции
        _handlers.emplace(_nextHandlerId, std::move(h));
        return Subscription(*this, _nextHandlerId++);
    }

    void unsubscribe(HandlerId id)
    {
        auto it = std::find_if(_handlers.begin(), _handlers.end(), 
            [id](auto& pair){
                return pair.first == id;
            });
        if (it != _handlers.end())
        {
            _handlers.erase(it);
        }
    }

    
    void emit(T& data)
    {
        for (auto hndl : _handlers)
        {
            hndl.second(data);
        }
    }

};
#endif
