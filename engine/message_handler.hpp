#pragma once

#include "messages.hpp"
class message_system;

class message_handler {
protected:
    message_system* m_message_system;
public:
    message_handler(message_system* ms);
    virtual void handle_message(msg_render& message);
    virtual void handle_message(msg_set_mesh& message);
    virtual void handle_message(msg_set_transform& message);
    virtual void handle_message(msg_get_transform& message);
    virtual void handle_message(msg_update_delta_transform& message);
    virtual void handle_message(msg_set_material& message);
    virtual void handle_message(msg_set_program& message);
    virtual void handle_message(msg_set_resolution& message);
};
