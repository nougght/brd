// #ifndef TAB_ID_H
// #define TAB_ID_H

// // browser tab id
// struct TabId
// {
//     unsigned int value;
//     TabId();
//     explicit TabId(unsigned int value_);
//     TabId(TabId &other);
//     TabId &operator=(const TabId &other);
//     operator size_t() const;
//     bool operator==(const TabId& other) const;
//     bool isValid();
// };

// namespace std {
// template <>
// struct hash<TabId> {
//     size_t operator()(const TabId& id) const {
//         // Просто конвертируем в size_t и используем стандартный хэш
//         return std::hash<size_t>{}(static_cast<size_t>(id));
//     }
// };
// }

// #endif
