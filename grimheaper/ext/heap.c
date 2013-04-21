#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *items;
    int last;
} BinaryHeap;

PyObject *get(BinaryHeap *self, int pos) {
    return PyList_GetItem(self->items, pos);
}

int set(BinaryHeap *self, int pos, PyObject *item) {
    return PyList_SetItem(self->items, pos, item);
}

int append(BinaryHeap *self, PyObject *item) {
    int result = PyList_Append(self->items, item);
    /*printf("\n\nAPPEND WORKED? %d\n\n", result);*/
    return result;
}

void exchange(BinaryHeap *self, int pos, int pos2) {
    PyObject *aux = get(self, pos);
    set(self, pos, get(self, pos2));
    set(self, pos2, aux);
}


int compare(PyObject *item, PyObject *other) {
    return PyObject_Compare(item, other) > 0;
}


int swim(BinaryHeap *self) {
    int k = self -> last;

    while (k > 1) {
        PyObject *item = get(self, k);
        PyObject *parent = get(self, k / 2);
        if (compare(item, parent)) {
            exchange(self, k, k / 2);
        } else {
            return k;
        }

        k = k / 2;
    }

    return k;
}



static int BinaryHeap_traverse(BinaryHeap *self, visitproc visit, void *arg)
{
    Py_VISIT(self->items);
    return 0;
}

static int BinaryHeap_clear(BinaryHeap *self)
{
    Py_CLEAR(self->items);
    return 0;
}

static void BinaryHeap_dealloc(BinaryHeap* self)
{
    BinaryHeap_clear(self);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *BinaryHeap_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    BinaryHeap *self;

    self = (BinaryHeap *)type->tp_alloc(type, 0);

    if (self != NULL) {
        self->items = PyList_New(0);

        if (self->items == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        self->last = 0;
    }

    return (PyObject *)self;
}

static int BinaryHeap_init(BinaryHeap *self, PyObject *args, PyObject *kwds)
{
    Py_INCREF(Py_None);
    append(self, Py_None);

    return 0;
}


static PyMemberDef BinaryHeap_members[] = {
    {"items", T_OBJECT_EX, offsetof(BinaryHeap, items), 0,
     "items in the heap"},
    {"last", T_INT, offsetof(BinaryHeap, last), 0,
     "index of the last item in the heap"},
    {NULL}  /* Sentinel */
};

static PyObject *
BinaryHeap_put(BinaryHeap* self, PyObject *item)
{
    append(self, item);
    self->last++;
    int result = swim(self);
    return Py_BuildValue("i", result);
}

static PyMethodDef BinaryHeap_methods[] = {
    {"put", (PyCFunction)BinaryHeap_put, METH_O,
     "Puts a new item in the heap"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject BinaryHeapType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "grimheaper.BinaryHeap",   /*tp_name*/
    sizeof(BinaryHeap),        /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)BinaryHeap_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC, /*tp_flags*/
    "Binary Heap",           /* tp_doc */
    (traverseproc)BinaryHeap_traverse,   /* tp_traverse */
    (inquiry)BinaryHeap_clear,           /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    BinaryHeap_methods,             /* tp_methods */
    BinaryHeap_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)BinaryHeap_init,      /* tp_init */
    0,                         /* tp_alloc */
    BinaryHeap_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initheap(void) 
{
    PyObject* m;

    if (PyType_Ready(&BinaryHeapType) < 0)
        return;

    m = Py_InitModule3("heap", module_methods,
                       "Binary Heap implementation.");

    if (m == NULL)
      return;

    Py_INCREF(&BinaryHeapType);
    PyModule_AddObject(m, "BinaryHeap", (PyObject *)&BinaryHeapType);
}

/*typedef struct {*/
    /*int first;*/
    /*int last;*/
    /*int *heap;*/
/*} queue;*/


/*static PyObject * create_heap(PyObject *self, PyObject *args)*/
/*{*/
    /*int *heap;*/
    /*heap = malloc(sizeof(int) * 1000);*/
    /**heap = 0;*/

    /*queue q = {*/
        /*.first = 1,*/
        /*.last = 1,*/
        /*.heap = heap*/
    /*};*/

    /*printf("\ncreating @%p\n", &q);*/

    /*PyObject *result = PyCapsule_New(&q, NULL, NULL);*/

    /*return result;*/
/*}*/


/*static PyObject * put(PyObject *self, PyObject *args)*/
/*{*/
    /*PyObject *capsule;*/
    /*int item;*/

    /*if (!PyArg_ParseTuple(args, "Oi", &capsule, &item)) {*/
        /*return NULL;*/
    /*}*/

    /*queue *q = (queue*)PyCapsule_GetPointer(capsule, NULL);*/
    /*printf("\nusing queue @%p\n", q);*/

    /*[>q->heap[q->last] = item;<]*/
    /*[>int pos = swim(q);<]*/
    /*q->last++;*/

    /*return Py_BuildValue("i", 1);*/
/*}*/


/*static PyMethodDef heap_funcs[] = {*/
    /*{*/
        /*"create_heap",*/
        /*(PyCFunction)create_heap, */
        /*METH_VARARGS,*/
        /*"Creates a binary heap"*/
    /*},*/
    /*{*/
        /*"put",*/
        /*(PyCFunction)put, */
        /*METH_VARARGS,*/
        /*"Puts an item in the heap"*/
    /*},*/
    /*{NULL}*/
/*};*/

/*void initheap(void)*/
/*{*/
    /*Py_InitModule3("heap", heap_funcs,*/
                   /*"Heap extension");*/
/*}*/
