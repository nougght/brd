#ifndef TAB_ID_H
#define TAB_ID_H

// browser tab id
struct TabId
{
    unsigned int value;
    explicit TabId(unsigned int value_);
    TabId(TabId &other);
    bool operator==(const TabId& other) const;
};

#endif
