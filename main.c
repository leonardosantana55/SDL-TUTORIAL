// compile: 'gcc main.c input.c init.c draw.c -o prog -lSDL2'

#include "main.h"

void animateBullet(Bullet *bullet);
    
App app;
int WinMain(int argc, char *argv[]){
    SDL_Rect r1; r1.h = 50; r1.w = 50; r1.x = 50; r1.y = 50;
    Bullet bullet; bullet.form.h = 10; bullet.form.w = 30; bullet.form.x = r1.x; bullet.form.y = r1.y; bullet.dx = 2; bullet.dy = 0; bullet.distance = 150;
    
    initSDL(); // create window

    while (1){
        prepareScene();
        doInput();
        drawRectangle(&r1);
        drawBullet(&bullet.form);
        
        printf("%d ,%d ,%d ,%d", app.down, app.up, app.left, app.rigth);
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
            drawBullet(&bullet.form);
            animateBullet(&bullet);

        }
        
        //animateBullet(&bullet);
        presentScene();
        SDL_Delay(16);
    }

return 0;

}

void animateBullet(Bullet *bullet){
    if (bullet->distance > 0){
        bullet->form.x += bullet->dx;
        bullet->form.y += bullet->dy;
        bullet->distance--;
    }
}