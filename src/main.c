#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vitaGL.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>

#define SCREEN_W 960
#define SCREEN_H 544

typedef struct {
    float x, y, z;
    float rot_y;
    int is_attacking;
} Player;

void draw_cube(float x, float y, float z, float sx, float sy, float sz, uint32_t color) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f,  1.0f); glVertex3f( 1.0f, -1.0f,  1.0f); glVertex3f( 1.0f,  1.0f,  1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}

int main(int argc, char *argv[]) {
    vglInit(0x800000);
    glViewport(0, 0, SCREEN_W, SCREEN_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)SCREEN_W / (float)SCREEN_H, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    SceCtrlData pad;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    Player kratos = {0.0f, 0.0f, -5.0f, 0.0f, 0};

    while (1) {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        if (pad.buttons & SCE_CTRL_START) break;

        float lx = (pad.lx - 128) / 128.0f;
        float ly = (pad.ly - 128) / 128.0f;
        if (fabsf(lx) > 0.2f) kratos.x += lx * 0.1f;
        if (fabsf(ly) > 0.2f) kratos.z -= ly * 0.1f;
        kratos.is_attacking = (pad.buttons & SCE_CTRL_SQUARE) ? 1 : 0;

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(kratos.x, kratos.y + 3.0f, kratos.z + 6.0f, kratos.x, kratos.y, kratos.z, 0.0f, 1.0f, 0.0f);
        draw_cube(kratos.x, kratos.y, kratos.z, 0.5f, 1.0f, 0.5f, 0xFF0000FF);

        if (kratos.is_attacking) {
            draw_cube(kratos.x + 1.2f, kratos.y, kratos.z - 0.5f, 0.8f, 0.1f, 0.1f, 0xFFFF0000);
            draw_cube(kratos.x - 1.2f, kratos.y, kratos.z - 0.5f, 0.8f, 0.1f, 0.1f, 0xFFFF0000);
        }
        vglSwapBuffers(GL_FALSE);
    }
    glEnd();
    sceKernelExitProcess(0);
    return 0;
}
