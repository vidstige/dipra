#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "dipra/dipra.h"

static PyObject* array_to_list_i(int* values, size_t n) {
    PyObject* python_val = PyList_New(n);
    for (int i = 0; i < n; i++) {
        PyObject* item = Py_BuildValue("i", values[i]);
        PyList_SetItem(python_val, i, item);
    }
    return python_val;
}

static PyObject* array_to_list_d(double* values, size_t n) {
    PyObject* python_val = PyList_New(n);
    for (int i = 0; i < n; i++) {
        PyObject* item = Py_BuildValue("d", values[i]);
        PyList_SetItem(python_val, i, item);
    }
    return python_val;
}

static PyObject *
py_dipra_render(PyObject *self, PyObject *args)
{
    PyObject *polygonObject, *bboxObject = NULL;
    if (!PyArg_ParseTuple(args, "O!|O", &PyList_Type, &polygonObject, &bboxObject)) {
        PyErr_SetString(PyExc_TypeError, "polygon must be a list.");
        return NULL;
    }

    // convert polygon to c-structure    
    size_t vertices = PyObject_Length(polygonObject);
    polygon_t polygon = create_polygon(vertices);

    PyObject *iter = PyObject_GetIter(polygonObject);
    int i = 0;
    for (PyObject *next = PyIter_Next(iter); next != NULL && i < polygon.n; next = PyIter_Next(iter), i++) {
        if (!PyArg_ParseTuple(next, "dd", polygon.x + i, polygon.y + i)) {
            PyErr_SetString(PyExc_TypeError, "expected tuple");
            return NULL;
        }
    }

    // if bbox not supplied, create one
    bbox_t bbox;
    if (bboxObject == NULL) {
        bbox = polygon_bbox(&polygon);
    } else {
        // TODO: unpack bboxObject into bbox_t
        PyErr_SetString(PyExc_NotImplementedError, "Not implemented yet");
        return NULL;
    }
    
    int area = bbox_area(&bbox);
    render_t render = create_render(area);
    dipra_render(&polygon, &bbox, &render);
    destroy_polygon(&polygon);

    // convert to lists
    PyObject *xList = array_to_list_i(render.x, render.n);
    PyObject *yList = array_to_list_i(render.y, render.n);
    PyObject *alphaList = array_to_list_d(render.alpha, render.n);
        
    destroy_render(&render);
    return Py_BuildValue("OOO", xList, yList, alphaList);
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