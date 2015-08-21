#define BF_LOG_ERROR_CANNOT_INSTRUMENT(reason, ...) \
    PyErr_Clear(); \
    bf_log(BF_LOG_ERROR, "Cannot instrument"); \
    goto instrument_loop_end;
    
static void do_instrument(PyObject *list) {
	if (!(context.flags & BLACKFIRE_FLAGS_FN_ARGS)) {
		return;
	}

	if (PyList_Check(list)) {
		if (context.fn_args_lookup == NULL) {
			context.fn_args_lookup = ht_create(HT_FN_ARGS_SIZE);
			if (!context.fn_args_lookup) {
				bf_log(BF_LOG_ERROR, "Cannot allocate fn_args_lookup");
				context.flags &= ~BLACKFIRE_FLAGS_FN_ARGS;
				return;
			}
		}

		Py_ssize_t len = PyList_Size(list);
		if(len == 0) {
			bf_log(BF_LOG_ERROR, "No function to instrument");
			context.flags &= ~BLACKFIRE_FLAGS_FN_ARGS;
			return;
		}

		PyObject *tuple;
		Py_ssize_t i;
#ifndef IS_PY3K
		PyObject * from_list = Py_BuildValue("[s]", PyStr_FromString("*"));
		Py_INCREF(from_list);
#endif

		for (i = 0 ; i < len ; i++) {
			tuple = PyList_GET_ITEM(list, i);

			if (!PyTuple_Check(tuple)) {
				bf_log(BF_LOG_ERROR, "Wrong function definition. Tuple expected.");
				continue;
			}

			if (PyTuple_Size(tuple) != 4) {
				bf_log(BF_LOG_ERROR, "Wrong function definition.");
				continue;
			}

			PyObject *module_name = PyTuple_GET_ITEM(tuple, 0);
			PyObject *class_name = PyTuple_GET_ITEM(tuple, 1);
			PyObject *method_name = PyTuple_GET_ITEM(tuple, 2);
			PyObject *arg_name = PyTuple_GET_ITEM(tuple, 3);

#ifdef IS_PY3K
			PyObject* module = PyImport_Import(module_name); // New reference
#else
			PyObject* module = PyImport_ImportModuleLevel(PyStr_AS_CSTRING(module_name), NULL, NULL, from_list, -1); // New reference
#endif

			if (!module || module == Py_None) {
				BF_LOG_ERROR_CANNOT_INSTRUMENT("Module not found");
			}

			PyObject *module_dict = PyModule_GetDict(module); // Borrowed reference

			PyObject *class = NULL;
			PyObject *method = NULL;

			if (class_name != Py_None) {
				class = PyDict_GetItem(module_dict, class_name); // Borrowed reference

				if (!class || class == Py_None) {
					BF_LOG_ERROR_CANNOT_INSTRUMENT("Class not found");
				}

#ifndef IS_PY3K
				if (PyClass_Check(class)) {
					// Python Class
					PyClassObject * classobj = (PyClassObject *) class;
					method = PyDict_GetItem(classobj->cl_dict, method_name); // Borrowed reference
				} else
#endif
				if (PyType_Check(class)) {
					// "Class" defined in C or any class with Python3
					PyTypeObject * type = (PyTypeObject*)class;
					method = PyDict_GetItem(type->tp_dict, method_name); // Borrowed reference
				} else {
					BF_LOG_ERROR_CANNOT_INSTRUMENT("Unknown class type");
				}
			} else {
				method = PyDict_GetItem(module_dict, method_name); // Borrowed reference
			}

			if (!method || method == Py_None) {
				BF_LOG_ERROR_CANNOT_INSTRUMENT("Method not found");
			}

			void * key = NULL;
			if (PyCFunction_Check(method)) {
				PyCFunctionObject * function = ((PyCFunctionObject *) method);
				key = function->m_ml;

				bf_log(BF_LOG_DEBUG, "instrumented (C Function)");
			} else if (PyFunction_Check(method)) {
#ifdef IS_PY3K
				PyCodeObject *code = (PyCodeObject *) PyObject_GetAttrString(method, "__code__");
#else
				PyCodeObject *code = (PyCodeObject *) PyObject_GetAttrString(method, "func_code");
#endif
				key = code->co_code;

				if (class) {
					bf_log(BF_LOG_DEBUG, "instrumented (Python Method)");
				} else {
					bf_log(BF_LOG_DEBUG, "instrumented (Python Function)",);
				}
			} else if (class && PyType_Check(class)) {
				bf_log(BF_LOG_DEBUG, "instrumented (C type member)");
				key = ((PyMethodDescrObject *) method)->d_method;
			} else {
				BF_LOG_ERROR_CANNOT_INSTRUMENT("Unknown method type");
			}

			Py_INCREF(arg_name);
			ht_add(context.fn_args_lookup, (uint64_t)key, (uint64_t) arg_name);

		instrument_loop_end:
			Py_XDECREF(module);
		}
#ifndef IS_PY3K
		Py_DECREF(from_list);
#endif
	} else {
		bf_log(BF_LOG_ERROR, "instrumentation aborted");
	}
}
