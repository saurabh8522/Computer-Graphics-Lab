#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

struct vertex {
        float  x;
        float  y;
};


typedef struct vertex triangle[3];


struct tle {
        triangle t;
        struct tle  *next;
};

struct vertex
mid(const struct vertex *v1, const struct vertex *v2)
{
        assert(v1);
        assert(v2);

        struct vertex mid;
        mid.x = (v1->x + v2->x) / 2.0;
        mid.y = (v1->y + v2->y) / 2.0;
        return mid;
}


struct tle *
sierpinski(struct tle *s)
{
        assert(s);

        struct tle *new = s;

        while (s) {
               
                triangle st = {s->t[0], s->t[1], s->t[2]};

                triangle n1, n2;

                n2[0] = mid(&st[0], &st[2]);
                n2[1] = n1[2] = mid(&st[1], &st[2]);
                n2[2] = st[2];

                n1[0] = mid(&st[0], &st[1]);
                n1[1] = st[1];

                s->t[1] = n1[0];
                s->t[2] = n2[0];

                struct tle *new1 = malloc(sizeof(struct tle));
                struct tle *new2 = malloc(sizeof(struct tle));
                assert(new1);
                assert(new2);
                int i;
                for (i = 0; i < 3; i++) {
                        new2->t[i] = n2[i];
                        new1->t[i] = n1[i];
                }
                new2->next = s->next;
                new1->next = new2;
                s->next = new1;

                s = new2->next;
        }

        return new;
}

void
free_sierpinski(struct tle *s)
{
        while (s) {
                struct tle *next = s->next;
                free(s);
                s = next;
        }
}


const struct tle *sier;

void
render_sierpinski(void)
{
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        const struct tle *s = sier;
        while (s) {
                glBegin(GL_POLYGON);
                int i;
                for (i = 0; i < 3; i++)
                        glVertex2f(s->t[i].x, s->t[i].y);
                glEnd();
                s = s->next;
        }
        glFlush();
}



void
draw_sierpinski(int argc, char *argv[ ], const struct tle *s)
{
        assert(s);
        sier = s;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Sierpinski");
        glutDisplayFunc(render_sierpinski);
        glutMainLoop();
}

int
main(int argc, char *argv[ ])
{
        if (argc != 8) {
                fprintf(stderr, "Usage: sierpinski n x1 y1 x2 y2 x3 y3\n");
                return 1;
        }

        struct tle *s = malloc(sizeof(struct tle));
        assert(s);
        s->next = 0;
        sscanf(argv[2], "%f", &s->t[0].x);
        sscanf(argv[3], "%f", &s->t[0].y);
        sscanf(argv[4], "%f", &s->t[1].x);
        sscanf(argv[5], "%f", &s->t[1].y);
        sscanf(argv[6], "%f", &s->t[2].x);
        sscanf(argv[7], "%f", &s->t[2].y);

        unsigned int level;
        sscanf(argv[1], "%u", &level);

        int i;
        for (i = 0; i < level; i++)
                s = sierpinski(s);

        draw_sierpinski(argc, argv, s);
        free_sierpinski(s);

        return 0;
}