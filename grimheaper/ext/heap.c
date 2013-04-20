#include <Python.h>

int* heap;

static PyObject * create_heap(PyObject *self, PyObject *args)
{
    heap = malloc(sizeof(int) * 1000);
    *heap = 10;

    return Py_BuildValue("i", 1);
}


static PyObject * put(PyObject *self, PyObject *args)
{
    int *item;
    if (!PyArg_ParseTuple(args, "i", &item)) {
        return NULL;
    }

    return Py_BuildValue("i", item);
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
