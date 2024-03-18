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
int distanceBeforeColision(SDL_Rect *me, SDL_Rect *object, enum Direction direction);

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
        if (app.down){
            if (!colisionDetection(&r1, &r2, down)){
                r1.y += PLAYER_SPEED;
            }
            else{
                r1.y += distanceBeforeColision(&r1, &r2, down);
            }
        }
        if (app.up){
            if (!colisionDetection(&r1, &r2, up)){
                r1.y -= PLAYER_SPEED;
            }
            else{
                r1.y -= distanceBeforeColision(&r1, &r2, up);
            }
        }
        if (app.left){
            if (!colisionDetection(&r1, &r2, left)){
                r1.x -= PLAYER_SPEED;
            }
            else{
                r1.x -= distanceBeforeColision(&r1, &r2, left);
            }
        }
        if (app.rigth){
            if (!colisionDetection(&r1, &r2, rigth)){
                r1.x += PLAYER_SPEED;
            }
            else{
                r1.x += distanceBeforeColision(&r1, &r2, rigth);
            }
        }
        if (app.fire){
            app.fire = 0;
            linkedbullet = defineBullet(&r1);
            insert_ll(linkedlist_bullets, linkedbullet);
/*             printf("r1x: \n[%d, %d], [%d, %d]\n[%d, %d], [%d, %d]\n",
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
 */            
        }

        moveBullets(linkedlist_bullets);
        
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

bool colisionDetection(SDL_Rect *me, SDL_Rect *object, enum Direction direction){
    //printf("the func received: %d\n", direction);
    if (direction == rigth){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w + PLAYER_SPEED < object->x + object->w && // superior direito
            me->x + me->w + PLAYER_SPEED > object->x &&
            me->y + PLAYER_SPEED <= object->y + object->h &&
            me->y + PLAYER_SPEED >= object->y
            ||
            me->x < object->x + object->w && // inferior esquerdo
            me->x > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y
            ||
            me->x + me->w + PLAYER_SPEED < object->x + object->w && // inferior direito
            me->x + me->w + PLAYER_SPEED > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                printf("colision detected rigth\n");
                return 1;
            }
    }
    if (direction == left){
        if (me->x - PLAYER_SPEED < object->x + object->w && // superior esquerdo
            me->x - PLAYER_SPEED > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w < object->x + object->w && // superior direito
            me->x + me->w > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y
            ||
            me->x - PLAYER_SPEED < object->x + object->w && // inferior esquerdo
            me->x - PLAYER_SPEED > object->x &&
            me->y + me->h - PLAYER_SPEED <= object->y + object->h &&
            me->y + me->h - PLAYER_SPEED >= object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                printf("colision detected left\n");
                return 1;
            }
    }
    if (direction == down){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w < object->x + object->w && // superior direito
            me->x + me->w > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y
            ||
            me->x + PLAYER_SPEED <= object->x + object->w && // inferior esquerdo
            me->x + PLAYER_SPEED >= object->x &&
            me->y + me->h + PLAYER_SPEED < object->y + object->h &&
            me->y + me->h + PLAYER_SPEED > object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h + PLAYER_SPEED < object->y + object->h &&
            me->y + me->h + PLAYER_SPEED > object->y){
                printf("colision detected down. difference: %d\n", (object->y) - (me->y + me->h));
                return 1;
            }
    }
    if (direction == up){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y - PLAYER_SPEED < object->y + object->h &&
            me->y - PLAYER_SPEED > object->y 
            ||
            me->x + me->w - PLAYER_SPEED <= object->x + object->w && // superior direito
            me->x + me->w - PLAYER_SPEED >= object->x &&
            me->y - PLAYER_SPEED < object->y + object->h &&
            me->y - PLAYER_SPEED > object->y
            ||
            me->x < object->x + object->w && // inferior esquerdo
            me->x > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                printf("colision detected up\n");
                return 1;
            }

    }
    return 0;
}

int distanceBeforeColision(SDL_Rect *me, SDL_Rect *object, enum Direction direction){
    //printf("the func received: %d\n", direction);
    if (direction == rigth){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w + PLAYER_SPEED < object->x + object->w && // superior direito
            me->x + me->w + PLAYER_SPEED > object->x &&
            me->y + PLAYER_SPEED <= object->y + object->h &&
            me->y + PLAYER_SPEED >= object->y
            ||
            me->x < object->x + object->w && // inferior esquerdo
            me->x > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y
            ||
            me->x + me->w + PLAYER_SPEED < object->x + object->w && // inferior direito
            me->x + me->w + PLAYER_SPEED > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                return (object->x) - (me->x + me->w);
            }
    }
    if (direction == left){
        if (me->x - PLAYER_SPEED < object->x + object->w && // superior esquerdo
            me->x - PLAYER_SPEED > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w < object->x + object->w && // superior direito
            me->x + me->w > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y
            ||
            me->x - PLAYER_SPEED < object->x + object->w && // inferior esquerdo
            me->x - PLAYER_SPEED > object->x &&
            me->y + me->h - PLAYER_SPEED <= object->y + object->h &&
            me->y + me->h - PLAYER_SPEED >= object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                return (me->x) - (object->x + object->w);
            }
    }
    if (direction == down){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y 
            ||
            me->x + me->w < object->x + object->w && // superior direito
            me->x + me->w > object->x &&
            me->y < object->y + object->h &&
            me->y > object->y
            ||
            me->x + PLAYER_SPEED <= object->x + object->w && // inferior esquerdo
            me->x + PLAYER_SPEED >= object->x &&
            me->y + me->h + PLAYER_SPEED < object->y + object->h &&
            me->y + me->h + PLAYER_SPEED > object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h + PLAYER_SPEED < object->y + object->h &&
            me->y + me->h + PLAYER_SPEED > object->y){
                return (object->y) - (me->y + me->h);
            }
    }
    if (direction == up){
        if (me->x < object->x + object->w && // superior esquerdo
            me->x > object->x &&
            me->y - PLAYER_SPEED < object->y + object->h &&
            me->y - PLAYER_SPEED > object->y 
            ||
            me->x + me->w - PLAYER_SPEED <= object->x + object->w && // superior direito
            me->x + me->w - PLAYER_SPEED >= object->x &&
            me->y - PLAYER_SPEED < object->y + object->h &&
            me->y - PLAYER_SPEED > object->y
            ||
            me->x < object->x + object->w && // inferior esquerdo
            me->x > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y
            ||
            me->x + me->w < object->x + object->w && // inferior direito
            me->x + me->w > object->x &&
            me->y + me->h < object->y + object->h &&
            me->y + me->h > object->y){
                return (me->y) - (object->y + object->h);
            }

    }
    return 0;
}