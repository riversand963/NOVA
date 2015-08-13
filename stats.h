/*
 * Persistent Memory File System
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */


/* ======================= Timing ========================= */
enum timing_category {
	init_t,
	mount_t,
	ioremap_t,
	recovery_t,

	/* Namei operations */
	create_t,
	lookup_t,
	link_t,
	unlink_t,
	symlink_t,
	mkdir_t,
	rmdir_t,
	mknod_t,
	rename_t,
	readdir_t,
	add_entry_t,
	remove_entry_t,
	setattr_t,

	/* I/O operations */
	dax_read_t,
	cow_write_t,
	page_cache_write_t,
	copy_to_nvmm_t,

	/* Memory operations */
	memcpy_r_nvmm_t,
	memcpy_r_dram_t,
	memcpy_w_nvmm_t,
	memcpy_w_dram_t,
	memcpy_w_wb_t,
	partial_block_t,

	/* Memory management */
	new_data_blocks_t,
	new_log_blocks_t,
	new_meta_block_t,
	new_cache_page_t,
	free_data_t,
	free_log_t,
	free_meta_t,
	free_cache_t,

	/* Logging and journaling */
	logging_t,
	append_entry_t,
	log_gc_t,
	check_invalid_t,

	/* Others */
	find_cache_t,
	assign_t,
	fsync_t,
	direct_IO_t,
	delete_file_tree_t,
	delete_dir_tree_t,
	new_vfs_inode_t,
	new_pmfs_inode_t,
	free_inode_t,
	free_inode_log_t,
	evict_inode_t,
	mmap_fault_t,
	malloc_test_t,

	/* Sentinel */
	TIMING_NUM,
};

extern const char *Timingstring[TIMING_NUM];
extern unsigned long long Timingstats[TIMING_NUM];
extern u64 Countstats[TIMING_NUM];
extern unsigned long long read_bytes;
extern unsigned long long cow_write_bytes;
extern unsigned long long page_cache_write_bytes;
extern unsigned long long fsync_bytes;
extern unsigned long long checked_pages;
extern unsigned long gc_pages;
extern unsigned long alloc_data_pages;
extern unsigned long free_data_pages;
extern unsigned long alloc_log_pages;
extern unsigned long free_log_pages;
extern atomic64_t fsync_pages;
extern atomic64_t meta_alloc;
extern atomic64_t meta_free;
extern atomic64_t cache_alloc;
extern atomic64_t cache_free;
extern atomic64_t mempair_alloc;
extern atomic64_t mempair_free;
extern atomic64_t dirnode_alloc;
extern atomic64_t dirnode_free;
extern atomic64_t header_alloc;
extern atomic64_t header_free;

extern int measure_timing;
extern int contiguous_allocation;
extern int support_clwb;

typedef struct timespec timing_t;

#define PMFS_START_TIMING(name, start) \
	{if (measure_timing) getrawmonotonic(&start);}

#define PMFS_END_TIMING(name, start) \
	{if (measure_timing) { \
		timing_t end; \
		getrawmonotonic(&end); \
		Timingstats[name] += \
			(end.tv_sec - start.tv_sec) * 1000000000 + \
			(end.tv_nsec - start.tv_nsec); \
	} \
	Countstats[name]++; \
	}

extern unsigned long alloc_steps;
extern unsigned long free_steps;
extern unsigned long write_breaks;
