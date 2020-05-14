//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_ECS_H
#define TEMPGAMEMOTOR_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include <nlohmann/json.hpp>

class Component;
class Entity;
class Manager;

constexpr std::size_t max_components    = 32;
constexpr std::size_t max_groups        = 32;

using json = nlohmann::json;

namespace ComponentHelper{

    typedef struct {
        std::function<Component*()> creator;
    } ComponentBlock;
    typedef  unsigned int  ComponentType;

    typedef std::map<std::string, ComponentType > map_sct;
    typedef std::map<ComponentType, ComponentBlock> map_type;
    extern map_type ComponentMap;
    extern map_sct ComponentMapSCT;

};

class Component{
public:
    Entity* entity = nullptr;

    virtual void init(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void set_data(json *data){};

    virtual ~Component() = default;
};

class Entity{
private :
    Manager& manager;
    bool active = true;
    std::vector<Component* > components;

    std::map<ComponentHelper::ComponentType, Component*> component_array;
    std::bitset<max_components> component_bitset;
    std::bitset<max_groups> group_bitset;
public:

    Entity(Manager& manager_t) : manager(manager_t){}
    void update(){
        for(auto& c : components) c->update();
    };

    void draw(){
        for(auto& c : components) c->draw();
    }

    bool is_active(){return active;};
    void destroy(){active = false;};

    bool has_group(std::size_t group_t){
        return group_bitset[group_t];
    }

    void add_group(std::size_t group_t);
    void del_group(std::size_t group_t){
        group_bitset[group_t] = false;
    }

    bool has_component(ComponentHelper::ComponentType c_type) const{
        return component_bitset[c_type];
    }

    Component* add_component(ComponentHelper::ComponentType c_type, json *args){
        Component* c;
        if(!has_component(c_type)){
            c = ComponentHelper::ComponentMap[c_type].creator();

            c->entity = this;
            components.push_back(c);

            component_array[c_type] = c;
            component_bitset[c_type] = true;

            c->init();
        }else
            c = component_array[c_type];

        c->set_data(args);
        return c;
    }
    Component* add_component(ComponentHelper::ComponentType c_type){
        if(has_component(c_type)) return get_component(c_type);
        return add_component(c_type, new json("{}"));
    }

    Component* get_component(ComponentHelper::ComponentType c_type){
        Component* ptr = component_array[c_type];
        return ptr;
    }
};

class Manager{
private:
    std::vector<std::unique_ptr<Entity> > entities;
    std::array<std::vector<Entity*>, max_groups > grouped_entities;
public:
    void update(){
        for(auto& e : entities) e->update();
    };
    void draw(){
        for(auto& e : entities) e->draw();
    };

    void refresh(){

        for(auto i(0u); i < max_groups; i++){
            auto& v(grouped_entities[i]);
            v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* entity_t){
                return !entity_t->is_active() || !entity_t->has_group(i);
            }), std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity> &mEntity){
            return !mEntity->is_active();
        }), std::end(entities));
    };

    void clear(){
        entities.clear();
        for(int i = 0; i < grouped_entities.size(); i++)
            grouped_entities[i].clear();
    }

    void add_group(Entity* entity, std::size_t group_t){
        grouped_entities[group_t].emplace_back(entity);
    }

    std::vector<Entity*>& get_group(std::size_t group_t){
        return grouped_entities[group_t];
    }

    Entity& add_entity(){
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};



#endif //TEMPGAMEMOTOR_ECS_H
