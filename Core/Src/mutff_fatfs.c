#include "mutff_fatfs.h"

/*
 * mutff_fatfs.c
 *
 *  Created on: Feb 8, 2023
 *      Author: Frank Plowman <post@frankplowman.com>
 */

#include <fatfs.h>
#include "../../Libraries/mutff/include/mutff.h"

MuTFFError mutff_read_fatfs(mutff_file_t *file, void *dest,
                             unsigned int bytes) {
	unsigned int read;
	f_read(file, dest, bytes, &read);
	if (read != bytes) {
		return MuTFFErrorIOError;
	}
	return MuTFFErrorNone;
}

MuTFFError mutff_write_fatfs(mutff_file_t *file, void *src,
                              unsigned int bytes) {
	unsigned int written;
	f_write(file, src, bytes, &written);
	if (written != bytes) {
		return MuTFFErrorIOError;
	}
	return MuTFFErrorNone;
}

MuTFFError mutff_tell_fatfs(mutff_file_t *file, unsigned int *location) {
	return MuTFFErrorIOError;
}

MuTFFError mutff_seek_fatfs(mutff_file_t *file, long delta) {
	return MuTFFErrorIOError;
}
