import sys, pygame
import OpenGL
from pygame.locals import *
from pygame.constants import *
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import pywavefront

# import pyassimp
# from pyassimp import *
# import assimp_py

# import collada
# from collada import Collada

BodyStructure = ['body', 'head', 'tail', 'FL_leg1', 'FL_leg2', 'FR_leg1', 'FR_leg2', 'BL_leg1', 'BL_leg2', 'BR_leg1', 'BR_leg2']
MoveChoice = ['False', 'Up', 'Down']
if_ani, if_control, if_move = False, False, False
ControlMap = {}

time = 0
ani_time = 0

rx, ry = (0,0)
tx, ty = (0,0)
zpos = 5
rotate = move = False

def ControlMapInit():
    global BodyStructure, ControlMap, MoveChoice
    for i in BodyStructure:
        ControlMap[i] = MoveChoice[0]
    # print(ControlMap)

# def scene_set(scene, size):
#     scene_box = (scene.vertices[0], scene.vertices[0])
#     for vertex in scene.vertices:
#         min_v = [min(scene_box[0][i], vertex[i]) for i in range(3)]
#         max_v = [max(scene_box[1][i], vertex[i]) for i in range(3)]
#         scene_box = (min_v, max_v)

#     scene_size     = [scene_box[1][i]-scene_box[0][i] for i in range(3)]
#     max_scene_size = max(scene_size)
#     scaled_size    = size

#     scene_scale    = [scaled_size/max_scene_size for i in range(3)]
#     scene_trans    = [-(scene_box[1][i] + scene_box[0][i])/2 for i in range(3)]
#     return scene_scale, scene_trans

scene = pywavefront.Wavefront('cube.obj', collect_faces=True)

def DrawCube(scale, trans, rotate):
    glPushMatrix()
    glTranslatef(trans[0]*2, trans[1]*2, trans[2]*2)
    glRotatef(rotate[0], rotate[1], rotate[2], rotate[3])
    glScalef(scale[0], scale[1], scale[2])

    for i, mesh in enumerate(scene.mesh_list):
        glBegin(GL_POLYGON)
        for face in mesh.faces:
            for vertex_i in face:
                glVertex3f(*scene.vertices[vertex_i])
        glEnd()
    glPopMatrix()

def DrawCubebyScale(scale):
    glPushMatrix()
    glScalef(scale[0], scale[1], scale[2])

    for i, mesh in enumerate(scene.mesh_list):
        glBegin(GL_POLYGON)
        for face in mesh.faces:
            for vertex_i in face:
                glVertex3f(*scene.vertices[vertex_i])
        glEnd()
    glPopMatrix()


def front_right_leg():
    global if_control, time, ani_time
    global ControlMap, MoveChoice
    glPushMatrix()

    # leg 1
    glPushMatrix()
    glTranslate(-3*2, -2.2*2, -1.6*2)

    glRotatef(ani_time%30, 0, 0, -1)

    if ControlMap['FR_leg1'] == MoveChoice[1]:
        glTranslate(0, 1.2, 0)
        glRotatef(time%360 * 3, 0, 0, -1)
        glTranslate(0, -1.2, 0)
    elif ControlMap['FR_leg1'] == MoveChoice[2]:
        glTranslate(0, 1.2, 0)
        glRotatef(time%360 * 3, 0, 0, 1)
        glTranslate(0, -1.2, 0)

    DrawCubebyScale((0.5, 1.4, 0.6))

    # leg 2
    glPushMatrix()
    glTranslate(-0.4*2, -0.5*2, 0)

    if ControlMap['FR_leg2'] == MoveChoice[1]:
        glTranslate(0, -0.2, 0)
        glRotatef(time%360 *3, 0, 0, -1)
        glTranslate(0, 0.2, 0)
    elif ControlMap['FR_leg2'] == MoveChoice[2]:
        glTranslate(0, -0.2, 0)
        glRotatef(time%360 *3, 0, 0, 1)
        glTranslate(0, 0.2, 0)

    DrawCubebyScale((0.3, 0.4, 0.6)) # leg 2
    glPopMatrix()
    glPopMatrix()
    glPopMatrix()

def front_left_leg():
    global ani_time
    glPushMatrix()

    glPushMatrix()
    glTranslate(-3*2, -2.2*2, 1.6*2)
    glRotatef(ani_time%30, 0, 0, -1)
    DrawCubebyScale((0.5, 1.4, 0.6))

    glPushMatrix()
    glTranslate(-0.4*2, -0.5*2, 0)
    DrawCubebyScale((0.3, 0.4, 0.6))
    glPopMatrix()
    glPopMatrix()
    glPopMatrix()


def back_right_leg():
    global ani_time
    glPushMatrix()

    glPushMatrix() # 8 3 4
    glTranslate(3*2, -2.2*2, -1.6*2)
    glRotatef(ani_time%30, 0, 0, 1)
    DrawCubebyScale((0.5, 1.4, 0.6))

    glPushMatrix()
    glTranslate(-0.4*2, -0.5*2, 0)
    DrawCubebyScale((0.3, 0.4, 0.6))
    glPopMatrix()
    glPopMatrix()
    glPopMatrix()

def back_left_leg():
    global ani_time
    glPushMatrix()

    glPushMatrix() # 8 3 4
    glTranslate(3*2, -2.2*2, 1.6*2)
    glRotatef(ani_time%30, 0, 0, 1)
    DrawCubebyScale((0.5, 1.4, 0.6))

    glPushMatrix()
    glTranslate(-0.4*2, -0.5*2, 0)
    DrawCubebyScale((0.3, 0.4, 0.6))
    glPopMatrix()
    glPopMatrix()
    glPopMatrix()


