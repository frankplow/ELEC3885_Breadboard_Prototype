/*
 * container_template.h
 *
 * This file defines a bare-bones QTFF file. It is set up with a single track of uncompressed video
 * with the following parameters:
 * - 12fps
 *
 * Many of the fields in this template will need to be modified at run-time, for example the creation
 * time should be taken from the RTC.
 *
 * File
 *  ╷
 *  ├─ ftyp
 *  │
 *  ├─ moov
 *  │   ╷
 *  │   ├─ mvhd
 *  │   │
 *  │   └─ trak
 *  │       ╷
 *  │       ├─ tkhd
 *  │       │
 *  │       └─ mdia
 *  │           ╷
 *  │           ├─ mdhd
 *  │           │
 *  │           ├─ hdlr
 *  │           │
 *  │           └─ minf
 *  │               ╷
 *  │               ├─ vmhd
 *  │               │
 *  │               └─ hdlr
 *  └─ mdat
 *
 *
 *  Created on: 7 Feb 2023
 *      Author: Frank Plowman <post@frankplowman.com>
 */

#ifndef INC_CONTAINER_TEMPLATE_H_
#define INC_CONTAINER_TEMPLATE_H_

// stdlib includes
#include <stdbool.h>

// library includes
#include <mutff.h>

// project includes


#define FRAME_RATE 13
#define WIDTH 480
#define HEIGHT 270

const MuTFFMediaHeaderAtom mdhd_template = {
		0,           // Version
		0,           // Flags
		0,           // Creation time
		0,           // Modification time
		FRAME_RATE,  // Time scale
		0,           // Duration
		0,		     // Language
		0,           // Quality
};

const MuTFFMediaAtom mdia_template = {
		mdhd_template,  // mdhd
		false,          // elng present
		{},
		false,          // hdlr present
		{},
		false,          // minf present
		{},
		{},
		{},
		false,          // udta present
		{}
};

const MuTFFTrackHeaderAtom tkhd_template = {
		0,        									// Version
		0,        									// Flags
		0,        									// Creation time
		0,        									// Modification time
		0,        									// Track ID
		0,        									// Duration
		0,        									// Layer
		0,  	  									// Alternate group
		{1, 0},   									// Volume
		{         									// Matrix structure
				{1, 0}, {0, 0}, {0, 0},
				{0, 0}, {1, 0}, {0, 0},
				{0, 0}, {0, 0}, {1, 0}
		},
		{WIDTH, 0},  								// Track width
		{HEIGHT, 0}  								// Track height
};

const MuTFFTrackAtom trak_template = {
		tkhd_template,
		mdia_template,
		false,          // tapt present
		{},
		false,          // clip present
		{},
		false,          // matt present
		{},
		false,          // edts present
		{},
		false,          // tref present
		{},
		false,          // txas present
		{},
		false,          // load present
		{},
		false,          // imap present
		{},
		false,          // udta present
		{}
};

const MuTFFMovieHeaderAtom mvhd_template = {
		0,	         								// Version
		0,           								// Flags
		0,	         								// Creation time
		0, 	         								// Modification time
		FRAME_RATE,  								// Frames per second
		0,           								// Duration
		{1, 0},      								// Preferred rate
		{1, 0},      								// Preferred volume
		{            								// Matrix structure
				{1, 0}, {0, 0}, {0, 0},
				{0, 0}, {1, 0}, {0, 0},
				{0, 0}, {0, 0}, {1, 0}
		},
		0,           								// Preview time
		0,           								// Preview duration
		0,           								// Poster time
		0,           								// Selection time
		0,           								// Selection duration
		0,           								// Current time
		0           								// Next track ID
};

const MuTFFMovieAtom moov_template = {
		mvhd_template,          // mvhd
		1,                      // trak count
		{                       // trak
				trak_template,  // trak[0]
		},
		false,                  // clip present
		{},                     // clip
		false,                  // ctab present
		{},                     // ctab
		false,                  // udta present
		{}                      // udta
};

const MuTFFFileTypeAtom ftyp_template = {
		MuTFF_FOURCC('q', 't', ' ', ' '),          // Major brand
		0x20160900,                                // Minor version
		2,                                         // Compatible brands count
		{								           // Compatible brands
				MuTFF_FOURCC('q', 't', ' ', ' '),  // Compatible brands[0]
				MuTFF_FOURCC('m', 'p', '4', '1')   // Compatible brands[1]
		}
};

const MuTFFMovieFile file_template = {
		true,           // ftyp present
		ftyp_template,  // ftyp
		moov_template,  // moov
		0,              // mdat count
		{},             // mdat
		0,              // free count
		{},             // free
		0,              // skip count
		{},             // skip
		0,              // wide count
		{},             // wide
		false,          // preview present
		{}              // preview
};

#endif /* INC_CONTAINER_TEMPLATE_H_ */
