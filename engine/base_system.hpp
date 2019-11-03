#pragma once
#include <vector>
#include <unordered_map>
#include "entity.hpp"
#include "message_handler.hpp"

/**
 * Every component type need a system, each system is resposible for
 * keeping track of components of each type. 
 */

class scene;

template <typename T>
class base_system : public message_handler {
protected:
    std::vector<T> m_component_array;
    std::vector<size_t> m_free_list;
    std::unordered_map<entity_id, size_t> m_component_map;

    scene* parent_scene;
public:
    base_system(scene* parent_scene, message_system* ms) :
        message_handler(ms), parent_scene(parent_scene) {}
    virtual ~base_system() {}
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    
    bool add_component(entity_id id) {        
        if (m_component_map.find(id) != m_component_map.end())
            return false;
        if (!m_free_list.empty()) {
            size_t idx = m_free_list[0];
            m_free_list.erase(m_free_list.begin());
            m_component_array[idx] = T(-1);
            m_component_map[id] = idx;
            return true;
        }
        m_component_map[id] = m_component_array.size();
        m_component_array.emplace_back(id);
        return true;
    }
    
    bool has_component(entity_id id) {
        return m_component_map.find(id) != m_component_map.end();
    }
    void remove_component(entity_id id) {
        size_t idx = m_component_map[id];
        m_free_list.push_back(idx);
        m_component_map.erase(id);
    }
    T& get_component(entity_id id) {
        return m_component_array[m_component_map[id]];
    }
    std::vector<T>& get_components() {
        return m_component_array;
    }
};
