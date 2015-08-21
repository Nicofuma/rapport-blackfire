/**
 * Returns a new reference to the instrumented argument, or NULL
 */
static PyObject* get_arg_from_python(PyFrameObject *frame, PyObject * arg) {
	// Get By index
	long last = PyNumeric_AsULong(arg);

	if (last != -1) {
		if (PyTuple_Check(frame->f_code->co_varnames)) {
			long first = 1;

			// Skip self
			if (strcmp(PyStr_AS_CSTRING(PyTuple_GET_ITEM(frame->f_code->co_varnames, 0)), "self") == 0) {
				bf_log(BF_LOG_DEBUG, "Skip self.");
				last++;
				first = 2;
			}

			PyObject *args = PyList_New(0);
			long i;

			// We are instrumenting a Python function, frame is referring to the 
			// calleeand f_localsplus points to the first local. Moreover the 
			// first locals are the arguments of the function (in the same order).
			for (i = first; i <= last; i++) {
				if (last <= frame->f_code->co_argcount) {
					PyObject *value = frame->f_localsplus[i - 1];

					bf_log(BF_LOG_DEBUG, "Found arg from PyFunction.");
					PyObject *item = Py_BuildValue("(lO)", i - first + 1, value);
					PyList_Append(args, item);
				} else {
					bf_log(BF_LOG_ERROR, "Invalid arg last");
				}
			}

			return args;
		} else {
			bf_log(BF_LOG_ERROR, "Invalid arg.");
		}
	} else {
		bf_log(BF_LOG_ERROR, "Invalid arg (last %d).", last);
	}

	return NULL;
}
