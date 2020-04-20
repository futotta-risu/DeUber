//
// Created by whiwho on 18/04/2020.
//

#ifndef GAME_MOTOR_COMPONENT_HELPER_T_H
#define GAME_MOTOR_COMPONENT_HELPER_T_H

#include "ECS/ECS.h"
#include "transform_component.h"
#include "sprite_component.h"
#include "collision_component.h"

using namespace ComponentHelper;

inline void add_new_component_meta(ComponentHelper::ComponentType comp_id, const std::string& comp_name, std::function<Component*()> creator){
    if(ComponentMap.count(comp_id)) return; // TODO Add Error
    ComponentMap[comp_id] = {std::move(creator)};
    ComponentMapSCT[comp_name] = comp_id;
}

inline void load_default_components(){
    add_new_component_meta(ComponentHelper::TRANSFORM,
            "transform",[]() -> TransformComponent* {return new TransformComponent;});
    add_new_component_meta(ComponentHelper::COLLISION,
            "collision", []() -> CollisionComponent* {return new CollisionComponent;});
    add_new_component_meta(ComponentHelper::SPRITE,
            "sprite", []() -> SpriteComponent* {return new SpriteComponent;});

}

#endif //GAME_MOTOR_COMPONENT_HELPER_T_H
