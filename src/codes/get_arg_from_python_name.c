/**
 * Returns a new reference to the instrumented argument, or NULL
 */
static PyObject* get_arg_from_python(PyFrameObject *frame, PyObject * arg) {
	PyFrame_FastToLocals(frame);
	if (frame->f_code->co_argcount) {
		PyObject *locals = frame->f_locals;
		if (locals) {
			PyObject *value = PyDict_GetItemString(locals, PyStr_AS_CSTRING(arg)); // Borrowed reference

			if (value && value != Py_None) {
				bf_log(BF_LOG_DEBUG, "Found arg from PyFunction (type: %s).", value->ob_type->tp_name);

				return Py_BuildValue("(OO)", arg, value);
			} else {
				bf_log(BF_LOG_ERROR, "Invalid arg (%s not found in locals).", PyStr_AS_CSTRING(arg));
			}
		} else {
			bf_log(BF_LOG_ERROR, "Invalid arg (no local to fetch the argument).");
		}
	} else {
		bf_log(BF_LOG_ERROR, "Invalid arg (the function doesn't take any argument).");
	}

	return NULL;
}
