
/* The original ray tracing code was taken from the web site:
    https://www.purplealienplanet.com/node/23 */

/* A simple ray tracer */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /* Needed for boolean datatype */
#include <math.h>
#include <string.h>
#include <pthread.h>

/* added scale and threads to allow command line controls */
/* scale controls how many times the height and width will increase */
/* threads is used to indicate how many threads should be created */
int scale = 1;
int threads = 1;
/* output 0 means not output file is created by default */
/* change to 1 to create output image file image.ppm */
/* using the -o on the command line sets output==1 (creates the file) */
int output = 0;
// int currentSphere = -1;

#define min(a, b) (((a) < (b)) ? (a) : (b))

/* Width and height of out image */
/* scale added to allow larger output images to be created */
#define WIDTH (800 * scale)
#define HEIGHT (600 * scale)

/* The vector structure */
typedef struct
{
    float x, y, z;
} vector;

/* The sphere */
typedef struct
{
    vector pos;
    float radius;
    int material;
} sphere;

/* The ray */
typedef struct
{
    vector start;
    vector dir;
} ray;

/* Colour */
typedef struct
{
    float red, green, blue;
} colour;

/* Material Definition */
typedef struct
{
    colour diffuse;
    float reflection;
} material;

/* Lightsource definition */
typedef struct
{
    vector pos;
    colour intensity;
} light;
// typedef struct task task;
typedef struct a_task
{
    ray *r;
    sphere *s;
    float *t;
    struct a_task *next;
} task;

typedef struct
{
    task *head;
    task *tail;
} queue;

int push(queue *q)
{
    task *new = malloc(sizeof(task));
    if (new == NULL)
        return -1;
    new->next = NULL;

    if (q->tail != NULL)
        q->tail->next = new;

    q->tail = new;
    if (q->head == NULL) /* first value */
        q->head = new;
    printf("added task\n");
    return 0;
}
void *pop(queue *q)
{
    printf("lets pop it\n");
    if (q->head != NULL)
    {
        task *current = q->head;
        q->head = q->head->next;
        free(current);
    }
    return NULL;
}

void popAll(queue *q)
{
    task *temp = q->head;
    task *freeMe = NULL;
    int count = 0;
    while (temp->next != NULL)
    {
        freeMe = temp;
        temp = temp->next;
        free(freeMe);
        count++;
    }
    printf("Count: %d\n", count);
    free(temp);
}
void printThing(queue *q)
{
    task *temp = q->head;
    while (temp->next != NULL)
    {
        printf("there is a task in queue\n");
        temp = temp->next;
    }
}

int main(int argc, char *argv[])
{

    queue *q = malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    int x, y;
    pthread_t threadList[threads];


    for (y = 0; y < 5; y++)
    {
        for (x = 0; x < 2; x++)
        {

            push(q);
        }
    }
    popAll(q);
            return 0;

}
