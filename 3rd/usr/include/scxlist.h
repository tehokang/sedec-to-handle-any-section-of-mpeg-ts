/*************************************************************************************************************
	File 		: scxlist.h
	author 		: STC Component tstbcomp@humaxdigital.com
	comment		:
	date    	: 2013/12/27
	attention 	: This module copied from klist in linux kernel.

	(c) 2011-2014 Humax Co., Ltd.
	This program is produced by Humax Co., Ltd. (¡°Humax¡±) and
	the proprietary Software of Humax and its licensors. Humax provides you, as an Authorized Licensee,
	non-assignable, non-transferable and non-exclusive license to use this Software.
	You acknowledge that this Software contains valuable trade secrets of Humax and by using this Software
	you agree to the responsibility to take all reasonable efforts to protect the any information
	you receive from Humax. You are not permitted to duplicate, modify, distribute, sell or lease and
	reverse engineer or extract the source code of this Software unless you have Humax's written permission
	to do so.
	If you have no authorized license, discontinue using this Software immediately.

	THE SOFTWARE IS PROVIDED ¡°AS IS¡± AND HUMAX MAKES NO PROMISES, REPRESENTATIONS OR WARRANTIES,
	EITHER EXPRESS, IMPLIED OR STATUTORY, OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.
	IN NO EVENT SHALL HUMAX BE LIABLE FOR LOST PROFITS, REVENUES, OR DATA, FINANCIAL LOSSES OR
	INDIRECT, SPECIAL, CONSEQUENTIAL, EXEMPLARTY OR PUNITIVE DAMAGES WHATSOEVER RELATING TO YOUR USE OR
	INABILITY TO USE THE SOFTWARE.

	This License is effective until terminated. You may terminate this License at any time
	by destroying all copies of the Software including all documentation. This License will terminate
	immediately without notice from Humax to you if you fail to comply with any provision of this License.
	Upon termination, you must destroy all copies of the Software and all documentation.

	The laws of the Republic of Korea will apply to any disputes arising out of or relating to
	this Copyright Notice. All claims arising out of or relating to this Copyright Notice will be litigated
	in the Seoul Central District Court, in the Republic of Korea.
*************************************************************************************************************/



#ifndef __SCXLIST_H__
#define __SCXLIST_H__

typedef struct scxlist_head {
	struct scxlist_head *next, *prev;
} scxlist_head;

#define SCXLIST_HEAD_INIT(name) { &(name), &(name) }

#define SCXLIST_HEAD(name) \
	struct scxlist_head name = SCXLIST_HEAD_INIT(name)

#define INIT_SCXLIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries. 
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __scxlist_add(struct scxlist_head *newone,
		struct scxlist_head *prev,
		struct scxlist_head *next)
{
	next->prev = newone;
	newone->next = next;
	newone->prev = prev;
	prev->next = newone;
}

/**
 * scxlist_add - add a newone entry
 * @newone: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void scxlist_add(struct scxlist_head *newone, struct scxlist_head *head)
{
	__scxlist_add(newone, head, head->next);
}

/**
 * scxlist_add_tail - add a new entry
 * @newone: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void scxlist_add_tail(struct scxlist_head *newone, struct scxlist_head *head)
{
	__scxlist_add(newone, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __scxlist_del(struct scxlist_head *prev, struct scxlist_head *next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * scxlist_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: scxlist_empty on entry does not return true after this, the entry is in an undefined state.
 */
static inline void scxlist_del(struct scxlist_head *entry)
{
	__scxlist_del(entry->prev, entry->next);
	entry->next = (scxlist_head *) 0;
	entry->prev = (scxlist_head *) 0;
}

/**
 * scxlist_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void scxlist_del_init(struct scxlist_head *entry)
{
	__scxlist_del(entry->prev, entry->next);
	INIT_SCXLIST_HEAD(entry); 
}

/**
 * scxlist_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void scxlist_move(struct scxlist_head *list, struct scxlist_head *head)
{
	__scxlist_del(list->prev, list->next);
	scxlist_add(list, head);
}

/**
 * scxlist_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void scxlist_move_tail(struct scxlist_head *list,
		struct scxlist_head *head)
{
	__scxlist_del(list->prev, list->next);
	scxlist_add_tail(list, head);
}

/**
 * scxlist_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int scxlist_empty(struct scxlist_head *head)
{
	return head->next == head;
}

static inline void __scxlist_splice(struct scxlist_head *list,
		struct scxlist_head *head)
{
	struct scxlist_head *first = list->next;
	struct scxlist_head *last = list->prev;
	struct scxlist_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

/**
 * scxlist_splice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void scxlist_splice(struct scxlist_head *list, struct scxlist_head *head)
{
	if (!scxlist_empty(list))
		__scxlist_splice(list, head);
}

/**
 * scxlist_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static inline void scxlist_splice_init(struct scxlist_head *list,
		struct scxlist_head *head)
{
	if (!scxlist_empty(list)) {
		__scxlist_splice(list, head);
		INIT_SCXLIST_HEAD(list);
	}
}

/**
 * scxlist_entry - get the struct for this entry
 * @ptr:	the &struct scxlist_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the scxlist_struct within the struct.
 */
#define scxlist_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * scxlist_for_each	-	iterate over a list
 * @pos:	the &struct scxlist_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define scxlist_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
			pos = pos->next)
/**
 * scxlist_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct scxlist_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define scxlist_for_each_prev(pos, head) \
	for (pos = (head)->prev; pos != (head); \
			pos = pos->prev)

/**
 * scxlist_for_each_safe	-	iterate over a list safe against removal of list entry
 * @pos:	the &struct scxlist_head to use as a loop counter.
 * @n:		another &struct scxlist_head to use as temporary storage
 * @head:	the head for your list.
 */
#define scxlist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

/**
 * scxlist_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop counter.
 * @head:	the head for your list.
 * @member:	the name of the scxlist_struct within the struct.
 */
#define scxlist_for_each_entry(pos, head, member)				\
	for (pos = scxlist_entry((head)->next, typeof(*pos), member);	\
			&pos->member != (head); 					\
			pos = scxlist_entry(pos->member.next, typeof(*pos), member))

/**
 * scxlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the scxlist_struct within the struct.
 */
#define scxlist_for_each_entry_safe(pos, n, head, member)			\
	for (pos = scxlist_entry((head)->next, typeof(*pos), member),	\
			n = scxlist_entry(pos->member.next, typeof(*pos), member);	\
			&pos->member != (head); 					\
			pos = n, n = scxlist_entry(n->member.next, typeof(*n), member))

#endif	/* __SCXLIST_H__ */
