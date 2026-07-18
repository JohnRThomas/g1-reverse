/* readable reconstruction; identity: FUN_0007e022 @ 0x0007e022
 * public-name: free_list_add
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   free_list_add                            <= FUN_0007e022 @ 0x0007e022
 */
/* Reconstructed free_list_add @ 0x0007e022 from Zephyr heap.c.
 * Raw backmap: FUN_0007e022@0x0007e022. */

#include <stdint.h>
#define free_list_add free_list_add
extern uint32_t chunk_size(void *heap,void *chunk);
extern uint32_t FUN_0007de82(uint32_t heap_size,uint32_t chunk_size); /* bucket index */
extern uintptr_t chunk_field(void *heap,void *chunk,uint32_t field);
extern void chunk_set(void *heap,void *chunk,uint32_t field,void *value);
void free_list_add(void *heap_arg,void *chunk)
{
 uint8_t *heap=(uint8_t*)heap_arg;uint32_t heap_size=*(uint32_t*)(heap+8u);uint32_t size=chunk_size(heap_arg,chunk);
 if(heap_size>=0x8000u && size==1u)return;
 uint32_t index=FUN_0007de82(heap_size,size);void **slot=(void**)(heap+0x10u+index*4u);void *head=*slot;
 if(head==0){*(uint32_t*)(heap+0x0cu)|=1u<<index;*slot=chunk;chunk_set(heap_arg,chunk,2u,chunk);chunk_set(heap_arg,chunk,3u,chunk);return;}
 void *tail=(void*)chunk_field(heap_arg,head,2u);chunk_set(heap_arg,chunk,2u,tail);chunk_set(heap_arg,chunk,3u,head);chunk_set(heap_arg,tail,3u,chunk);chunk_set(heap_arg,head,2u,chunk);
}
