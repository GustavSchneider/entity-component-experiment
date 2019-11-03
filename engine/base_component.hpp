#pragma once

#include <memory>
#include "entity.hpp"

class base_component {
protected:
    bool m_valid = true;
    entity_id m_entity_id;
public:
    base_component(entity_id id);
    virtual void init();
    virtual void update(float dt);
    virtual ~base_component();
    virtual int get_entity_ptr();
    bool valid();
    void set_valid(bool b);
};
