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


#define FRAME_RATE 9
#define WIDTH 320
#define HEIGHT 240
#define DURATION 0
#define BIT_DEPTH 16
#define SAMPLE_SIZE (WIDTH * HEIGHT * BIT_DEPTH / 8)
#define DATA_SIZE (SAMPLE_SIZE * DURATION)

const MuTFFSampleDescription sample_desc_template = {
		MuTFF_FOURCC('j', 'p', 'e', 'g'),  // Data format
		1,                                 // Data reference index
		70,                                // Additional data size
		{                                  // Additional data
				0x00, 0x00,                // Version
				0x00, 0x00,                // Revision level
				0x00, 0x00, 0x00, 0x00,    // Vendor
				0x00, 0x00, 0x00, 0x00,    // Temporal quality
				0x00, 0x00, 0x00, 0x00,    // Spatial quality
				0x01, 0x40,                // Width
				0x00, 0xf0,                // Height
				0x00, 0x48, 0x00, 0x00,    // Horizontal resolution
				0x00, 0x48, 0x00, 0x00,    // Vertical resolution
				0x00, 0x00, 0x00, 0x00,    // Data size
				0x00, 0x01,                // Frame count
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x10,                // Depth
				0xFF, 0xFF                 // Color table ID

		}
};

const MuTFFSampleDescriptionAtom stsd_template = {
		0,  // Version
		0,  // Flags
		1,  // Number of entries
		{   // Entries
				sample_desc_template
		}
};

const MuTFFTimeToSampleAtom stts_template = {
		0,                         // Version
		0,                         // Flags
		1,                         // Number of entries
		{                          // Entries
				{
						DURATION,  // Sample count
						1          // Sample duration
				}
		}
};

const MuTFFSampleToChunkAtom stsc_template = {
		0,  // Version
		0,  // Flags
		1,  // Number of entries
		{
				{
						1,         // First chunk
						DURATION,  // Samples per chunk
						1          // Sample description ID
				}
		}
};

const MuTFFSampleSizeAtom stsz_template = {
		0,            // Version
		0,            // Flags,
		SAMPLE_SIZE,  // Sample size
		DURATION,     // Number of entries
		{}            // Entries
};

const MuTFFChunkOffsetAtom stco_template = {
		0,  // Version
		0,  // Flags
		1,  // Number of entries
		{   // Entries
				0
		}
};

const MuTFFSampleTableAtom stbl_template = {
		stsd_template,  // stsd
		stts_template,  // stts
		false,          // ctts present
		{},             // ctts
		false,          // cslg present
		{},             // cslg
		false,          // stss present
		{},             // stss
		false,          // stps present
		{},             // stps
		true,           // stsc present
		stsc_template,  // stsc
		true,           // stsz present
		stsz_template,  // stsz
		true,           // stco present
		stco_template,  // stco
		false,          // sdtp present
		{}              // sdtp
};

const MuTFFDataReference data_ref_template = {
		MuTFF_FOURCC('u', 'r', 'l', ' '),  // Type
		0,                                 // Version
		1,                                 // Flags
		0,                                 // Data size
		{}                                 // Data
};

const MuTFFDataReferenceAtom dref_template = {
		0,  // Version
		0,  // Flags
		1,  // Number of entries
		{   // Data references
				data_ref_template
		}
};

const MuTFFDataInformationAtom dinf_template = {
		dref_template,
};

const MuTFFHandlerReferenceAtom minf_hdlr_template = {
		0,                                 // Version
		0,                                 // Flags
		MuTFF_FOURCC('m', 'h', 'l', 'r'),  // Component type
		MuTFF_FOURCC('v', 'i', 'd', 'e'),  // Component subtype
		0,                                 // Component manufacturer
		0,                                 // Component flags
		0,                                 // Component flags mask
		""                                 // Component name
};

const MuTFFVideoMediaInformationHeaderAtom vmhd_template = {
		0,          // Version
		1,          // Flags
		0,          // Graphics mode
		{
				0,  // opcolor[0]
				0,  // opcolor[1]
				0   // opcolor[2]
		}
};

const MuTFFVideoMediaInformationAtom minf_template = {
		vmhd_template,       // vmhd
		minf_hdlr_template,  // hdlr
		true,                // dinf present
		dinf_template,       // dinf
		true,                // stbl present
		stbl_template        // stbl
};

const MuTFFHandlerReferenceAtom mdia_hdlr_template = {
		0,                                 // Version
		0,                                 // Flags
		MuTFF_FOURCC('m', 'h', 'l', 'r'),  // Component type
		MuTFF_FOURCC('v', 'i', 'd', 'e'),  // Component subtype
		0,                                 // Component manufacturer
		0,                                 // Component flags
		0,                                 // Component flags mask
		""                                 // Component name
};

const MuTFFMediaHeaderAtom mdhd_template = {
		0,           // Version
		0,           // Flags
		0,           // Creation time
		0,           // Modification time
		FRAME_RATE,  // Time scale
		DURATION,    // Duration
		0,		     // Language
		0,           // Quality
};

const MuTFFMediaAtom mdia_template = {
		mdhd_template,       // mdhd
		false,               // elng present
		{},
		true,                // hdlr present
		mdia_hdlr_template,
		true,                // minf present
		minf_template,
		{},
		{},
		false,               // udta present
		{}
};

const MuTFFTrackHeaderAtom tkhd_template = {
		0,        									// Version
		0,        									// Flags
		0,        									// Creation time
		0,        									// Modification time
		0,        									// Track ID
		DURATION,        							// Duration
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
		DURATION,           						// Duration
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
		MuTFF_FOURCC(20, 16, 9, 0),                // Minor version
		1,                                         // Compatible brands count
		{								           // Compatible brands
				MuTFF_FOURCC('q', 't', ' ', ' '),  // Compatible brands[0]
		}
};

const MuTFFMovieFile file_template = {
		true,           // ftyp present
		ftyp_template,  // ftyp
		moov_template,  // moov
		1,              // mdat count
		{               // mdat
				{
						DATA_SIZE,
						0
				}
		},
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
