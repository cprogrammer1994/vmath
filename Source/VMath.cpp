#include "Python.h"

#include <cmath>

PyObject * ModuleError;

static PyMethodDef methods[] = {
	// {"cross", cross, METH_VARARGS, 0},
	// {"dot", dot, METH_VARARGS, 0},
	// {"inv", inv, METH_VARARGS, 0},
	// {"det", det, METH_VARARGS, 0},
	// {"lst", lst, METH_VARARGS, 0},
	{0, 0, 0, 0},
};

PyObject * InitModule(PyObject * module) {
	return module;
}

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "vmath", 0, -1, methods, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_vmath();
}

PyObject * PyInit_vmath() {
	PyObject * module = PyModule_Create(&moduledef);
	return InitModule(module);
}

#else

extern "C" {
	PyObject * initvmath();
}

PyObject * initvmath() {
	PyObject * module = Py_InitModule("vmath", methods);
	return InitModule(module);
}

#endif
