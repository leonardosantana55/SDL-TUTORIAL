/* 
gcc main.c input.c init.c draw.c structs.c -o prog -lSDL2
 */
#include "main.h"

//function definitions
Bullet defineBullet(SDL_Rect *r1);
LinkedList* createLinkedBullets(Bullet *bullet, SDL_Rect *r1);
void moveBullets(LinkedList *linkedlist_bullets);
void destroyBullets(Bullet *bullet);
bool colisionDetection(SDL_Rect *active, SDL_Rect *passive, int direction); // não sei que tipo utilizar para direção. Talvez seja um enum
    
App app;
int WinMain(int argc, char *argv[]){
    initSDL(); // create window
    
    SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;
    SDL_Rect r2; r2.h = 50; r2.w = 50; r2.x = SCREEN_WIDTH - (50*2); r2.y = 50;
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
            r1.y += PLAYER_SPEED;
        }
        if (app.up){
            r1.y -= PLAYER_SPEED;
        }
        if (app.left){
            r1.x += PLAYER_SPEED;
        }
        if (app.rigth){
            r1.x -= PLAYER_SPEED;
        }
        if (app.fire){
            app.fire = 0;
            linkedbullet = defineBullet(&r1);
            insert_ll(linkedlist_bullets, linkedbullet);
            //bullet = createBullets(bullet, &r1);
            //printf("after %d\n",bullet->size);
        }

        print_ll(linkedlist_bullets);
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

