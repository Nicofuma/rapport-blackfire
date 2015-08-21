static int _blackfire_count_opcodes(PyObject *self, PyFrameObject *frame, int what, PyObject *arg) {
	if (!context.profiling) {
		return -1;
	}

	if (what == PyTrace_LINE) {
		// Decode the lnotab field to retrieve the bounds of the line.
		// inspired by dis.findlinestarts()
		char * code;
		Py_ssize_t code_size;

		PyBytes_AsStringAndSize(frame->f_code->co_code, &code, &code_size);

		int64_t current_opcode = frame->f_lasti;
		int64_t first_opcode = 0;
		int64_t last_opcode = (int64_t) INT64_MAX;

		char * s;
		Py_ssize_t length;
		Pylnotab_AsStr(frame->f_code->co_lnotab, s, length);

		int64_t lineno = frame->f_code->co_firstlineno;
		int64_t addr = 0;
		int64_t lastlineno = -1;

		int64_t j = 0;
		for (j=0; j < length;) {
			int byte_incr = s[j++];
			int line_incr = s[j++];

			if (byte_incr) {
				if (lineno != lastlineno) {
					if (addr <= current_opcode) {
						first_opcode = addr;
					} else if (addr >= current_opcode) {
						last_opcode = addr;
						break;
					}

					lastlineno = lineno;
				}
				addr += byte_incr;
			}
			lineno += line_incr;
		}

		if (lineno != lastlineno) {
			if (addr <= current_opcode) {
				first_opcode = addr;
			} else if (addr >= current_opcode) {
				last_opcode = addr;
			}
		}

		// Lets count the opcodes in the line
		for (current_opcode = first_opcode; current_opcode < last_opcode && current_opcode < code_size; current_opcode++) {
			char c = code[current_opcode];

			context.opcode_count++;

			// opcode with parameter
			if (c >= HAVE_ARGUMENT) {
				current_opcode += 2;
			}
		}
	}

	return 0;
}
