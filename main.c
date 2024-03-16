/* 
gcc main.c input.c init.c draw.c structs.c -o prog -lSDL2
 */
#include "main.h"

enum Direction{down, up, left, rigth};

//function definitions
Bullet defineBullet(SDL_Rect *r1);
LinkedList* createLinkedBullets(Bullet *bullet, SDL_Rect *r1);
void moveBullets(LinkedList *linkedlist_bullets);
void destroyBullets(Bullet *bullet);
bool colisionDetection(SDL_Rect *me, SDL_Rect *object, enum Direction direction); // não sei que tipo utilizar para direção. Talvez seja um enum
    
App app;
int WinMain(int argc, char *argv[]){
    initSDL(); // create window
    
    SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;
    SDL_Rect r2; r2.h = 50; r2.w = 50; r2.x = SCREEN_WIDTH/2; r2.y = SCREEN_HEIGHT/2;
    Bullet linkedbullet = defineBullet(&r1);
    LinkedList *linkedlist_bullets = createLinkedList(linkedbullet);
    
    while (1){
        prepareScene();
        doInput();
        drawRectangle(&r1);
        drawRectangle(&r2);
        drawAllBullets(linkedlist_bullets);
        //printf("size before %u\n", bullet->size);
        //printf("%d ,%d ,%d ,%d", app.down, app.up, app.left, app.rigth);
        if (app.down && !colisionDetection(&r1, &r2, down)){
            r1.y += PLAYER_SPEED;
        }
        if (app.up && !colisionDetection(&r1, &r2, up)){
            r1.y -= PLAYER_SPEED;
        }
        if (app.left && !colisionDetection(&r1, &r2, left)){
            r1.x -= PLAYER_SPEED;
        }
        if (app.rigth && !colisionDetection(&r1, &r2, rigth)){
            r1.x += PLAYER_SPEED;
        }
        if (app.fire){
            app.fire = 0;
            linkedbullet = defineBullet(&r1);
            insert_ll(linkedlist_bullets, linkedbullet);
            printf("r1x: \n[%d, %d], [%d, %d]\n[%d, %d], [%d, %d]\n",
            r1.x, r1.y,
            r1.x + r1.w, r1.y,
            r1.x, r1.y + r1.h,
            r1.x + r1.w, r1.y + r1.h);
            printf("r2x: \n[%d, %d], [%d, %d]\n[%d, %d], [%d, %d]\n",
            r2.x, r2.y,
            r2.x + r2.w, r2.y,
            r2.x, r2.y + r2.h,
            r2.x + r2.w, r2.y + r2.h
            );
            
/* //0, 10
//50, 10
//0, 60
//50, 60

            printf("r1x: %d, %d\n", r1.x, r1.x + r1.w);
            printf("r1y: %d, %d\n", r1.y, r1.y + r1.h);
            printf("r2x: %d, %d\n", r2.x, r2.x + r2.w);
            printf("r2y: %d, %d\n", r2.y, r2.y + r2.h);
 */            //bullet = createBullets(bullet, &r1);
            //printf("after %d\n",bullet->size);
        }

        moveBullets(linkedlist_bullets);
        
        //animateBullet(&bullet);
        presentScene();
        SDL_Delay(16);
    }

return 0;
}

Bullet defineBullet(SDL_Rect *r1){
    Bullet bullet;
    bullet.form.h = 10;
    bullet.form.w = 30;
    bullet.form.x = r1->x;
    bullet.form.y = r1->y;

    bullet.distance = 30;
    bullet.dx = 30;
    bullet.dy = 0;
    bullet.health = 1;

    return bullet;
}


void moveBullets(LinkedList *linkedlist_bullets){
    Node* temp;
    temp = linkedlist_bullets->head;
    
    while (temp != NULL){
        if (temp->bullet.distance > 0){
        temp->bullet.form.x += temp->bullet.dx;
        temp->bullet.form.y += temp->bullet.dy;
        temp->bullet.distance--;
        }
        
        temp = temp->next;
    }
    
    return;
}


//proximo passo é implementar detecção de colisão.
//primeiro devo implementar a detecção entre dois retangulos
//identificar a area onde ocupa
//depende do formato
//se for um quadrado, quatro pontos vão ser utilizados para calcular a area dele
//SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;
//r1 ocupa os valores entre x50 até x100
//r1 ocupa os valores entre y50 até y100
//re o resultado da posição de r2 + seu movimento for x95 e y55, colisão retorn positivo
//        if (app.down && !colision(&r1, &r2, direction)){
//            r1.y += PLAYER_SPEED;
//        }
//movment and colision detection are linked. When i try to move, i can only do it if there is no colision

bool colisionDetection(SDL_Rect *me, SDL_Rect *object, enum Direction direction){
    if (me->x < object->x + object->w &&
        me->x > object->x &&
        me->y < object->y + object->h &&
        me->y > object->y 
        ||
        me->x < object->x + object->w &&
        me->x > object->x &&
        me->y + me->h < object->y + object->h &&
        me->y + me->h > object->y
        ||
        me->x + me->w < object->x + object->w &&
        me->x + me->w > object->x &&
        me->y < object->y + object->h &&
        me->y > object->y
        ||
        me->x + me->w < object->x + object->w &&
        me->x + me->w > object->x &&
        me->y + me->h < object->y + object->h &&
        me->y + me->h > object->y){
            printf("colision detected\n");
            return 0;
        }
/*   
    if (direction = rigth){            
        if ((me->x + PLAYER_SPEED > object->x) && me->y){
            printf("x overlap rigth\n");
            //return 0;
        }
    }
    if (direction = left){            
        if ((me->x - PLAYER_SPEED) < (object->x + object->w)){
            printf("x overlap left\n");
            //return 0;
        }
    }
    if (direction = down){            
        if (me->y + PLAYER_SPEED > object->y){
            printf("y overlap down\n");
            //return 0;
        }
    }
    if (direction = up){            
        if (me->y + PLAYER_SPEED < (object->y + object->h)){
            printf("y overlap up\n");
            //return 0;
        }
    }
 */    
    return 0;
}