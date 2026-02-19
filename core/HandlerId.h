// #ifndef SUBSCRIPTION_ID_H
// #define SUBSCRIPTION_ID_H


// struct HandlerId
// {
//     unsigned int value;
//     explicit HandlerId(unsigned int value_);
//     operator size_t() const;
//     bool operator==(const HandlerId& other) const;
// };

// namespace std {
// template <>
// struct hash<HandlerId> {
//     size_t operator()(const HandlerId& id) const {
//         // Просто конвертируем в size_t и используем стандартный хэш
//         return std::hash<size_t>{}(static_cast<size_t>(id));
//     }
// };
// }

// #endif
