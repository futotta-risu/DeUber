//
// Created by whiwho on 15/03/2020.
//

#ifndef TEMPGAMEMOTOR_SPRITE_COMPONENT_H
#define TEMPGAMEMOTOR_SPRITE_COMPONENT_H

#include "transform_component.h"
#include "SDL.h"
#include "texture_manager.h"
#include "ECS/animation.h"

#include <map>
#include <iostream>
#include <renderer.h>

namespace ComponentHelper {
    extern ComponentHelper::ComponentType SPRITE;
}
class SpriteComponent : public Component{
private:

    bool animated = false;
    int animation_id = 0;
    int frames = 0;
    int speed = 1;

    // Component Render
    int x_desp = 0, y_desp = 0;

    TransformComponent *transf = nullptr;
    SDL_Texture *tex = nullptr;
    SDL_Rect src = {0,0,32,32},dest={0,0,32,32};

    std::map<std::string, Animation> animations;
public:


    SpriteComponent() = default;

    ~SpriteComponent() override{
        SDL_DestroyTexture(tex);
    }


    void set_data(json *data) override{
        if(data->contains("animated")) animated = (*data)["animated"];
        else animated = false;
        std::string sprite_name = (*data)["sprite_name"];
        tex = GameRender::ast_man.get_texture(sprite_name);

        if(animated){
            animations = GameRender::ast_man.get_animation_map(sprite_name);
            play("stand");
        }
    }

    void init() override{
        if(!entity->has_component(ComponentHelper::TRANSFORM))
            entity->add_component(ComponentHelper::TRANSFORM);
        Component* cmp = entity->get_component(ComponentHelper::TRANSFORM);

        transf = dynamic_cast<TransformComponent*>(cmp);
        transf->scale = 1;

        src.x = src.y = 0;
        src.w = transf->width;
        src.h = transf->height;

        dest.x = static_cast<int>(transf->x());
        dest.y = static_cast<int>(transf->y());
        dest.w = dest.h = 50;
    }


    void update() override{
        if(animated)
            src.x = src.w* static_cast<int>((SDL_GetTicks() / speed) % frames);

        src.y = animation_id * transf->height;
        dest.x = x_desp+static_cast<int>(transf->x());
        dest.y = y_desp+static_cast<int>(transf->y());

        dest.w = static_cast<int>(transf->width*transf->scale);
        dest.h = static_cast<int>(transf->height*transf->scale);
    }

    void draw() override{
        TextureManager::draw(GameRender::ren, tex, src,dest);
    }

    void play(const char* anim_name){
        frames = animations[anim_name].frames;
        animation_id = animations[anim_name].index;
        speed = animations[anim_name].speed;
    }

    void set_place(int x, int y){
        x_desp = x;
        y_desp = y;
    }
};

#endif //TEMPGAMEMOTOR_SPRITE_COMPONENT_H
