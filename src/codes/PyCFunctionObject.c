struct PyMethodDef {
	const char  *ml_name;   /* The name of the built-in function/method */
	PyCFunction ml_meth;    /* The C function that implements it */
	int         ml_flags;   /* Combination of METH_xxx flags, which mostly
				   describe the args expected by the C func */
	const char  *ml_doc;    /* The __doc__ attribute, or NULL */
};
typedef struct PyMethodDef PyMethodDef;

typedef struct {
	PyObject_HEAD
	PyMethodDef *m_ml;     /* Description of the C function to call */
	PyObject    *m_self;   /* Passed as 'self' arg to the C func, can be NULL */
	PyObject    *m_module; /* The __module__ attribute, can be anything */
} PyCFunctionObject;
