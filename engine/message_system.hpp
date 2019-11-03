#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <typeindex>

#include "messages.hpp"
#include "message_handler.hpp"

class message_system {
private:
    std::unordered_map<std::type_index, std::vector<message_handler*>>m_registered_handlers;
public:
    template <typename T>
    void register_handler(message_handler* handler) {
        m_registered_handlers[typeid(T)].push_back(handler);
    }

    template <typename T>
    void unregister_handler(message_handler* handler) {
        std::vector<message_handler*>& hv = m_registered_handlers[typeid(T)];        
        auto pos = find(hv.begin(), hv.end(), handler);
        hv.erase(pos);
    }

    template <typename T>
    void dispatch_message(T message) {
        for (message_handler* mh : m_registered_handlers[typeid(message)]) {
            mh->handle_message(message);
        }
    }
};
