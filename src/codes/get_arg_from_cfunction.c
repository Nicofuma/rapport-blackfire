/**
 * Returns a new reference to the instrumented argument, or NULL
 */
static PyObject* get_arg_from_cfunction(PyFrameObject *frame, PyCFunctionObject * func, PyObject * arg) {
	long index;
	if (PyNumeric_Check(arg)) {
		index = PyNumeric_AsULong(arg);
	} else {
		bf_log(BF_LOG_ERROR, "Insupported key type %s in CFunction instrumentation.", (arg)->ob_type->tp_name);

		return NULL;
	}

	if (index >= 0) {
		bf_log(BF_LOG_DEBUG, "Getting %d args from CFunction.", index);

		PyObject *args = PyList_New(0);

		// We are instrumenting a C function, frame is referring to the caller
		// and f_valuestack points just after the last local and so at the first argument
		long i;
		for (i = 1; i <= index; i++) {
			PyObject *value = frame->f_valuestack[i];

			bf_log(BF_LOG_DEBUG, "Found arg from CFunction (type: %s).", value->ob_type->tp_name);
			PyObject *item = Py_BuildValue("(lO)", i, value);
			PyList_Append(args, item);
		}

		return args;
	} else {
		bf_log(BF_LOG_ERROR, "Invalid arg index %d", index);
	}

	return NULL;
}
