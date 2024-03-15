/* 
gcc main.c input.c init.c draw.c structs.c -o prog -lSDL2
 */
#include "main.h"

void animateBullet(Bullet *bullet);


//função createbullet
//a bala criada vai precisar ser desenhada. A função que desenha as balas tem que iterar pelo endereço que aponta pra elas e renderizar cada uma
//se a bala percorrer toda a distancia, ela fica com health 0
//se a bala está com health zero ela deve ser destruida

//function definitions
Bullet defineBullet(SDL_Rect *r1);
Bullet* createBullets(Bullet *bullet, SDL_Rect *r1);
LinkedList* createLinkedBullets(Bullet *bullet, SDL_Rect *r1);
void moveBullets(LinkedList *linkedlist_bullets);
void destroyBullets(Bullet *bullet);

    
App app;
int WinMain(int argc, char *argv[]){
    initSDL(); // create window
    
    SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;
    //Bullet *bullet;
    Bullet linkedbullet = defineBullet(&r1);
    LinkedList *linkedlist_bullets = createLinkedList(linkedbullet);
    //memset(bullet, 0, sizeof(Bullet));
    //printf("init %d\n",bullet->size);
    
    while (1){
        prepareScene();
        doInput();
        drawRectangle(&r1);
        drawAllBullets(linkedlist_bullets);
        //printf("size before %u\n", bullet->size);
        //printf("%d ,%d ,%d ,%d", app.down, app.up, app.left, app.rigth);
        if (app.down){
            r1.y += 1;
        }
        if (app.up){
            r1.y -= 1;
        }
        if (app.left){
            r1.x += 1;
        }
        if (app.rigth){
            r1.x -= 1;
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



/* 
void animateBullet(Bullet *bullet){
    if (bullet->distance > 0){
        bullet->form.x += bullet->dx;
        bullet->form.y += bullet->dy;
        bullet->distance--;
    }
}
 */


// PROVAVELMENTE VOU TER QUE IMPLEMENTAR ESSA PORA COMO LISTA LINKADA, MAS VAI COM REALLOC POR ENQUANTO HIHI
Bullet* createBullets(Bullet *bullet, SDL_Rect *r1){
        if (bullet->size == 0){
            bullet = (Bullet*)malloc(1 * sizeof(Bullet));
            bullet->size = _msize(bullet);

            bullet->form.h = 10;
            bullet->form.w = 30;
            bullet->form.x = r1->x;
            bullet->form.y = r1->y;

            bullet->distance = 100;
            bullet->dx = 1;
            bullet->dy = 0;
            bullet->health = 1;

            return bullet;
        }
        else{
            bullet = realloc(bullet, bullet->size + (1*sizeof(Bullet)));
            bullet->size = _msize(bullet);
            
            Bullet *temp_bullet = bullet;
                        
            return bullet;
        }

    //bullet->form.h = 10; bullet->form.w = 30; bullet->form.x = r1->x; bullet->form.y = r1->y; bullet->dx = 2; bullet->dy = 0; bullet->distance = 150;   
}

Bullet defineBullet(SDL_Rect *r1){
    Bullet bullet;
    bullet.form.h = 10;
    bullet.form.w = 30;
    bullet.form.x = r1->x;
    bullet.form.y = r1->y;

    bullet.distance = 100;
    bullet.dx = 1;
    bullet.dy = 0;
    bullet.health = 1;

    return bullet;

}


void moveBullets(LinkedList *linkedlist_bullets){
    Node* temp;
    temp = linkedlist_bullets->head;
    
    //int count = 0;
    while (temp != NULL){
        if (temp->bullet.distance > 0){
        temp->bullet.form.x += temp->bullet.dx;
        temp->bullet.form.y += temp->bullet.dy;
        temp->bullet.distance--;
        }
        
        temp = temp->next;
        //count++;
        //printf("quantidade %d\n",count);
    }
    
    return;

}


// Eu ja tenho a ação de alocar memoria, definir e linkar as balas
//Agora eu preciso animar elas
//desenhar elas
//destruir elas