def hair():
    glPushMatrix()
    DrawCube((0.1, 1, 0.1), (-3.8, 2, 0), (30, 0, 0, 1)) # middle
    glPopMatrix()

    glPushMatrix()
    DrawCube((0.1, 1, 0.1), (-3.8, 2, 0.3), (30, 1, 0, 1)) # left
    glPopMatrix()

    glPushMatrix()
    DrawCube((0.1, 1, 0.1), (-3.8, 2, -0.3), (30, -1, 0, 1)) # right
    glPopMatrix()

def mouse():
    global ani_time
    glPushMatrix()
    DrawCube((2, 0.5, 2.5), (-5, -0.6, 0), (10 -ani_time%25*0.5, 0, 0, 1)) # below
    glPopMatrix()

    glPushMatrix()
    DrawCube((2, 0.5, 2.5), (-4.5, -0.9, 0), (0, 0, 0, 0)) # under
    glPopMatrix()

def tail():
    global ani_time
    glPushMatrix()
    DrawCube((6, 0.5, 2.5), (6, 0.5, 0), (10 -ani_time%40*0.5, 0, 0, 1)) # tail
    glPopMatrix()


def body():
    global ani_time
    glPushMatrix()

    glPushMatrix()
    glTranslate(0, 0, 0)
    DrawCubebyScale((8, 3, 4))
    glPopMatrix()
    
    mouse()
    tail()
    hair()
    
    front_right_leg()
    front_left_leg()

    back_right_leg()
    back_left_leg()

    glPopMatrix()

def Model():
    global ani_time
    glPushMatrix()
    if if_move:
        glTranslatef(0-ani_time % 360*0.3, 0, 0)
    body()
    
    glPopMatrix()
    
def light():
    glLightfv(GL_LIGHT0, GL_POSITION,  (1, 1, 1, 1))
    glLightfv(GL_LIGHT0, GL_AMBIENT, (0.2, 0.2, 0.2, 1.0))
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (0.6, 0.6, 0.6, 1.0))
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHTING)
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_FLAT) 

def keyboardCtrl():
    global rx, ry, tx, ty, zpos, rotate, move
    global if_ani, if_control, if_move, ControlMap, MoveChoice
    for e in pygame.event.get():
        if e.type == QUIT:
            sys.exit()
        elif e.type == KEYDOWN and e.key == K_ESCAPE:
            sys.exit()
        elif e.type == MOUSEBUTTONDOWN:
            if e.button == 4: zpos = max(1, zpos-1)
            elif e.button == 5: zpos += 1
            elif e.button == 1: rotate = True
            elif e.button == 3: move = True
        elif e.type == MOUSEBUTTONUP:
            if e.button == 1: rotate = False
            elif e.button == 3: move = False
        elif e.type == MOUSEMOTION:
            i, j = e.rel
            if rotate:
                rx += i
                ry += j
            if move:
                tx += i
                ty -= j
        elif e.type == KEYDOWN and e.key == K_RETURN: # animation control
            if if_ani:
                if_ani = False
            else:
                if_ani = True
        elif e.type == KEYDOWN and e.key == K_SPACE: # animation control
            if if_ani:
                if_ani = False
            else:
                if_ani = True

            if if_move:
                if_move = False
            else:
                if_move = True
        elif e.type == KEYDOWN and e.key == K_q: # FR_leg1 rotate up
            if ControlMap['FR_leg1'] == MoveChoice[1]:
                ControlMap['FR_leg1'] = MoveChoice[0]
            else:
                ControlMap['FR_leg1'] = MoveChoice[1]
        elif e.type == KEYDOWN and e.key == K_w: # FR_leg1 rotate down
            if ControlMap['FR_leg1'] == MoveChoice[2]:
                ControlMap['FR_leg1'] = MoveChoice[0]
            else:
                ControlMap['FR_leg1'] = MoveChoice[2]
        elif e.type == KEYDOWN and e.key == K_a: # FR_leg2 rotate up
            if ControlMap['FR_leg2'] == MoveChoice[1]:
                ControlMap['FR_leg2'] = MoveChoice[0]
            else:
                ControlMap['FR_leg2'] = MoveChoice[1]
        elif e.type == KEYDOWN and e.key == K_s: # FR_leg2 rotate down
            if ControlMap['FR_leg2'] == MoveChoice[2]:
                ControlMap['FR_leg2'] = MoveChoice[0]
            else:
                ControlMap['FR_leg2'] = MoveChoice[2]

def main():
    ControlMapInit()
    global if_ani, if_control, time, ani_time, ControlMap, MoveChoice
    pygame.init()
    display = (800, 600)
    pygame.display.set_mode(display, DOUBLEBUF | OPENGL)
    clock = pygame.time.Clock()

    light()

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    width, height = display
    # gluPerspective(100.0, width/float(height), 1, 100.0)
    gluPerspective(100, (display[0] / display[1]), 1, 500.0)
    glEnable(GL_DEPTH_TEST)
    glMatrixMode(GL_MODELVIEW)
    glutInit()

    
    time, ani_time = 0, 0
    if_control, if_ani = False, False

    while True:
        clock.tick(30)

        keyboardCtrl()
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        glLoadIdentity() # matrix initailize to identity
        glTranslate(tx/20., ty/20., - zpos)
        glRotate(ry, 1, 0, 0)
        glRotate(rx, 0, 1, 0)

        time += 1
        if time > 1000:
            time = 0
        if if_ani:
            ani_time = time
        else:
            ani_time = 0
        Model()

        pygame.display.flip()


if __name__ == "__main__":
    main()