/* ------------------------------------------- */
/* ----------------- GLOBAL ------------------ */
/* TODO ogz to q3map converter. */

/************************************************
 * UNIT_OGZRAD_ATTR
 * Description:
 * 	Every OGZ radiant octree has its own list
 * 		of attributes (additional parameters like: texture, material,
 * 			       color, modified faces, alpha etc.)
 * 	By default octree have no attributes.
 ***********************************************/
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

struct ogzrad_attr_header {
	uint8_t			   type;
	struct ogzrad_attr_header *next;
};

void ogzrad_attr_header_init(struct ogzrad_attr_header *self,
			     const uint8_t		type)
{
	self->type = type;
	self->next = NULL;
}

/* TODO continue. */

/* ------------------------------------------- */
/* ------------- MEMORY MANAGMENT ------------ */
struct ogzrad_attr_allocator {
	uint8_t *buf;
	size_t	 buf_size;

	size_t allocated;
};

void ogzrad_attr_allocator_init(struct ogzrad_attr_allocator *self)
{
	self->buf      = NULL;
	self->buf_size = 0;

	self->allocated = 0;
}

void ogzrad_attr_allocator_assign_buffer(struct ogzrad_attr_allocator *self,
					 uint8_t *buf, const size_t size)
{
	self->buf      = buf;
	self->buf_size = size;
}

void *ogzrad_attr_allocator_alloc(struct ogzrad_attr_allocator *self,
				  const uint8_t			size)
{
	void *memory;

	assert(self->allocated + size <= self->buf_size);

	memory		 = &self->buf[self->allocated];
	self->allocated += size;

	return memory;
}

/* TODO tests. */

/************************************************
 * UNIT_OGZRAD_OCTREE
 * Description:
 * 	OGZ Radiant octree data structure.
 ***********************************************/
struct ogzrad_octree {
	enum {
		OGZRAD_OCTREE_FLAG_EMPTY = 0,
		OGZRAD_OCTREE_FLAG_SOLID = 1
	} flags;
	struct ogzrad_octree	  *children[8];
	struct ogzrad_attr_header *attributes;
};

void ogzrad_octree_init(struct ogzrad_octree *self)
{
	int i;

	self->flags = OGZRAD_OCTREE_FLAG_EMPTY;

	for (i = 0; i < 8; i++)
		self->children[i] = NULL;

	self->attributes = NULL;
}

void ogzrad_octree_add_attr(struct ogzrad_octree *self, const uint8_t type)
{
	struct ogzrad_attr_header **header = &self->attributes;
	
	while (*header)
		header = &(*header)->next;

	/* TODO */
	(void)type;
}

/* TODO continue. */
/* TODO tests. */

/* ------------------------------------------- */
/* ------------- MEMORY MANAGMENT ------------ */
struct ogzrad_octree_allocator {
	uint8_t *buf;
	size_t	 buf_size;

	size_t allocated;
};

void ogzrad_octree_allocator_init(struct ogzrad_octree_allocator *self)
{
	self->buf      = NULL;
	self->buf_size = 0;

	self->allocated = 0;
}

void ogzrad_octree_allocator_assign_buffer(struct ogzrad_octree_allocator *self,
					   uint8_t *buf, const size_t size)
{
	self->buf      = buf;
	self->buf_size = size;
}

struct ogzrad_octree *ogzrad_octree_allocator_alloc(struct ogzrad_octree_allocator *self)
{
	struct ogzrad_octree *memory;
	const int octree_sz = sizeof(struct ogzrad_octree) * 8;
	int i;

	assert(self->allocated + octree_sz <= self->buf_size);

	memory		 = (struct ogzrad_octree *)&self->buf[self->allocated];
	self->allocated += octree_sz;

	for (i = 0; i < 8; i++)
		ogzrad_octree_init(&memory[i]);

	return memory;
}

/************************************************
 * UNIT_OGZRAD
 * Description:
 * 	Main OGZ radiant instance.
 ***********************************************/
struct ogzrad {	
	uint8_t *buf;
	size_t	 buf_size;

	struct ogzrad_attr_allocator attr_a;
	struct ogzrad_octree_allocator octree_a;
};

void ogzrad_init(struct ogzrad *self)
{
	self->buf      = NULL;
	self->buf_size = 0;
	
	ogzrad_attr_allocator_init(&self->attr_a);
	ogzrad_octree_allocator_init(&self->octree_a);
}

void ogzrad_assign_buffer(struct ogzrad *self, uint8_t *buf, const size_t size)
{
	self->buf      = buf;
	self->buf_size = size;
	
	/* TODO assign subbuffers for allocators. */
}

/* TODO continue. */
/* TODO tests. */
