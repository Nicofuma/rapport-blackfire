#define BF_METRICS \
	long long wt; \
	long long cpu; \
	long long opcode;

typedef struct {
	PyObject *module_name;
	PyObject *class_name;
	PyObject *name;
	bool module_resolved;
	unsigned int rec_level; // Current rec level of the method
} _method;

typedef struct {
	_method *method;
	unsigned int rec_level; // Rec level of the call
	PyObject *arg;

	BF_METRICS;
} _callstack_item;
