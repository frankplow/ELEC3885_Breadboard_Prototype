/*
 * mutff_fatfs.h
 *
 *  Created on: Feb 8, 2023
 *      Author: Frank Plowman <post@frankplowman.com>
 */

#ifndef INC_MUTFF_FATFS_H_
#define INC_MUTFF_FATFS_H_

#include <mutff.h>

MuTFFError mutff_read_fatfs(mutff_file_t *file, void *dest,
                             unsigned int bytes);

MuTFFError mutff_write_fatfs(mutff_file_t *file, void *src,
                              unsigned int bytes);

MuTFFError mutff_tell_fatfs(mutff_file_t *file, unsigned int *location);

MuTFFError mutff_seek_fatfs(mutff_file_t *file, long delta);

#endif /* INC_MUTFF_FATFS_H_ */
