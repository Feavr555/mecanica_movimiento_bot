#include <stdio.h>
#include <iostream>
#include <SDL.h>

SDL_Window*window=NULL;
SDL_Renderer*renderer=NULL;
const int ANCHO=500;
const int ALTO=500;

void init(){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    window=SDL_CreateWindow("IA Basica",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,ANCHO,ALTO,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,0);
}
void cerrar(){
    SDL_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

class objeto{
    public:
    SDL_Rect rect;
    SDL_Color colo;
    objeto(int x,int y,int w,int h,SDL_Color c){
        rect.x=x;
        rect.y=y;
        rect.h=h;
        rect.w=w;
        colo=c;
    }
    void pintar(SDL_Renderer*renderer){
        SDL_SetRenderDrawColor(renderer,colo.r,colo.g,colo.b,colo.a);
        SDL_RenderFillRect(renderer,&rect);
    }
};

bool checkCollisionLeft(const objeto&enemy,const objeto&left) {
    return SDL_HasIntersection(&enemy.rect, &left.rect);
}
bool checkCollisionRight(const objeto&enemy,const objeto&right){
    return SDL_HasIntersection(&enemy.rect, &right.rect);
}
bool checkCollisionDown(const objeto&enemy,const objeto&down){
    return SDL_HasIntersection(&enemy.rect, &down.rect);
}
bool checkCollisionUp(const objeto&enemy,const objeto&up){
    return SDL_HasIntersection(&enemy.rect, &up.rect);
}

int main(int argc,char*argv[]){
    std::string direccion="right";
    int velocidad=2;
    int velocidadDiagonal=1;
    int numAle;
    init();
    bool correr=true;
    SDL_Event event;
    objeto enemy(200,200,50,50,{0,255,255,255});
    objeto left(0,0,50,500,{0,255,255,255});
    objeto right(450,0,50,500,{0,255,255,255});
    objeto down(0,450,500,50,{0,255,255,255});
    objeto up(0,0,500,50,{0,255,255,255});
    while(correr){
        if(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                correr=false;
            }
        }
        SDL_SetRenderDrawColor(renderer,0,200,200,200);
        SDL_RenderClear(renderer);
        enemy.pintar(renderer);
        left.pintar(renderer);
        right.pintar(renderer);
        down.pintar(renderer);
        up.pintar(renderer);
        SDL_RenderPresent(renderer);
        if(direccion=="right"){
            enemy.rect.x+=velocidad;
            SDL_Delay(1);
        }else if(direccion=="left"){
            enemy.rect.x-=velocidad;
            SDL_Delay(1);
        }else if(direccion=="up"){
            enemy.rect.y-=velocidad;
            SDL_Delay(1);
        }else if(direccion=="down"){
            enemy.rect.y+=velocidad;
            SDL_Delay(1);
        }else if(direccion=="left-up"){
            enemy.rect.x-=velocidadDiagonal;
            enemy.rect.y-=velocidadDiagonal;
            SDL_Delay(1);
        }else if(direccion=="left-down"){
            enemy.rect.x-=velocidadDiagonal;
            enemy.rect.y+=velocidadDiagonal;
            SDL_Delay(1);
        }else if(direccion=="right-up"){
            enemy.rect.x+=velocidadDiagonal;
            enemy.rect.y-=velocidadDiagonal;
            SDL_Delay(1);
        }else if(direccion=="right-down"){
            enemy.rect.x+=velocidadDiagonal;
            enemy.rect.y+=velocidadDiagonal;
            SDL_Delay(1);
        }
        if(checkCollisionRight(right,enemy)){
            numAle=rand()%5+1;
            printf("Colision detectada! %i\n",numAle);
            if(numAle==1){
                direccion="left";
            }
            if(numAle==2){
                direccion="left-down";
            }
            if(numAle==3){
                direccion="left-up";
            }
            if(numAle==4){
                enemy.rect.x-=1;
                direccion="up";
            }
            if(numAle==5){
                enemy.rect.x-=1;
                direccion="down";
            }
        }
        if(checkCollisionLeft(left,enemy)){
            numAle=rand()%5+1;
            printf("Colision detectada! %i\n",numAle);
            if(numAle==1){
                direccion="right";
            }
            if(numAle==2){
                direccion="right-down";
            }
            if(numAle==3){
                direccion="right-up";
            }
            if(numAle==4){
                enemy.rect.x+=1;
                direccion="up";
            }
            if(numAle==5){
                enemy.rect.x+=1;
                direccion="down";
            }
        }
        if(checkCollisionDown(down,enemy)){
            numAle=rand()%5+1;
            printf("Colision detectada! %i\n",numAle);
            if(numAle==1){
                direccion="up";
            }
            if(numAle==2){
                direccion="right-up";
            }
            if(numAle==3){
                direccion="left-up";
            }
            if(numAle==4){
                enemy.rect.y-=1;
                direccion="left";
            }
            if(numAle==5){
                enemy.rect.y-=1;
                direccion="right";
            }
        }
        if(checkCollisionUp(up,enemy)){
            numAle=rand()%5+1;
            printf("Colision detectada! %i\n",numAle);
            if(numAle==1){
                direccion="down";
            }
            if(numAle==2){
                direccion="left-down";
            }
            if(numAle==3){
                direccion="right-down";
            }
            if(numAle==4){
                enemy.rect.y+=1;
                direccion="right";
            }
            if(numAle==5){
                enemy.rect.y+=1;
                direccion="left";
            }
        }
    }
    cerrar();
    return 0;
}
