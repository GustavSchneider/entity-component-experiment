#include "message_handler.hpp"
#include "message_system.hpp"

message_handler::message_handler(message_system* ms) : m_message_system(ms) {}
void message_handler::handle_message(msg_render& message) {}
void message_handler::handle_message(msg_set_mesh& message) {}
void message_handler::handle_message(msg_set_transform& message) {}
void message_handler::handle_message(msg_get_transform& message) {}
void message_handler::handle_message(msg_update_delta_transform& message) {}
void message_handler::handle_message(msg_set_material& message) {}
void message_handler::handle_message(msg_set_program& message) {}
void message_handler::handle_message(msg_set_resolution& message) {}
