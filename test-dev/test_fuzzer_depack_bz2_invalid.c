#include "test.h"


TEST(test_fuzzer_depack_bz2_invalid)
{
	xmp_context opaque;
	int ret;

	opaque = xmp_create_context();

	/* This input caused uninitialized reads in the original bzip2
	 * depacker due to a faulty check on group selectors. */
	ret = xmp_load_module(opaque, "data/f/depack_bz2_invalid_selector.bz2");
	fail_unless(ret == -XMP_ERROR_DEPACK, "depacking (invalid_selector)");

	/* This input caused out-of-bounds array reads in the Huffman
	 * decoder due to bounds checking the index after indexing by it. */
	ret = xmp_load_module(opaque, "data/f/depack_bz2_invalid_tree.bz2");
	fail_unless(ret == -XMP_ERROR_DEPACK, "depacking (invalid_tree)");

	xmp_free_context(opaque);
}
END_TEST
