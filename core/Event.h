#ifndef EVENT_H
#define EVENT_H

// #include "HandlerId.h"
#include "Identifier.h"
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>
#include <iostream>

// template <typename T>
// class Event;

// template <>
// class Event<void>;

// Базовый класс без шаблона
class ISubscription
{
public:
    virtual ~ISubscription() = default; // Виртуальный деструктор — это КРИТИЧЕСКИ важно
};

template <typename T>
class Subscription;

template <>
class Subscription<void>;

template <typename T>
class Event
{
    // тип обработчика события
    using Handler = std::function<void(const T &)>;

private:
    unsigned int _nextHandlerId = 0;
    std::unordered_map<HandlerId, Handler> _handlers;

public:
    Event()
    {
    }
    Event(const Event<T> &other) = delete;
    Event &operator=(const Event<T> &other) = delete;
    Subscription<T> subscribe(Handler h);

    void unsubscribe(HandlerId id);

    void invoke(const T &data);
    unsigned int handlersSize() const
    {
        return _handlers.size();
    }
};

template <>
class Event<void>
{
    // тип обработчика события
    using Handler = std::function<void()>;

private:
    unsigned int _nextHandlerId = 0;
    std::unordered_map<HandlerId, Handler> _handlers;

public:
    Subscription<void> subscribe(Handler h);

    void unsubscribe(HandlerId id);

    void invoke();
    unsigned int handlersSize() const
    {
        return _handlers.size();
    }
};

template <typename T>
class Subscription : public ISubscription
{
private:
    Event<T> *_event;
    HandlerId _handlerId;

public:
    Subscription(Event<T> &event, HandlerId id)
        : _event(&event), _handlerId(id)
    {
    }
    // запрет копирования
    Subscription(Subscription &other) = delete;

    // // конструктор перемещения
    Subscription(Subscription &&other) : _event(other._event), _handlerId(other._handlerId)
    {
        other._event = nullptr;
    }
    Subscription &operator=(Subscription &&other) noexcept
    {
        if (this != &other)
        {
            // Если в текущем объекте уже была подписка — отписываемся
            if (_event && _handlerId.isValid())
                _event->unsubscribe(_handlerId);

            _event = other._event;
            _handlerId = other._handlerId;

            // Снова обнуляем оригинал
            other._event = nullptr;
            other._handlerId = HandlerId();
        }
        return *this;
    }

    ~Subscription() override
    {
        if (_event != nullptr)
        {
            _event->unsubscribe(_handlerId);
        }
    }
};

template <>
class Subscription<void> : public ISubscription
{
private:
    Event<void> *_event;
    HandlerId _handlerId;

public:
    Subscription(Event<void> &event, HandlerId id)
        : _event(&event), _handlerId(id)
    {
    }
    // запрет копирования
    Subscription(Subscription &other);

    // конструктор перемещения
    Subscription(Subscription &&other) : _event(other._event), _handlerId(other._handlerId)
    {
        other._event = nullptr;
    }

    ~Subscription() override
    {
        if (_event != nullptr)
        {
            _event->unsubscribe(_handlerId);
        }
    }
};

template <typename T>
inline Subscription<T> Event<T>::subscribe(Handler h)
{
    // сохраняем копию фукнции
    _handlers.emplace(_nextHandlerId, std::move(h));
    std::cerr << '\n'
              << _handlers.size();
    return Subscription<T>(*this, HandlerId(_nextHandlerId++));
}

template <typename T>
inline void Event<T>::unsubscribe(HandlerId id)
{
    auto it = std::find_if(_handlers.begin(), _handlers.end(),
                           [id](auto &pair)
                           {
                               return pair.first == id;
                           });
    if (it != _handlers.end())
    {
        _handlers.erase(it);
    }
}

template <typename T>
inline void Event<T>::invoke(const T &data)
{
    std::cerr << '\n'
              << _handlers.size();
    for (auto hndl : _handlers)
    {
        hndl.second(data);
    }
}

inline Subscription<void> Event<void>::subscribe(Handler h)
{
    // сохраняем копию фукнции
    _handlers.emplace(_nextHandlerId, std::move(h));
    return Subscription<void>(*this, HandlerId(_nextHandlerId++));
}

inline void Event<void>::unsubscribe(HandlerId id)
{
    auto it = std::find_if(_handlers.begin(), _handlers.end(),
                           [id](auto &pair)
                           {
                               return pair.first == id;
                           });
    if (it != _handlers.end())
    {
        _handlers.erase(it);
    }
}

inline void Event<void>::invoke()
{
    for (auto hndl : _handlers)
    {
        hndl.second();
    }
}
#endif
