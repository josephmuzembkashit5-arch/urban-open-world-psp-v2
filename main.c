#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <pspgum.h>
#include <math.h>

PSP_MODULE_INFO("UrbanOpenWorld", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define BUF_WIDTH 512
#define SCR_WIDTH 480
#define SCR_HEIGHT 272
#define LIST_SIZE 262144

static unsigned int __attribute__((aligned(16))) display_list[LIST_SIZE];

typedef struct {
    float x, y, z;
    unsigned int color;
} Vertex;

static Vertex floor_vertices[] = {
    {-40.0f, -1.0f, -40.0f, 0xFF55585C},
    { 40.0f, -1.0f, -40.0f, 0xFF55585C},
    {-40.0f, -1.0f,  40.0f, 0xFF55585C},
    { 40.0f, -1.0f,  40.0f, 0xFF55585C}
};

static Vertex player_vertices[] = {
    {-0.35f, 0.0f, 0.0f, 0xFF33AAFF},
    { 0.35f, 0.0f, 0.0f, 0xFF33AAFF},
    {-0.35f, 1.5f, 0.0f, 0xFF33AAFF},
    { 0.35f, 1.5f, 0.0f, 0xFF33AAFF}
};

static float player_x = 0.0f;
static float player_z = 0.0f;
static float camera_yaw = 0.0f;

static void draw_scene(void)
{
    sceGuStart(GU_DIRECT, display_list);
    sceGuClearColor(0xFF87B8E8);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    sceGuMatrixMode(GU_PROJECTION);
    sceGumLoadIdentity();
    sceGumPerspective(55.0f, 16.0f / 9.0f, 0.5f, 200.0f);

    sceGuMatrixMode(GU_VIEW);
    sceGumLoadIdentity();

    ScePspFVector3 camera = {
        player_x + sinf(camera_yaw) * 6.0f,
        3.0f,
        player_z + cosf(camera_yaw) * 6.0f
    };
    ScePspFVector3 target = { player_x, 0.7f, player_z };
    ScePspFVector3 up = { 0.0f, 1.0f, 0.0f };
    sceGumLookAt(&camera, &target, &up);

    sceGuMatrixMode(GU_MODEL);
    sceGumLoadIdentity();
    sceGumDrawArray(GU_TRIANGLE_STRIP,
        GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TRANSFORM_3D,
        4, 0, floor_vertices);

    sceGumPushMatrix();
    ScePspFVector3 translation = { player_x, 0.0f, player_z };
    sceGumTranslate(&translation);
    sceGumDrawArray(GU_TRIANGLE_STRIP,
        GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TRANSFORM_3D,
        4, 0, player_vertices);
    sceGumPopMatrix();

    sceGuFinish();
    sceGuSync(0, 0);
    sceGuSwapBuffers();
    sceDisplayWaitVblankStart();
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    SceCtrlData pad;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    sceGuInit();
    sceGuStart(GU_DIRECT, display_list);
    sceGuDrawBuffer(GU_PSM_8888, (void *)0, BUF_WIDTH);
    sceGuDispBuffer(SCR_WIDTH, SCR_HEIGHT,
        (void *)(BUF_WIDTH * SCR_HEIGHT * 4), BUF_WIDTH);
    sceGuDepthBuffer((void *)(BUF_WIDTH * SCR_HEIGHT * 8), BUF_WIDTH);
    sceGuOffset(2048 - (SCR_WIDTH / 2), 2048 - (SCR_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCR_WIDTH, SCR_HEIGHT);
    sceGuDepthRange(65535, 0);
    sceGuScissor(0, 0, SCR_WIDTH, SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuFrontFace(GU_CW);
    sceGuShadeModel(GU_SMOOTH);
    sceGuDisable(GU_TEXTURE_2D);
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    for (;;) {
        sceCtrlReadBufferPositive(&pad, 1);

        float move_x = ((float)pad.Lx - 128.0f) * 0.0008f;
        float move_y = ((float)pad.Ly - 128.0f) * 0.0008f;

        player_x += move_x;
        player_z += move_y;

        if (pad.Buttons & PSP_CTRL_LEFT) camera_yaw -= 0.035f;
        if (pad.Buttons & PSP_CTRL_RIGHT) camera_yaw += 0.035f;

        draw_scene();
    }

    return 0;
}
