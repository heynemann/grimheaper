#include <Python.h>

typedef struct {
    int first;
    int last;
    int *heap;
} queue;

void exchange(queue *q, int pos, int pos2) {
    int aux = q->heap[pos];
    q->heap[pos] = q->heap[pos2];
    q->heap[pos2] = aux;
}


int compare(int item, int other) {
    return item > other;
}


int swim(queue *q) {
    int k = q -> last + 2;

    while (k > 1) {
        if (compare(q->heap[k], q->heap[k / 2])) {
            exchange(q, k, k / 2);
        }

        k = k / 2;
    }

    return k;
}


static PyObject * create_heap(PyObject *self, PyObject *args)
{
    int *heap;
    heap = malloc(sizeof(int) * 1000);
    *heap = 0;

    queue q = {
        .first = 1,
        .last = 1,
        .heap = heap
    };

    printf("\ncreating @%p\n", &q);

    PyObject *result = PyCapsule_New(&q, NULL, NULL);

    return result;
}


static PyObject * put(PyObject *self, PyObject *args)
{
    PyObject *capsule;
    int item;

    if (!PyArg_ParseTuple(args, "Oi", &capsule, &item)) {
        return NULL;
    }

    queue *q = (queue*)PyCapsule_GetPointer(capsule, NULL);
    printf("\nusing queue @%p\n", q);

    /*q->heap[q->last] = item;*/
    /*int pos = swim(q);*/
    q->last++;

    return Py_BuildValue("i", 1);
}


static PyMethodDef heap_funcs[] = {
    {
        "create_heap",
        (PyCFunction)create_heap, 
        METH_VARARGS,
        "Creates a binary heap"
    },
    {
        "put",
        (PyCFunction)put, 
        METH_VARARGS,
        "Puts an item in the heap"
    },
    {NULL}
};

void initheap(void)
{
    Py_InitModule3("heap", heap_funcs,
                   "Heap extension");
}
