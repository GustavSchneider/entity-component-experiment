#include "base_component.hpp"

base_component::base_component(entity_id id) : m_entity_id(id) {}
base_component::~base_component() {}
void base_component::init() {}
void base_component::update(float dt) {}
int base_component::get_entity_ptr() { return m_entity_id; }
bool base_component::valid() { return m_valid; }
void base_component::set_valid(bool b) { m_valid = b; }
