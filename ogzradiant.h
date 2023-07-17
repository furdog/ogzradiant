/* ------------------------------------------- */
/* ----------------- GLOBAL ------------------ */
/* TODO ogz to q3map converter. */

/************************************************
 * UNIT_OGZRAD_ALLOCATOR
 * Description:
 * 	Linear memory allocator for fast object managment.
 ***********************************************/
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

struct ogzrad_allocator {
	uint8_t *buf;
	size_t	 buf_size;

	size_t allocated;
};

void ogzrad_allocator_init(struct ogzrad_allocator *self)
{
	self->buf      = NULL;
	self->buf_size = 0;

	self->allocated = 0;
}

void ogzrad_allocator_assign_buffer(struct ogzrad_allocator *self,
					 uint8_t *buf, const size_t size)
{
	self->buf      = buf;
	self->buf_size = size;
}

void *ogzrad_allocator_alloc(struct ogzrad_allocator *self,
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
 * UNIT_OGZRAD_ATTR
 * Description:
 * 	Every octree has its own list
 * 		of attributes (additional parameters like: texture, material,
 * 			       color, modified faces, alpha etc.)
 * 	By default octree have no attributes.
 ***********************************************/
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

/************************************************
 * UNIT_OGZRAD_OCTREE_NODE
 * Description:
 * 	Single octree node data structure.
 ***********************************************/
struct ogzrad_octree_node {
	enum {
		OGZRAD_OCTREE_NODE_FLAG_EMPTY = 0,
		OGZRAD_OCTREE_NODE_FLAG_SOLID = 1
	} flags;
	struct ogzrad_octree_node *subnodes;
	struct ogzrad_attr_header *attributes;
};

void ogzrad_octree_node_init(struct ogzrad_octree_node *self)
{
	self->flags = OGZRAD_OCTREE_NODE_FLAG_EMPTY;
	self->subnodes = NULL;
	self->attributes = NULL;
}

/* TODO continue. */
/* TODO tests. */

/************************************************
 * UNIT_OGZRAD_OCTREE
 * Description:
 * 	Octree data structure manager.
 ***********************************************/
struct ogzrad_octree {
	struct ogzrad_allocator attr_a;
	struct ogzrad_allocator node_a;
	
	struct ogzrad_octree_node root;
};

void ogzrad_octree_init(struct ogzrad_octree *self)
{
	ogzrad_allocator_init(&self->attr_a);
	ogzrad_allocator_init(&self->node_a);
}

void ogzrad_octree_assign_buffer(struct ogzrad_octree *self, uint8_t *buf, const size_t size)
{
	(void)self;
	(void)buf;
	(void)size;
	/* TODO assign buffer to allocators. */
}

void ogzrad_octree_create_subnodes(struct ogzrad_octree *self, struct ogzrad_octree_node *parent)
{
	const int subnodes_sz = sizeof(struct ogzrad_octree_node) * 8;
	int i;

	parent->subnodes = (struct ogzrad_octree_node *)ogzrad_allocator_alloc(&self->node_a, subnodes_sz);
	for (i = 0; i < 8; i++)
		ogzrad_octree_node_init(&parent->subnodes[i]);
}

void ogzrad_octree_node_add_attr(struct ogzrad_octree_node *self, const uint8_t type)
{
	struct ogzrad_attr_header **header = &self->attributes;
	
	while (*header)
		header = &(*header)->next;

	/* TODO */
	(void)type;
}

/************************************************
 * UNIT_OGZRAD
 * Description:
 * 	Main OGZ Radiant instance.
 ***********************************************/
struct ogzrad {	
	struct ogzrad_octree octree;
};

void ogzrad_init(struct ogzrad *self)
{
	ogzrad_octree_init(&self->octree);
}

void ogzrad_assign_buffer(struct ogzrad *self, uint8_t *buf, const size_t size)
{
	ogzrad_octree_assign_buffer(&self->octree, buf, size);
}

/* TODO continue. */
/* TODO tests. */
