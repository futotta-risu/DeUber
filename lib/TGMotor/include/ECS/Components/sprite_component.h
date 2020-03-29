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

class SpriteComponent : public Component{
private:

    // Component Metadata

    // Component Values

    bool animated = false;
    int animation_id = 0;
    int frames = 0;
    int speed = 1;

    // Component Render
    int x_desp = 0, y_desp = 0;

    TransformComponent *transf;
    SDL_Texture *tex;
    SDL_Rect src,dest;
    Game* gApp;

public:

    std::map<std::string, Animation> animations;

    SpriteComponent() = default;

    SpriteComponent(const char* file_path, Game* gApp_t){
        gApp = gApp_t;
        set_tex(file_path);
    }

    SpriteComponent(std::string& sprite_name, Game* gApp_t, bool animated){
        gApp = gApp_t;
        animated = animated;

        if(animated){
            animations = gApp->ast_man.get_animation_map(sprite_name);
            play("stand");
        }
        tex = gApp->ast_man.get_texture(sprite_name);
    }

    ~SpriteComponent(){
        SDL_DestroyTexture(tex);
    }

    void set_tex(const char* file_path){
        tex = TextureManager::LoadTexture(gApp->ren, file_path);
    }

    void init() override{
        if(!entity->has_component<TransformComponent>())
            entity->add_component<TransformComponent>();
        transf = &entity->get_component<TransformComponent>();

        transf->scale = 1;

        src.x = src.y = 0;
        src.w = transf->width;
        src.h = transf->height;

        dest.x = x_desp+static_cast<int>(transf->x());
        dest.y = y_desp+static_cast<int>(transf->y());
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
        TextureManager::draw(gApp->ren, tex, src,dest);
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
