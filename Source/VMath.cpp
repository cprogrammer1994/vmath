#include "Python.h"

#include <cmath>

PyObject * ModuleError;

struct Matrix {
	PyObject_HEAD
	float m[16];
};

struct Vector {
	PyObject_HEAD
	float v[3];
};

PyObject * Matrix_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

PyObject * Vector_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int Matrix_init(Matrix * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Matrix.\nCall NewMatrix(...) to get a Matrix object.");
	return -1;
}

int Vector_init(Vector * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Vector.\nCall NewVector(...) to get a Vector object.");
	return -1;
}

void Matrix_dealloc(Matrix * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

void Vector_dealloc(Vector * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * Matrix_str(Matrix * self) {
	return PyUnicode_FromFormat("<Matrix>");
}

PyObject * Vector_str(Vector * self) {
	return PyUnicode_FromFormat("<Vector>");
}

PyTypeObject MatrixType = {
	PyVarObject_HEAD_INIT(0, 0)
	"vmath.Matrix",
	sizeof(Matrix),
	0,
	(destructor)Matrix_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Matrix_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Matrix",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Matrix_init,
	0,
	Matrix_new,
};

PyTypeObject VectorType = {
	PyVarObject_HEAD_INIT(0, 0)
	"vmath.Vector",
	sizeof(Vector),
	0,
	(destructor)Vector_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Vector_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Vector",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Vector_init,
	0,
	Vector_new,
};

static PyMethodDef methods[] = {
	// {"normalize", normalize, METH_VARARGS, 0},
	// {"length", length, METH_VARARGS, 0},
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
