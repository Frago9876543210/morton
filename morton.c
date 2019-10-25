/* morton extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_morton.h"

#include <immintrin.h>

/* {{{ int morton_interleave2( int $x, int $y )
 */
PHP_FUNCTION(morton_interleave2)
{
	zend_ulong x, y;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(_pdep_u64(x, 0x5555555555555555) | _pdep_u64(y, 0xaaaaaaaaaaaaaaaa));
}
/* }}}*/

/* {{{ void morton_deinterleave2( int $hash, int &$x, int &$y )
 */
PHP_FUNCTION(morton_deinterleave2)
{
	zend_ulong hash;
	zval *zX = NULL, *zY = NULL;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(hash)
		Z_PARAM_ZVAL_DEREF(zX)
		Z_PARAM_ZVAL_DEREF(zY)
	ZEND_PARSE_PARAMETERS_END();

	zval_ptr_dtor(zX);
	ZVAL_LONG(zX, (int32_t) _pext_u64(hash, 0x5555555555555555));

	zval_ptr_dtor(zY);
	ZVAL_LONG(zY, (int32_t) _pext_u64(hash, 0xaaaaaaaaaaaaaaaa));
}
/* }}}*/

/* {{{ int morton_interleave3( int $x, int $y, int $z )
 */
PHP_FUNCTION(morton_interleave3)
{
	zend_ulong x, y, z;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_LONG(x)
		Z_PARAM_LONG(y)
		Z_PARAM_LONG(z)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(_pdep_u64(x, 0x9249249249249249) | _pdep_u64(y, 0x2492492492492492) | _pdep_u64(z, 0x4924924924924924));
}
/* }}}*/

/* {{{ void morton_deinterleave3( int $hash, int &$x, int &$y, int &$z )
 */
PHP_FUNCTION(morton_deinterleave3)
{
	zend_ulong hash;
	zval *zX = NULL, *zY = NULL, *zZ = NULL;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_LONG(hash)
		Z_PARAM_ZVAL_DEREF(zX)
		Z_PARAM_ZVAL_DEREF(zY)
		Z_PARAM_ZVAL_DEREF(zZ)
	ZEND_PARSE_PARAMETERS_END();

	zend_ulong x, y, z;

	x = ((int32_t) _pext_u64(hash, 0x9249249249249249)) << 11 >> 11;
	y = ((int32_t) _pext_u64(hash, 0x2492492492492492)) << 11 >> 11;
	z = ((int32_t) _pext_u64(hash, 0x4924924924924924)) << 11 >> 11;

	zval_ptr_dtor(zX);
	ZVAL_LONG(zX, x);

	zval_ptr_dtor(zY);
	ZVAL_LONG(zY, y);

	zval_ptr_dtor(zZ);
	ZVAL_LONG(zZ, z);
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(morton)
{
#if defined(ZTS) && defined(COMPILE_DL_MORTON)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(morton)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "morton support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_morton_interleave2, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_morton_deinterleave2, 0)
	ZEND_ARG_INFO(0, hash)
	ZEND_ARG_INFO(1, x)
	ZEND_ARG_INFO(1, y)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_morton_interleave3, 0)
	ZEND_ARG_INFO(0, x)
	ZEND_ARG_INFO(0, y)
	ZEND_ARG_INFO(0, z)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_morton_deinterleave3, 0)
	ZEND_ARG_INFO(0, hash)
	ZEND_ARG_INFO(1, x)
	ZEND_ARG_INFO(1, y)
	ZEND_ARG_INFO(1, z)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ morton_functions[]
 */
static const zend_function_entry morton_functions[] = {
	PHP_FE(morton_interleave2,   	arginfo_morton_interleave2)
	PHP_FE(morton_deinterleave2, 	arginfo_morton_deinterleave2)
	PHP_FE(morton_interleave3,   	arginfo_morton_interleave3)
	PHP_FE(morton_deinterleave3, 	arginfo_morton_deinterleave3)
	PHP_FE_END
};
/* }}} */

/* {{{ morton_module_entry
 */
zend_module_entry morton_module_entry = {
	STANDARD_MODULE_HEADER,
	"morton",					/* Extension name */
	morton_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(morton),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(morton),			/* PHP_MINFO - Module info */
	PHP_MORTON_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MORTON
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(morton)
#endif

