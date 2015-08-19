typedef struct {
	char resolved_name[100];
	_method *caller;
	_method *callee;
	unsigned int caller_rlevel;
	unsigned int callee_rlevel;
	PyObject *caller_arg;
	PyObject *callee_arg;

	unsigned int calls;
	BF_METRICS;
} _profile_entry;
