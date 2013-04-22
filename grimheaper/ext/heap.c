#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *items;
} BinaryHeap;

PyObject *get(BinaryHeap *self, int pos) {
    return PyList_GetItem(self->items, pos);
}

int len(BinaryHeap *self) {
    return (int)PyList_Size(self->items);
}

int set(BinaryHeap *self, int pos, PyObject *item) {
    int result = PyList_SetItem(self->items, pos, item);
    if (result == -1) {
        printf("Assigning item to position %d FAILED!", pos);
    }
    return result;
}

int del(BinaryHeap *self, int pos) {
    Py_DECREF(get(self, pos));
    return PyList_SetSlice(self->items, pos, pos + 1, NULL);
}

int append(BinaryHeap *self, PyObject *item) {
    int result = PyList_Append(self->items, item);
    return result;
}

void exchange(BinaryHeap *self, int pos, int pos2) {
    PyObject *item = get(self, pos);
    PyObject *item2 = get(self, pos2);

    Py_INCREF(item);
    set(self, pos, item2);

    Py_INCREF(item2);
    set(self, pos2, item);
}

int greater(PyObject *item, PyObject *other) {
    return PyObject_Compare(item, other) > 0;
}


int swim(BinaryHeap *self) {
    int k = len(self) - 1;

    while (k > 1) {
        PyObject *item = get(self, k);
        PyObject *parent = get(self, k / 2);

        if (greater(item, parent)) {
            /*printf("%d and %d (%ld and %ld) LEN: %d\n", k, k / 2, PyInt_AsLong(item), PyInt_AsLong(parent), self -> last);*/
            exchange(self, k, k / 2);
        } else {
            break;
        }

        k = k / 2;
    }

    return k;
}

int sink(BinaryHeap *self, int pos) {
    int k = pos;
    int last = len(self) - 1;
    /*printf("LAST: %d\n", self->last);*/

    while (k * 2 < last) {
        /*printf("Trying to sink for item %d\n\n", k);*/
        PyObject *item = get(self, k);
        int childIndex = k * 2;
        /*printf("childIndex: %d\n\n", childIndex);*/
        PyObject *child = get(self, k * 2);

        if (k * 2 + 1 < last) {
            PyObject *child2 = get(self, k * 2 + 1);

            if (greater(child2, child)) {
                childIndex++;
                child = child2;
            }
        }

        /*printf("comparing items at %d and %d (Parent: %li Child: %li)\n", k, childIndex, PyInt_AsLong(item), PyInt_AsLong(child));*/
        if (greater(child, item)) {
            /*printf("Exchanging items at %d and %d (pos: %li pos2: %li)\n", k, childIndex, PyInt_AsLong(get(self, k)), PyInt_AsLong(get(self, childIndex)));*/
            exchange(self, k, childIndex);
        } else {
            break;
        }

        k = childIndex;
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
    {NULL}  /* Sentinel */
};

static PyObject *
BinaryHeap_put(BinaryHeap* self, PyObject *item)
{
    append(self, item);
    int result = swim(self);
    return Py_BuildValue("i", result);
}

static PyObject *
BinaryHeap_pop(BinaryHeap* self)
{
    int item_index = len(self) - 1;
    /*printf("Removing item %d", item_index);*/

    PyObject *item = get(self, 1);

    exchange(self, 1, item_index);

    del(self, item_index);

    sink(self, 1);

    Py_INCREF(item);
    return item;
}

static int BinaryHeap_len(BinaryHeap* self)
{
    return len(self) - 1;
}

static PyMethodDef BinaryHeap_methods[] = {
    {"put", (PyCFunction)BinaryHeap_put, METH_O,
     "Puts a new item in the heap"
    },
    {"pop", (PyCFunction)BinaryHeap_pop, METH_NOARGS,
     "Gets the largest item in the heap"
    },
    {NULL}  /* Sentinel */
};

static PySequenceMethods BinaryHeap_as_sequence[] = {
    {(lenfunc)BinaryHeap_len},       /* inquiry sq_length; */
    {0},                             /* binaryfunc sq_concat; */
    {0},                             /* intargfunc sq_repeat; */
    {0},                             /* intargfunc sq_item; */
    {0},                             /* intintargfunc sq_slice; */
    {0},                             /* intobjargproc sq_ass_item; */
    {0},                             /* intintobjargproc sq_ass_slice; */
    {NULL}                           /* Sentinel */
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
    BinaryHeap_as_sequence,    /*tp_as_sequence*/
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
