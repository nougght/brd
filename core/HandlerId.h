#ifndef SUBSCRIPTION_ID_H
#define SUBSCRIPTION_ID_H


struct HandlerId
{
    unsigned int value;
    explicit HandlerId(unsigned int value_);
    bool operator==(const HandlerId& other) const;
};

#endif