#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *
py_dipra_render(PyObject *self, PyObject *args)
{
    return PyLong_FromLong(1337);
}

static PyMethodDef dipra_methods[] = {
    {"rasterize", py_dipra_render, METH_VARARGS, "Rasterize a polygon"},
    {NULL, NULL, 0, NULL} // sentinel
};

static struct PyModuleDef dipramodule = {
    PyModuleDef_HEAD_INIT,
    "dipra",       // module name
    NULL,          // module documentation, may be NULL
    -1,            // size of per-interpreter state or -1 if the module keeps state in global variables
    dipra_methods, // module methods
};

PyMODINIT_FUNC
PyInit_dipra(void)
{
    PyObject *module;

    module = PyModule_Create(&dipramodule);
    if (module == NULL)
        return NULL;

    return module;
}